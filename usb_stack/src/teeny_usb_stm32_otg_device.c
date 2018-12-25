/*
 * teeny usb - light weight usb stack for STM32 micro controllers
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
#include "teeny_usb.h"

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)

// Public functions used by user app
int tusb_send_data(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len);
int tusb_set_recv_buffer(tusb_device_t* dev, uint8_t EPn, void* data, uint16_t len);
void tusb_set_rx_valid(tusb_device_t* dev, uint8_t EPn);


// Private functions used by teeny usb core
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn);
uint32_t tusb_read_ep0(tusb_device_t* dev, void* buf);
void tusb_recv_data(tusb_device_t* dev, uint8_t EPn, uint16_t EP);

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


void tusb_otg_read_data(USB_OTG_GlobalTypeDef *USBx, void* buf, uint32_t len)
{
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
  if(EPn == 0){
    if(USBx == USB_OTG_FS){
      // for the ep0 in otg FS core, the max packet size is defined by
      // DEP0CTL_MPS_64, DEP0CTL_MPS_32, DEP0CTL_MPS_16, DEP0CTL_MPS_8
      maxpacket = 8ul * (1ul << (3 - (maxpacket & 3) ));
    }else{
      // For high speed core, ep0 always 64 bytes, there is no mps info in DIEPCTL
      maxpacket = 64;
    }
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
  
  if(ISO_EP && ( (epin->DIEPCTL & USB_OTG_DIEPCTL_EPTYP)  ==  ((USB_EP_ISOCHRONOUS)<<(USB_OTG_DIEPCTL_EPTYP_Pos)) ) ){
    // ISO ep
    //USBx_INEP(EPn)->DIEPTSIZ &= ~(USB_OTG_DIEPTSIZ_MULCNT);
    epin->DIEPTSIZ |= (USB_OTG_DIEPTSIZ_MULCNT & (1 << 29));
    
    if ((USBx_DEVICE->DSTS & ( 1 << 8 )) == 0){
      epin->DIEPCTL |= USB_OTG_DIEPCTL_SODDFRM;
    }else{
      epin->DIEPCTL |= USB_OTG_DIEPCTL_SD0PID_SEVNFRM;
    }
  }
  
  
  if(USBx->GAHBCFG & USB_OTG_GAHBCFG_DMAEN){
    epin->DIEPDMA = (uint32_t)ep->tx_buf;
  }else{  
    if(len > 0){
      USBx_DEVICE->DIEPEMPMSK |= (1 << EPn);
    }
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
    }else if(dev->ep0_tx_done){
      // invoke status transmitted call back for ep0
      dev->ep0_tx_done(dev);
      dev->ep0_tx_done = 0;
    }
  }
  // clear the fifo empty mask
  tusb_on_tx_done(dev, EPn);
}

// un-like the USB FS core, we need buffer size to set the ep valid
void tusb_set_rx_valid(tusb_device_t* dev, uint8_t EPn)
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
  
  if(USBx->GAHBCFG & USB_OTG_GAHBCFG_DMAEN){
    epout->DOEPDMA = (uint32_t)ep->rx_buf;
  }
  
  if(ISO_EP && ((epout->DOEPCTL & USB_OTG_DOEPCTL_EPTYP)  ==  ((USB_EP_ISOCHRONOUS)<<(USB_OTG_DOEPCTL_EPTYP_Pos))) ){
    if ((USBx_DEVICE->DSTS & ( 1 << 8 )) == 0){
      epout->DOEPCTL |= USB_OTG_DOEPCTL_SODDFRM;
    }else{
      epout->DOEPCTL |= USB_OTG_DOEPCTL_SD0PID_SEVNFRM;
    }
  }
  epout->DOEPCTL |= (USB_OTG_DOEPCTL_CNAK | USB_OTG_DOEPCTL_EPENA);
}


#define  INTR()   (USBx->GINTSTS & USBx->GINTMSK)

void tusb_setup_handler(tusb_device_t* dev);

// Interrupt handler of DEVICE mode
void tusb_otg_device_handler(tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef *USBx = GetUSB(dev);
  uint32_t MAX_EP_NUM = USBx == USB_OTG_FS ? USB_OTG_FS_MAX_EP_NUM : USB_OTG_HS_MAX_EP_NUM;
  

  /* ensure that we are in device mode */
  //if (USB_GetMode(USBx) == USB_OTG_MODE_DEVICE)
  {
    // no flag set, return directly
    if(INTR() == 0){
      return;
    }

    if(INTR() & USB_OTG_GINTSTS_MMIS){
     /* incorrect mode, acknowledge the interrupt */
      USBx->GINTSTS = USB_OTG_GINTSTS_MMIS;
    }
    
    // Handle output 
    if(INTR() & USB_OTG_GINTSTS_OEPINT){
      uint32_t ep_intr = ((USBx_DEVICE->DAINT & USBx_DEVICE->DAINTMSK)) >> 16;
      uint8_t ep = 0;
      while(ep_intr){
        if(ep >= MAX_EP_NUM){
          break;
        }
        if (ep_intr & 0x1){
          uint32_t epint = USBx_OUTEP(ep)->DOEPINT;
          if(( epint & USB_OTG_DOEPINT_XFRC) == USB_OTG_DOEPINT_XFRC){
            // Get data from ep0, data of setup packet, the recv buffer is prepared in tusb_setup_handler
            if(ep == 0){
              // when got ep 0 data, invoke the setup data out call back
              if(dev->ep0_rx_done){
                dev->ep0_rx_done(dev);
                dev->ep0_rx_done = 0;
              }
              dev->Ep[0].rx_buf = 0;
            }else{
              if(tusb_on_rx_done(dev, ep, dev->Ep[ep].rx_buf, dev->Ep[ep].rx_count) == 0){
                dev->Ep[ep].rx_count = 0;
                tusb_set_rx_valid(dev, ep);
              }else{
                dev->Ep[ep].rx_count = dev->Ep[ep].rx_size;
              }
            }
          }
          if(( epint & USB_OTG_DOEPINT_STUP) == USB_OTG_DOEPINT_STUP){
            // Do it in USB_OTG_GINTSTS_RXFLVL interrupt
            tusb_setup_handler(dev);
            tusb_set_rx_valid(dev, 0);
          }
          // clear all interrupt flags
          USBx_OUTEP(ep)->DOEPINT = epint;
        }
        ep_intr>>=1;
        ep+=1;
      }
    }

    // handle input
    if(INTR() & USB_OTG_GINTSTS_IEPINT){
      uint32_t ep_intr = (USBx_DEVICE->DAINT & USBx_DEVICE->DAINTMSK) & 0xffff;
      uint8_t ep = 0;
      while(ep_intr){
        if(ep >= MAX_EP_NUM){
          break;
        }
        if (ep_intr & 0x1){
          USB_OTG_INEndpointTypeDef* epin = USBx_INEP(ep);
          uint32_t epint = epin->DIEPINT;
          // Xfer complete interrupt handler
          if(epint & USB_OTG_DIEPINT_XFRC){
            USBx_DEVICE->DIEPEMPMSK &= ~(0x1ul << ep);
            epin->DIEPINT = USB_OTG_DIEPINT_XFRC;
            tusb_send_data_done(dev, ep);
          }
          
//          if(( epint & USB_OTG_DIEPINT_TOC) == USB_OTG_DIEPINT_TOC){
//            epin->DIEPINT = USB_OTG_DIEPINT_TOC;
//          }
//          if(( epint & USB_OTG_DIEPINT_ITTXFE) == USB_OTG_DIEPINT_ITTXFE){
//            epin->DIEPINT = USB_OTG_DIEPINT_ITTXFE;
//          }
//          if(( epint & USB_OTG_DIEPINT_INEPNE) == USB_OTG_DIEPINT_INEPNE){
//            epin->DIEPINT = USB_OTG_DIEPINT_INEPNE;
//          }
//          if(( epint & USB_OTG_DIEPINT_EPDISD) == USB_OTG_DIEPINT_EPDISD){
//            epin->DIEPINT = USB_OTG_DIEPINT_EPDISD;
//          }
          // FIFO empty interrupt handler
          if( ((epint & USB_OTG_DIEPINT_TXFE) == USB_OTG_DIEPINT_TXFE) && (USBx_DEVICE->DIEPEMPMSK & (1 << ep)) ){
            tusb_fifo_empty(dev, ep);
          }
          // clear all interrupts
          epin->DIEPINT = epint;
        }
        ep_intr>>=1;
        ep+=1;
      }
    }
    /* Handle Resume Interrupt */
    if(INTR() & USB_OTG_GINTSTS_WKUINT){
      // TODO: leave low power mode
      /* Clear the Remote Wake-up Signaling */
      USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_RWUSIG;
      USBx->GINTSTS = USB_OTG_GINTSTS_WKUINT;
    }

    /* Handle Suspend Interrupt */
    if(INTR()& USB_OTG_GINTSTS_USBSUSP){
      // TODO: enter low power mode
      USBx->GINTSTS = USB_OTG_GINTSTS_USBSUSP;
    }

    /* Handle LPM Interrupt */
    if(INTR() & USB_OTG_GINTSTS_LPMINT){
      USBx->GINTSTS = USB_OTG_GINTSTS_LPMINT;
    }

    /* Handle Reset Interrupt */
    if(INTR() & USB_OTG_GINTSTS_USBRST ){
      uint32_t i;
      USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_RWUSIG;
      flush_tx(USBx, 0x10);
      for (i = 0; i < MAX_EP_NUM ; i++)
      {
        USBx_INEP(i)->DIEPINT = 0xFF;
        USBx_INEP(i)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
        USBx_INEP(i)->DIEPCTL |= USB_OTG_DIEPCTL_EPDIS;
        USBx_OUTEP(i)->DOEPINT = 0xFF;
        USBx_OUTEP(i)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
        USBx_OUTEP(i)->DOEPCTL |= USB_OTG_DOEPCTL_EPDIS;
      }
      USBx_DEVICE->DAINT = 0xFFFFFFFF;
      USBx_DEVICE->DAINTMSK |= 0x10001;
      {
        USBx_DEVICE->DOEPMSK |= (USB_OTG_DOEPMSK_STUPM | USB_OTG_DOEPMSK_XFRCM | USB_OTG_DOEPMSK_EPDM | USB_OTG_DOEPMSK_OTEPSPRM);
        USBx_DEVICE->DIEPMSK |= (USB_OTG_DIEPMSK_TOM | USB_OTG_DIEPMSK_XFRCM | USB_OTG_DIEPMSK_EPDM);
      }

      /* Set Default Address to 0 */
      USBx_DEVICE->DCFG &= ~USB_OTG_DCFG_DAD;

      /* setup EP0 to receive SETUP packets */
      // setup ep0
      USBx_OUTEP(0)->DOEPTSIZ = 0;
      USBx_OUTEP(0)->DOEPTSIZ |= (USB_OTG_DOEPTSIZ_PKTCNT & (1 << 19)) ;
      USBx_OUTEP(0)->DOEPTSIZ |= (3 * 8);
      USBx_OUTEP(0)->DOEPTSIZ |=  USB_OTG_DOEPTSIZ_STUPCNT;
      if(USBx->GAHBCFG & USB_OTG_GAHBCFG_DMAEN){
        USBx_OUTEP(0)->DOEPDMA = (uint32_t)&dev->setup;
        /* EP enable */
        USBx_OUTEP(0)->DOEPCTL = 0x80008000;
      }
      USBx->GINTSTS = USB_OTG_GINTSTS_USBRST;
    }

    /* Handle Enumeration done Interrupt */
    if(INTR() & USB_OTG_GINTSTS_ENUMDNE ){
      tusb_reconfig(dev);
      USBx->GUSBCFG &= ~USB_OTG_GUSBCFG_TRDT;
      switch(USBx_DEVICE->DSTS & USB_OTG_DSTS_ENUMSPD){
        case DSTS_ENUMSPD_HS_PHY_30MHZ_OR_60MHZ:
          USBx->GUSBCFG |= (uint32_t)((USBD_HS_TRDT_VALUE << 10) & USB_OTG_GUSBCFG_TRDT);
          break;
        case DSTS_ENUMSPD_LS_PHY_6MHZ:
          USBx_INEP(0)->DIEPCTL |= 3; // force ep0 packet size to 8 when in LS mode
        case DSTS_ENUMSPD_FS_PHY_30MHZ_OR_60MHZ:
        case DSTS_ENUMSPD_FS_PHY_48MHZ:
          USBx->GUSBCFG |= (uint32_t)((0x6 << 10) & USB_OTG_GUSBCFG_TRDT);
          break;
      }
      USBx_DEVICE->DCTL |= USB_OTG_DCTL_CGINAK;
      USBx->GINTSTS = USB_OTG_GINTSTS_ENUMDNE;
    }

    /* Handle RxQLevel Interrupt */
    if(INTR() & USB_OTG_GINTSTS_RXFLVL){
      USB_MASK_INTERRUPT(USBx, USB_OTG_GINTSTS_RXFLVL);
      {
        uint32_t sts = USBx->GRXSTSP;
        uint8_t EPn = sts & USB_OTG_GRXSTSP_EPNUM;
        uint32_t len = (sts & USB_OTG_GRXSTSP_BCNT) >> 4;
        if(((sts & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_DATA_UPDT){
          tusb_ep_data* ep = &dev->Ep[EPn];
          if(ep->rx_count<ep->rx_size && ep->rx_buf){
            // copy data packet
            tusb_otg_read_data(USBx, ep->rx_buf + ep->rx_count, len);
            ep->rx_count += len;
          }else{
            // drop the data because no memory to handle them
            tusb_otg_read_data(USBx,0, len);
          }
        }else if(((sts & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_SETUP_UPDT){
          // copy setup packet
          tusb_otg_read_data(USBx, &dev->setup, len);
        }
      }
      USB_UNMASK_INTERRUPT(USBx, USB_OTG_GINTSTS_RXFLVL);
    }

    /* Handle SOF Interrupt */
    if(INTR() & USB_OTG_GINTSTS_SOF){
      USBx->GINTSTS = USB_OTG_GINTSTS_SOF;
    }

    /* Handle Incomplete ISO IN Interrupt */
    if(INTR() & USB_OTG_GINTSTS_IISOIXFR){
      USBx->GINTSTS = USB_OTG_GINTSTS_IISOIXFR;
    }

    /* Handle Incomplete ISO OUT Interrupt */
    if(INTR() & USB_OTG_GINTSTS_PXFR_INCOMPISOOUT){
      USBx->GINTSTS = USB_OTG_GINTSTS_PXFR_INCOMPISOOUT;
    }

    /* Handle Connection event Interrupt */
    if(INTR() & USB_OTG_GINTSTS_SRQINT){
      USBx->GINTSTS = USB_OTG_GINTSTS_SRQINT;
    }

    /* Handle Disconnection event Interrupt */
    if(INTR() & USB_OTG_GINTSTS_OTGINT){
      uint32_t temp = USBx->GOTGINT;
      if((temp & USB_OTG_GOTGINT_SEDET) == USB_OTG_GOTGINT_SEDET){
        // dis connect event
      }
      USBx->GOTGINT |= temp;
    }
  }
}

#endif // #if defined(USB_OTG_FS) || defined(USB_OTG_HS)

