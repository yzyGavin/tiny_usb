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

// tiny usb platform header for STM32F7 device
#ifndef __STM32F7_PLATFORM_H__
#define __STM32F7_PLATFORM_H__

#include "usbd_def.h"
#include "usbd_core.h"
#define PCD_ENDP0                                                     ((uint8_t)0)
#define PCD_ENDP1                                                     ((uint8_t)1)
#define PCD_ENDP2                                                     ((uint8_t)2)
#define PCD_ENDP3                                                     ((uint8_t)3)
#define PCD_ENDP4                                                     ((uint8_t)4)
#define PCD_ENDP5                                                     ((uint8_t)5)
#define PCD_ENDP6                                                     ((uint8_t)6)
#define PCD_ENDP7                                                     ((uint8_t)7)
#define PCD_ENDP8                                                     ((uint8_t)8)
#define PCD_ENDP9                                                     ((uint8_t)9)

#define USB_EP_CONTROL                                                USBD_EP_TYPE_CTRL
#define USB_EP_ISOCHRONOUS                                            USBD_EP_TYPE_ISOC
#define USB_EP_BULK                                                   USBD_EP_TYPE_BULK
#define USB_EP_INTERRUPT                                              USBD_EP_TYPE_INTR


#define USB_OTG_FS_MAX_EP_NUM   6
#define USB_OTG_HS_MAX_EP_NUM   9

#if defined(USB_OTG_FS) && defined(USB_OTG_HS)
#define  USB_CORE_HANDLE_TYPE        PCD_TypeDef*
#define  GetUSB(dev)           ((dev)->handle)
#endif



#define init_ep_tx(dev, EPn, type, mps)                                                    \
do{                                                                                        \
  PCD_TypeDef *USBx = GetUSB(dev);                                                         \
  uint32_t maxpacket = mps;                                                                \
  USB_OTG_INEndpointTypeDef* INEp = USBx_INEP(EPn);                                        \
  if(USBx == USB_OTG_FS && EPn == 0){                                                      \
    maxpacket = __CLZ(maxpacket) - 25;                                                     \
  }                                                                                        \
  USBx_DEVICE->DAINTMSK |=  ( (USB_OTG_DAINTMSK_IEPM) & ( (1 << (EPn))) );                 \
  INEp->DIEPCTL |= ((maxpacket & USB_OTG_DIEPCTL_MPSIZ ) | (type << 18 ) |                 \
    ((EPn) << 22 ) | (USB_OTG_DIEPCTL_SD0PID_SEVNFRM) | (USB_OTG_DIEPCTL_USBAEP));         \
}while(0)

#define init_ep_rx(dev, EPn, type, mps)                                                    \
do{                                                                                        \
  PCD_TypeDef *USBx = GetUSB(dev);                                                         \
  uint32_t maxpacket = mps;                                                                \
  if(EPn == 0){                                                                            \
    maxpacket = __CLZ(maxpacket) - 25;                                                     \
  }                                                                                        \
  USBx_DEVICE->DAINTMSK |=  ( (USB_OTG_DAINTMSK_OEPM) & ( (1 << (EPn))<<16 ) );            \
  USBx_OUTEP(EPn)->DOEPCTL |= ((maxpacket & USB_OTG_DOEPCTL_MPSIZ ) | (type << 18 ) |      \
    (USB_OTG_DOEPCTL_SD0PID_SEVNFRM) | (USB_OTG_DIEPCTL_USBAEP));                          \
}while(0)

#define INIT_EP_Tx(dev, bEpNum, type, maxpacket)  \
do{\
  init_ep_tx(dev, bEpNum, type, maxpacket);\
}while(0)

#define INIT_EP_Rx(dev, bEpNum, type, maxpacket) \
do{\
  init_ep_rx(dev, bEpNum, type, maxpacket);\
}while(0)

// In OTG core, a fifo is used to handle the rx/tx data, all rx ep share a same fifo, each tx ep has a fifo

#define  SET_TX_FIFO(dev, bEpNum, addr, size) \
do{\
  if(bEpNum == 0){\
    GetUSB(dev)->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((uint32_t)( (size)/4) << 16) | ( (addr)/4));\
  }else{\
    GetUSB(dev)->DIEPTXF[bEpNum==0?0: bEpNum- 1] = (uint32_t)(((uint32_t)( (size)/4) << 16) | ( (addr)/4));\
  }\
}while(0)

#define  SET_RX_FIFO(dev, addr, size) \
  do{\
    GetUSB(dev)->GRXFSIZ = (size/4);\
  }while(0)

#endif

