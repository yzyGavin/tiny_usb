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


void tusb_setup_handler(tusb_device_t* dev);

#define  INTR()   (USBx->GINTSTS & USBx->GINTMSK)

// Interrupt handler of HOST mode
void tusb_otg_host_handler(tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef *USBx = GetUSB(dev);
  uint32_t MAX_CH_NUM = USBx == USB_OTG_FS ? USB_OTG_FS_MAX_CH_NUM : USB_OTG_HS_MAX_CH_NUM;
  if(INTR() == 0){
    return;
  }
  if( INTR() & USB_OTG_GINTSTS_PXFR_INCOMPISOOUT ){
    USBx->GINTSTS = USB_OTG_GINTSTS_PXFR_INCOMPISOOUT;
  }
  if(INTR() & USB_OTG_GINTSTS_IISOIXFR){
    USBx->GINTSTS = USB_OTG_GINTSTS_IISOIXFR;
  }
  if(INTR() & USB_OTG_GINTSTS_PTXFE){
    USBx->GINTSTS = USB_OTG_GINTSTS_PTXFE;
  }
  if(INTR() & USB_OTG_GINTSTS_MMIS){
    USBx->GINTSTS = USB_OTG_GINTSTS_MMIS;
  }
  /* Handle Host Disconnect Interrupts */
  if(INTR() &USB_OTG_GINTSTS_DISCINT){
    /* Cleanup HPRT */
    USBx_HPRT0 &= ~(USB_OTG_HPRT_PENA | USB_OTG_HPRT_PCDET |\
      USB_OTG_HPRT_PENCHNG | USB_OTG_HPRT_POCCHNG );
    /* Handle Host Port Interrupts */
    //HAL_HCD_Disconnect_Callback(hhcd);
    //(void)USB_InitFSLSPClkSel(hhcd->Instance, HCFG_48_MHZ);
    USBx->GINTSTS = USB_OTG_GINTSTS_DISCINT;
  }
  /* Handle Host Port Interrupts */
  if( INTR() & USB_OTG_GINTSTS_HPRTINT ){
    //HCD_Port_IRQHandler (hhcd);
    //tusb_port_irq(dev);
  }
  /* Handle Host SOF Interrupts */
  if( INTR() & USB_OTG_GINTSTS_SOF ){
    USBx->GINTSTS = USB_OTG_GINTSTS_SOF;
  }
  /* Handle Host channel Interrupts */
  if( INTR() & USB_OTG_GINTSTS_HCINT ){
    uint32_t hc_intr = (USBx_HOST->HAINT) & 0xFFFFU;
    uint32_t hc = 0;
    while(hc_intr){
      if(hc_intr & 1){
        if ( USBx_HC(hc)->HCCHAR & USB_OTG_HCCHAR_EPDIR ){
          //HCD_HC_IN_IRQHandler(hhcd, (uint8_t)i);
        }else{
          //HCD_HC_OUT_IRQHandler(hhcd, (uint8_t)i);
        }
      }
      hc++;
      hc_intr>>=1;
      if(hc>MAX_CH_NUM) break;
    }
    USBx->GINTSTS = USB_OTG_GINTSTS_HCINT;
  }
  /* Handle Rx Queue Level Interrupts */
  if( INTR() & USB_OTG_GINTSTS_RXFLVL ){
    USB_MASK_INTERRUPT(USBx, USB_OTG_GINTSTS_RXFLVL);
    // tusb_rxqlvl_handler();
    //HCD_RXQLVL_IRQHandler (hhcd);
    USB_UNMASK_INTERRUPT(USBx, USB_OTG_GINTSTS_RXFLVL);
  }
}

#endif // #if defined(USB_OTG_FS) || defined(USB_OTG_HS)

