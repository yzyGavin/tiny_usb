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
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn, uint16_t EP);
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



// Copy data to PMA buffer, if memory is aligned, copy two by two
static void tusb_pma_tx(tusb_device_t* dev, pma_record* pma, const void* data, uint32_t len)
{
  uint32_t count = (len + 1) / 2;
  pma_data *dest = GetPMAAddr(dev, pma->addr);
  pma->cnt = len;
#ifdef ALIGNED
  const uint16_t *src = ( const uint16_t *)data;
  for (uint8_t i = 0; i < count; i++) {
		dest->data = *src;
		dest++;
		src++;
	}
#else
  const uint8_t *src = ( const uint8_t *)data;
  for (uint8_t i = 0; i < count; i++) {
    uint16_t v = src[0] | (src[1]<<8);
    src+=2;
		dest->data = v;
		dest++;
	}
#endif
}

// Copy data from PMA buffer, if memory is aligned, copy two by two
static uint32_t tusb_pma_rx(tusb_device_t* dev, pma_record* pma, void* data)
{
  uint32_t len = pma->cnt;
  pma_data *src = GetPMAAddr(dev, pma->addr);
  uint32_t count = (len+1)/2;  
#ifdef ALIGNED
  uint16_t *dest = (uint16_t *) data;
  for (uint32_t i = 0; i < count; i++) {
		*dest = src->data;
		dest++;
		src++;
	}
#else
  uint8_t *dest = (uint8_t *) data;
  for (uint32_t i = 0; i < count; i++) {
		uint16_t v = src->data;
    *dest = (uint8_t)v;
    dest++;
    v>>=8;
    *dest = (uint8_t)v;
    dest++;
		src++;
	}
#endif
  return len;
}

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


// helper function to copy data to end point
static void copy_tx(tusb_device_t* dev, tusb_ep_data* ep, pma_record* pma, const void* data, uint16_t len, uint16_t tx_max_size)
{ 
    ep->tx_size = len;
    ep->tx_buf = (const uint8_t*) data;
    if(len > tx_max_size){
      len = tx_max_size;
    }
    tusb_pma_tx(dev, pma, data, len);
    ep->tx_pushed++;
    ep->tx_buf += len;
    ep->tx_size -= len;
    ep->tx_last_size = len;
}

// send data
int tusb_send_data(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len)
{
  uint16_t  EP = PCD_GET_ENDPOINT(GetUSB(dev), EPn);
  tusb_ep_data* ep = &dev->Ep[EPn];
  if(ep->tx_size) return -1;
  if( DOUBLE_BUFF  && (EP & (USB_EP_TYPE_MASK | USB_EP_KIND)) == (USB_EP_BULK | USB_EP_KIND)){
    // double buffer ep send data
    pma_record* pma0;
    pma_record* pma1;
    uint16_t TOG = (EP & (USB_EP_DTOG_RX | USB_EP_DTOG_TX));
    if( TOG != 0 && TOG != (USB_EP_DTOG_RX | USB_EP_DTOG_TX)){
      return -1;
    }
    ep->tx_pushed = 0;
    if(EP & USB_EP_DTOG_RX){
      pma0 = PMA_TX1(dev, EPn);
      pma1 = PMA_TX0(dev, EPn);
    }else{
      pma0 = PMA_TX0(dev, EPn);
      pma1 = PMA_TX1(dev, EPn);
    }
    copy_tx(dev, ep, pma0, data, len, GetInMaxPacket(dev, EPn));
    if( ep->tx_size || ep->tx_last_size == GetInMaxPacket(dev, EPn) ){
      copy_tx(dev, ep, pma1, ep->tx_buf, ep->tx_size, GetInMaxPacket(dev, EPn));
    }
    // toggle it
    TUSB_RX_DTOG(GetUSB(dev), EPn, EP);
  }else if( ISO_EP && ((EP & USB_EP_TYPE_MASK) == USB_EP_ISOCHRONOUS ) ){
    pma_record* pma = EP & USB_EP_DTOG_TX ? PMA_TX0(dev, EPn) : PMA_TX1(dev, EPn);
    ep->tx_pushed = 0;
    copy_tx(dev, ep, pma, data, len, GetInMaxPacket(dev, EPn));
    TUSB_SET_TX_STATUS(GetUSB(dev), EPn, EP, USB_EP_TX_VALID);
  }else{
    // normal ep send data
    if( (EP & USB_EPTX_STAT) != USB_EP_TX_NAK){
      return -1;
    }
    ep->tx_pushed = 0;
    copy_tx(dev, ep, PMA_TX(dev, EPn), data, len, GetInMaxPacket(dev, EPn));
    TUSB_SET_TX_STATUS(GetUSB(dev), EPn, EP, USB_EP_TX_VALID);
  }
  return 0;
}

