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
#include "tiny_usb.h"
// Default function to get report descriptor
// some class need report descriptor, e.g. HID, user should override it
WEAK const uint8_t* tusb_get_report_descriptor(tusb_device_t* dev, tusb_setup_packet *req, uint16_t* len)
{
  /**
   // example code for get report descriptor
   uint16_t interfaceIndex = req->wIndex;
   switch(interfaceIndex){
     case 0: 
         *len = interface_0_report_descriptor_size;
         return interface_0_report_descriptor;
     case 1:
         *len = interface_1_report_descriptor_size;
         return interface_1_report_descriptor;
   }
   */
  *len = 0;
  return 0;
}

// Default class request handler
// User need override it if the class need some special request
WEAK void tusb_class_request(tusb_device_t* dev, tusb_setup_packet* setup_req)
{
  tusb_send_data(dev, 0, 0, 0);
}

// Standard get descriptor function
static void tusb_get_descriptor(tusb_device_t* dev, tusb_setup_packet *req)
{
  const uint8_t* desc = 0;
  uint16_t len = 0;
	switch (HI_BYTE(req->wValue)) {
		case USB_DESC_TYPE_DEVICE:
      desc = dev->descriptors->device;
      if(desc) len = desc[0];
      break;
		case USB_DESC_TYPE_CONFIGURATION:
      desc = dev->descriptors->config;
      if(desc)len = *((uint16_t*)desc + 1);
      break;
		case USB_DESC_TYPE_REPORT:
      desc = tusb_get_report_descriptor(dev, req, &len);
      break;
    case USB_DESC_TYPE_STRING:
    {
      uint8_t index = LO_BYTE(req->wValue);
      if(index < dev->descriptors->string_cnt){
        desc = dev->descriptors->strings[index];
        if(desc)len = desc[0];
      }
#if defined(HAS_WCID)
      else if(index == 0xee && dev->descriptors->wcid_desc){
        desc = WCID_StringDescriptor_MSOS;
        len = desc[0];
      }
#endif
      break;
    }
	}
  tusb_send_data(dev, 0, desc,
					req->wLength > len ? len : req->wLength);
}

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
static void tusb_set_addr (tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef *USBx = GetUSB(dev);
  USBx_DEVICE->DCFG &= ~ (USB_OTG_DCFG_DAD);
  USBx_DEVICE->DCFG |= (dev->addr << 4) & USB_OTG_DCFG_DAD ;
}
#else
// Callback function for set address setup
static void tusb_set_addr(tusb_device_t* dev)
{
  if (dev->addr){
    GetUSB(dev)->DADDR = (dev->addr | USB_DADDR_EF);
    dev->addr = 0;
  }
}
#endif

#if defined(HAS_WCID)
static void tusb_vendor_request(tusb_device_t* dev, tusb_setup_packet* setup_req)
{
  uint32_t len = 0;
  const uint8_t* desc = 0;
  switch (setup_req->bRequest) {
    case WCID_VENDOR_CODE:
      switch(setup_req->wIndex)
      case 4:
        desc = dev->descriptors->wcid_desc;
        len = desc[0] + (desc[1]<<8) + (desc[2]<<16) + (desc[3]<<24);
        break;
      case 5:
        desc = dev->descriptors->wcid_properties;
        len = desc[0] + (desc[1]<<8) + (desc[2]<<16) + (desc[3]<<24);
        break;
  }
  // TODO: Handle length more than 0xffff
  tusb_send_data(dev, 0, desc,
					setup_req->wLength > len ? len : setup_req->wLength);
}
#endif

// Standard request process function
static void tusb_standard_request(tusb_device_t* dev, tusb_setup_packet* setup_req)
{
  // TODO: need process the interface and end point standard request
  /** for example:
   switch(setup_req->bmRequestType & USB_REQ_RECIPIENT_MASK ){
    USB_REQ_RECIPIENT_DEVICE:
    // standard device request
    break;
    USB_REQ_RECIPIENT_INTERFACE:
      // standard interface request
      uint16_t interface_index  = setup_req->wIndex;
      if(setup_req->bRequest  == USB_REQ_CLEAR_FEATURE){
      }else if(setup_req->bRequest  == USB_REQ_SET_FEATURE){
      }
    break;
    USB_REQ_RECIPIENT_ENDPOINT:
      // standard end point request
      uint8_t ep_addr  = LO_BYTE(setup_req->wIndex);
      if(setup_req->bRequest  == USB_REQ_CLEAR_FEATURE){
          // ep clear feature
      }else if(setup_req->bRequest  == USB_REQ_SET_FEATURE){
          // ep set feature
      }
    break;
   }
   */
  switch (setup_req->bRequest) {
  case USB_REQ_SET_ADDRESS:
    dev->addr = LO_BYTE(setup_req->wValue);
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
    tusb_set_addr(dev);
#else
    dev->status_callback = tusb_set_addr;
#endif
    tusb_send_data(dev, 0, 0, 0);
    break;
  
  case USB_REQ_GET_DESCRIPTOR:
    tusb_get_descriptor(dev, setup_req);
    break;
  
  case USB_REQ_GET_STATUS:
    tusb_send_data(dev, 0, (uint16_t *) &dev->status, 2);
    break;
  
  case USB_REQ_GET_CONFIGURATION:
    tusb_send_data(dev, 0, (uint16_t *) &dev->config, 1);
    break;
  
  case USB_REQ_SET_CONFIGURATION:
    dev->config = LO_BYTE(setup_req->wValue);
    tusb_send_data(dev, 0, 0, 0);
    break;
  
  case USB_REQ_GET_INTERFACE:
    tusb_send_data(dev, 0, &dev->alt_cfg, 1);
    break;
  case USB_REQ_SET_INTERFACE:
    dev->alt_cfg = LO_BYTE(setup_req->wValue);
    tusb_send_data(dev, 0, 0, 0);
    break;
  
  default:
    tusb_send_data(dev, 0, 0, 0);
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
    {
      PCD_TypeDef* USBx =  GetUSB(dev);
      USBx_INEP(0)->DIEPCTL &= ~(USB_OTG_DIEPCTL_EPDIS);
      USBx_INEP(0)->DIEPCTL |= USB_OTG_DIEPCTL_STALL;
    }
#else
    PCD_SET_EP_TX_STATUS(GetUSB(dev), 0 , USB_EP_TX_STALL);
#endif
    break;
  }
}

