/*
 * tiny usb - light weight usb stack for STM32 micro controllers
 * 
 * Copyright (c) 2018 XToolBox  - admin@xtoolbox.org
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "string.h"
#include "tiny_usb.h"

// Public functions used by user app
int tusb_send_data(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len);
int tusb_set_recv_buffer(tusb_device_t* dev, uint8_t EPn, void* data, uint16_t len);
void set_rx_valid(tusb_device_t* dev, uint8_t EPn);


// Private functions used by tiny usb core
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn);
uint32_t tusb_read_ep0(tusb_device_t* dev, void* buf);
void tusb_recv_data(tusb_device_t* dev, uint8_t EPn, uint16_t EP);

// Public callback function override by user
// default data transmit done callback
WEAK void tusb_on_tx_done(tusb_device_t* dev, uint8_t EPn)
{}

// default data received  callback, return 0 will continue receive data in end point rx buffer
// return other value will cause the OUT ep NAX, user can active the OUT ep by call set_rx_valid
WEAK int tusb_on_rx_done(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len)
{ return 0; }

#ifdef HAS_DOUBLE_BUFFER
#define  DOUBLE_BUFF 1
#else
#define  DOUBLE_BUFF 0
#endif
#ifdef HAS_ISO_EP
#define  ISO_EP  1
#else
#define  ISO_EP  0
#endif


void tusb_read_data(tusb_device_t* dev, void* buf, uint32_t len)
{
  USB_OTG_GlobalTypeDef *USBx = GetUSB(dev);
  __packed uint32_t * dest = (__packed uint32_t *)buf;
  len = (len + 3) / 4;
  while(len){
    if(dest){
      *(__packed uint32_t *)dest = USBx_DFIFO(0);
    }else{
      uint32_t t = USBx_DFIFO(0);
    }
    dest++;
    len--;
  }
}

static uint32_t get_max_in_packet_size(PCD_TypeDef* USBx, uint8_t EPn)
{
  uint32_t maxpacket = USBx_INEP(EPn)->DIEPCTL & USB_OTG_DIEPCTL_MPSIZ;
  if(EPn == 0 && USBx == USB_OTG_FS){
    // for the ep0 in otg FS core, the max packet size is defined by
    // DEP0CTL_MPS_64, DEP0CTL_MPS_32, DEP0CTL_MPS_16, DEP0CTL_MPS_8
    maxpacket = 8ul * (1ul << (3 - (maxpacket & 3) ));
  }
  return maxpacket;
}

static uint32_t get_max_out_packet_size(PCD_TypeDef* USBx, uint8_t EPn)
{
  uint32_t maxpacket = USBx_OUTEP(EPn)->DOEPCTL & USB_OTG_DOEPCTL_MPSIZ;
  if(EPn == 0){
    // for the ep0 in otg FS/HS core, the max packet size is defined by
    // DEP0CTL_MPS_64, DEP0CTL_MPS_32, DEP0CTL_MPS_16, DEP0CTL_MPS_8
    maxpacket = 8ul * (1ul << (3 - (maxpacket & 3) ));
  }
  return maxpacket;
}

int tusb_send_data(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len)
{
  PCD_TypeDef* USBx = GetUSB(dev);
  tusb_ep_data* ep = &dev->Ep[EPn];
  uint32_t maxpacket = GetInMaxPacket(dev, EPn);
  uint32_t pktCnt;
  uint32_t total_len = len;
  USB_OTG_INEndpointTypeDef* epin = USBx_INEP(EPn);
  ep->tx_buf = (const uint8_t*)data;
  if(epin->DIEPCTL & USB_OTG_DIEPCTL_EPENA){
    return -1;
  }

  if(EPn == 0){
    // EP0 always send 1 packet
    if(len > maxpacket){
      len = maxpacket;
    }
  }
  // set remain size of tx buffer, current tx size is saved in the DIEPTSIZ register
  ep->tx_size = total_len - len;
  // calculate last packet size
  ep->tx_last_size = len ? (len-1) % maxpacket + 1 : 0;
  
  pktCnt = (((len + maxpacket - 1) / maxpacket)<<19);
  if(pktCnt == 0){
    // avoid zero packet count, used to send ZLP(zero length packet) 
    pktCnt = 1<<19;
  }
  // clear and set the EPT size field
  epin->DIEPTSIZ =  pktCnt| len;
  
  if( (epin->DIEPCTL & USB_OTG_DIEPCTL_EPTYP)  ==  ((USB_EP_ISOCHRONOUS)<<(USB_OTG_DIEPCTL_EPTYP_Pos)) ){
    // ISO ep
    //USBx_INEP(EPn)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_MULCNT);
    epin->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & (1 << 29));
    
    if ((USBx_DEVICE->DSTS & ( 1 << 8 )) == 0){
      epin->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
    }else{
      epin->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
    }
  }else if(len > 0){
    USBx_DEVICE->DIEPEMPMSK |= (1 << EPn);
  }
  // do not fill data here, data will be filled in the empty interrupt
  //copy_data_to_fifo(dev, ep, EPn, data, len, total_len);
  epin->DIEPCTL |= (USB_OTG_DIEPCTL_CNAK | USB_OTG_DIEPCTL_EPENA);
  
  return 0;
}


// when fifo empty call this function
void tusb_fifo_empty(tusb_device_t* dev, uint8_t EPn)
{
  tusb_ep_data* ep = &dev->Ep[EPn];
  PCD_TypeDef* USBx = GetUSB(dev);
  USB_OTG_INEndpointTypeDef* epin = USBx_INEP(EPn);
  uint32_t xfer_size = epin->DIEPTSIZ & USB_OTG_DIEPTSIZ_XFRSIZ;
  uint32_t maxpacket = GetInMaxPacket(dev, EPn);
  uint32_t fifo_len = epin->DTXFSTS & USB_OTG_DTXFSTS_INEPTFSAV;
  const uint8_t* src = (const uint8_t*)ep->tx_buf;
  uint32_t len32b;
  // round transfer size to max packet boundary
  if(xfer_size > fifo_len*4){
    xfer_size = (fifo_len*4 / maxpacket) * maxpacket;
  }
  len32b = (xfer_size+3) /4;
  // push data to fifo
  while(len32b){
    USBx_DFIFO(EPn) = *((__packed uint32_t *)src);
    src+=4;
    len32b--;
  }
  // adjust the dat buffer
  ep->tx_buf = src;
  //calculate last packet size 
  ep->tx_last_size = xfer_size ? (xfer_size-1)%maxpacket+1 : 0;
  //if( xfer_size == 0){
  if( (epin->DIEPTSIZ & USB_OTG_DIEPTSIZ_XFRSIZ) == 0 ){
    // this xfer complete, so no need the fifo empty interrupt
    USBx_DEVICE->DIEPEMPMSK &= ~(1ul<<EPn);
  }
  
  return;
}

// called by the ep data interrupt handler when last packet tranfer done
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn)
{
  PCD_TypeDef* USBx = GetUSB(dev);
  tusb_ep_data* ep = &dev->Ep[EPn];
  uint32_t maxpacket = get_max_in_packet_size(USBx, EPn);
  //track(EPn, ep->tx_size, 3, ep->tx_last_size);
  if(EPn == 0){
    if(ep->tx_size){
      tusb_send_data(dev, EPn, ep->tx_buf, ep->tx_size);
    }else if(ep->tx_last_size == maxpacket){
      // Send a ZLP
      tusb_send_data(dev, EPn, ep->tx_buf, 0);
    }else if(dev->status_callback){
      // invoke status transmitted call back for ep0
      dev->status_callback(dev);
      dev->status_callback = 0;
    }
  }
  // clear the fifo empty mask
  tusb_on_tx_done(dev, EPn);
}

// un-like the USB FS core, we need buffer size to set the ep valid
void set_rx_valid(tusb_device_t* dev, uint8_t EPn)
{
  PCD_TypeDef* USBx = GetUSB(dev);
  USB_OTG_OUTEndpointTypeDef* epout = USBx_OUTEP(EPn);
  tusb_ep_data* ep = &dev->Ep[EPn];
  uint32_t maxpacket = GetOutMaxPacket(dev, EPn);
  uint32_t pktCnt;
  uint32_t len = ep->rx_size;
  ep->rx_count = 0;
  
  if(EPn == 0){
    // EP0 always recv 1 packet
    if(len > maxpacket){
      len = maxpacket;
    }
  }
  
  pktCnt = (((len + maxpacket - 1) / maxpacket));
  if(pktCnt == 0){
    // avoid zero packet count, used to send ZLP(zero length packet) 
    pktCnt = 1;
  }
  if(len) len = pktCnt * maxpacket;
  // clear and set the EPT size field
  epout->DOEPTSIZ =  (pktCnt<<19) | len;
  
  if(ISO_EP && ((epout->DOEPCTL & USB_OTG_DOEPCTL_EPTYP)  ==  ((USB_EP_ISOCHRONOUS)<<(USB_OTG_DOEPCTL_EPTYP_Pos))) ){
    if ((USBx_DEVICE->DSTS & ( 1 << 8 )) == 0){
      epout->DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM;
    }else{
      epout->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM;
    }
  }
  epout->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
}