// called by the ep data interrupt handler when last packet tranfer done
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn, uint16_t EP)
{
  tusb_ep_data* ep = &dev->Ep[EPn];
  //uint16_t  EP = PCD_GET_ENDPOINT(GetUSB(dev), EPn);
  pma_record* pma;
  if(DOUBLE_BUFF && (EP & (USB_EP_TYPE_MASK | USB_EP_KIND)) == (USB_EP_BULK | USB_EP_KIND)){
    // double buffer bulk end point, toggle first then copy data
    if(ep->tx_pushed){ep->tx_pushed--;}
    if(ep->tx_pushed){
      // toggle it first, then do some copy
      TUSB_RX_DTOG(GetUSB(dev), EPn, EP);
    }
    pma = (EP & USB_EP_DTOG_RX) ? PMA_TX0(dev, EPn) : PMA_TX1(dev, EPn);
  }else if( ISO_EP && ((EP & USB_EP_TYPE_MASK) == USB_EP_ISOCHRONOUS ) ){
    ep->tx_pushed = 0;
    pma = (EP & USB_EP_DTOG_TX) ? PMA_TX0(dev, EPn) : PMA_TX1(dev, EPn);
  }else{
    ep->tx_pushed = 0;
    pma = PMA_TX(dev, EPn);
  }
  if(ep->tx_size || ep->tx_last_size == GetInMaxPacket(dev, EPn)){
    copy_tx(dev, ep, pma, ep->tx_buf, ep->tx_size, GetInMaxPacket(dev, EPn));
    PCD_SET_EP_TX_STATUS(GetUSB(dev), EPn, USB_EP_TX_VALID);
    return;
  }
  if(ep->tx_pushed == 0){
    tusb_on_tx_done(dev, EPn);
  }
}

// set ep rx valid
void set_rx_valid(tusb_device_t* dev, uint8_t EPn)
{
  uint16_t  EP = PCD_GET_ENDPOINT(GetUSB(dev), EPn);
  tusb_ep_data* ep = &dev->Ep[EPn];
  ep->rx_count = 0;
  if(DOUBLE_BUFF && (EP & (USB_EP_TYPE_MASK | USB_EP_KIND)) == (USB_EP_BULK | USB_EP_KIND)){
    // Rx inital for double buffer ep
    uint16_t TOG = (EP & (USB_EP_DTOG_RX | USB_EP_DTOG_TX));
    pma_record* pma = 0;
    pma = (EP & USB_EP_DTOG_TX) ? PMA_RX0(dev, EPn) :  PMA_RX1(dev, EPn);
    // got the pma buffer last used by the USB core
    if(pma->cnt){
      // already has data in the pma buffer, copy it to the rx buffer
      uint32_t len = tusb_pma_rx(dev, pma, ep->rx_buf + ep->rx_count);
      pma->cnt = 0;
      ep->rx_count += len;
      if(len != GetOutMaxPacket(dev, EPn) || ep->rx_count >= ep->rx_size){
        if(tusb_on_rx_done(dev, EPn, ep->rx_buf, ep->rx_count) == 0){
          ep->rx_count = 0;
        }else{
          ep->rx_count = ep->rx_size;
        }
      }
    }
    if( TOG == 0 || TOG == (USB_EP_DTOG_RX | USB_EP_DTOG_TX)){
      // always enter here
      TUSB_TX_DTOG(GetUSB(dev), EPn, EP);
    }
  }else{
    // Rx initial for normal ep
    TUSB_SET_RX_STATUS(GetUSB(dev), EPn, EP, USB_EP_RX_VALID);
  }
}

// helper function to read ep0
uint32_t tusb_read_ep0(tusb_device_t* dev, void* buf)
{
  return tusb_pma_rx(dev, PMA_RX(dev, 0), buf);
}

// called by the ep data interrupt handler when got data
void tusb_recv_data(tusb_device_t* dev, uint8_t EPn, uint16_t EP)
{
  tusb_ep_data* ep = &dev->Ep[EPn];
  pma_record* pma = 0;
  if(DOUBLE_BUFF && (EP & (USB_EP_TYPE_MASK | USB_EP_KIND)) == (USB_EP_BULK | USB_EP_KIND)){
    // double buffer bulk end point
    if(ep->rx_count < ep->rx_size){
      TUSB_TX_DTOG(GetUSB(dev), EPn, EP);
      // If App last used buffer is 1, dev will fill data in 0
      // If App last used buufer is 0, dev will fill data in 1
      // We read the data filled by device
      pma = (EP & USB_EP_DTOG_TX) ? PMA_RX0(dev, EPn) :  PMA_RX1(dev, EPn);
    }
  }else if( ISO_EP && ((EP & USB_EP_TYPE_MASK) == USB_EP_ISOCHRONOUS ) ){
    pma = (EP & USB_EP_DTOG_RX) ? PMA_TX0(dev, EPn) : PMA_TX1(dev, EPn);
  }else{
    pma = PMA_RX(dev, EPn);
  }
  if(ep->rx_buf && pma){
    uint32_t len = tusb_pma_rx(dev, pma, ep->rx_buf + ep->rx_count);
    pma->cnt = 0;
    ep->rx_count += len;
    if(len != GetOutMaxPacket(dev, EPn) || ep->rx_count >= ep->rx_size){
      if(tusb_on_rx_done(dev, EPn, ep->rx_buf, ep->rx_count) == 0){
        ep->rx_count = 0;
      }else{
        // of rx done not return success, change rx_count to rx_size, this will block
        // the data recieve
        ep->rx_count = ep->rx_size;
      }
    }
  }
  if(ep->rx_count<ep->rx_size){
    TUSB_SET_RX_STATUS(GetUSB(dev), EPn, EP, USB_EP_RX_VALID);
  }
}