// forward declare for some internal function
void tusb_recv_data(tusb_device_t* dev, uint8_t EPn, uint16_t EP);
void tusb_send_data_done(tusb_device_t* dev, uint8_t EPn, uint16_t EP);
uint32_t tusb_read_ep0(tusb_device_t* dev, void* buf);
void tusb_read_data(tusb_device_t* dev, void* buf, uint32_t len);
// end point data handler
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)

void tusb_setup_handler(tusb_device_t* dev)
{
  tusb_setup_packet *setup_req = &dev->setup;
  if( (setup_req->bmRequestType & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_CLASS){
    tusb_class_request(dev, setup_req);
#if defined(HAS_WCID)
  }else if((setup_req->bmRequestType & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_VENDOR){
    tusb_vendor_request(dev, setup_req);
#endif
  }else{
    tusb_standard_request(dev, setup_req);
  }
}

void tusb_ep_tx_handler(tusb_device_t* dev, uint8_t ep)
{
  //PCD_TypeDef* USBx = dev->handle;
  if(ep == 0 && dev->status_callback && dev->Ep[0].tx_size == 0){
    // invoke status transmitted call back for ep0
    dev->status_callback(dev);
    dev->status_callback = 0;
  }
  tusb_send_data_done(dev, ep, ep);
}

#else
void tusb_ep_handler(tusb_device_t* dev, uint8_t EPn)
{
	uint16_t EP = PCD_GET_ENDPOINT(GetUSB(dev), EPn);
	if (EP & USB_EP_CTR_RX) {
		if (EPn == 0) {
			if (EP & USB_EP_SETUP) {
        // Handle setup packet
        tusb_read_ep0(dev, &dev->setup);
        tusb_setup_packet *setup_req = &dev->setup;
        if( (setup_req->bmRequestType & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_CLASS){
          tusb_class_request(dev, setup_req);
#if defined(HAS_WCID)
        }else if((setup_req->bmRequestType & USB_REQ_TYPE_MASK) == USB_REQ_TYPE_VENDOR){
          tusb_vendor_request(dev, setup_req);
#endif
        }else{
          tusb_standard_request(dev, setup_req);
        }
			}else{
        // Handle ep 0 data packet
        if(dev->Ep[0].rx_buf){
          tusb_ep_data* ep = &dev->Ep[0];
          uint32_t len = tusb_read_ep0(dev, ep->rx_buf + ep->rx_count);
          ep->rx_count += len;
          if(len < GetOutMaxPacket(dev, 0) || ep->rx_count >= ep->rx_size){
            // when got ep 0 data, invoke the setup data out call back
            if(dev->rx0_callback){
              dev->rx0_callback(dev);
              dev->rx0_callback = 0;
            }
            ep->rx_buf = 0;
          }
        }else{
          // recv ep0 data, but not processed, drop it
        }
      }
      TUSB_CLEAR_RX_CTR(GetUSB(dev), PCD_ENDP0, EP);
      TUSB_SET_RX_STATUS(GetUSB(dev), PCD_ENDP0, EP, USB_EP_RX_VALID);
		}else{
      TUSB_CLEAR_RX_CTR(GetUSB(dev), EPn, EP);
      tusb_recv_data(dev, EPn, EP);
    }
	}
  if ( (EP & USB_EP_CTR_TX)) { // something transmitted
    if(EPn == 0 && dev->status_callback){
      // invoke status transmitted call back for ep0
      dev->status_callback(dev);
      dev->status_callback = 0;
    }
    TUSB_CLEAR_TX_CTR(GetUSB(dev), EPn, EP);
    tusb_send_data_done(dev, EPn, EP);
	}
}
#endif

// initial the ep recv buffer
int tusb_set_recv_buffer(tusb_device_t* dev, uint8_t EPn, void* data, uint16_t len)
{
  tusb_ep_data* ep = &dev->Ep[EPn];
  ep->rx_buf = (uint8_t*)data;
  ep->rx_size = len;
  ep->rx_count = 0;
  return 0;
}

