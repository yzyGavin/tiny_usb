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

//  STM32F7 usb hardware handler
#include "tiny_usb.h"

#ifndef RX_FIFO_SIZE
#define RX_FIFO_SIZE   (128/4)
#endif


// #define  ENABLE_DMA
// #define  ENABLE_VBUS_DETECT 

#define   OTG_FS_SPEED      USB_OTG_SPEED_FULL
#define   OTG_HS_SPEED      USB_OTG_SPEED_HIGH
//#define   OTG_HS_SPEED      USB_OTG_SPEED_HIGH_IN_FULL

#if defined(OTG_HS_EMBEDDED_PHY) && defined(OTG_HS_EXTERNAL_PHY)
#error Embedded and external HS phy can not use together
#endif

static void flush_rx(USB_OTG_GlobalTypeDef *USBx)
{  
  USBx->GRSTCTL = USB_OTG_GRSTCTL_RXFFLSH;
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_RXFFLSH) == USB_OTG_GRSTCTL_RXFFLSH);
}

static void flush_tx(USB_OTG_GlobalTypeDef *USBx, uint32_t num)
{
  USBx->GRSTCTL = ( USB_OTG_GRSTCTL_TXFFLSH |(uint32_t)( num << 6));
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_TXFFLSH) == USB_OTG_GRSTCTL_TXFFLSH);
}

static void Wait_CoreReset(USB_OTG_GlobalTypeDef *USBx)
{
  /* Wait for AHB master IDLE state. */
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_AHBIDL) == 0);
  /* Core Soft Reset */
  USBx->GRSTCTL |= USB_OTG_GRSTCTL_CSRST;
  while ((USBx->GRSTCTL & USB_OTG_GRSTCTL_CSRST) == USB_OTG_GRSTCTL_CSRST);
}

#ifdef USB_HS_PHYC
static void USB_HS_PHYCInit(USB_OTG_GlobalTypeDef *USBx)
{
  uint32_t count = 0;

  /* Enable LDO */
  USB_HS_PHYC->USB_HS_PHYC_LDO |= USB_HS_PHYC_LDO_ENABLE;

  /* wait for LDO Ready */
  while((USB_HS_PHYC->USB_HS_PHYC_LDO & USB_HS_PHYC_LDO_STATUS) == RESET);

  /* Controls PHY frequency operation selection */
  if (HSE_VALUE == 12000000) /* HSE = 12MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x0 << 1);
  }
  else if (HSE_VALUE == 12500000) /* HSE = 12.5MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x2 << 1);
  }
  else if (HSE_VALUE == 16000000) /* HSE = 16MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x3 << 1);
  }

  else if (HSE_VALUE == 24000000) /* HSE = 24MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x4 << 1);
  }
  else if (HSE_VALUE == 25000000) /* HSE = 25MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x5 << 1);
  }
  else if (HSE_VALUE == 32000000) /* HSE = 32MHz */
  {
    USB_HS_PHYC->USB_HS_PHYC_PLL = (uint32_t)(0x7 << 1);
  }

  /* Control the tuning interface of the High Speed PHY */
  USB_HS_PHYC->USB_HS_PHYC_TUNE |= USB_HS_PHYC_TUNE_VALUE;

  /* Enable PLL internal PHY */
  USB_HS_PHYC->USB_HS_PHYC_PLL |= USB_HS_PHYC_PLL_PLLEN;

  /* 2ms Delay required to get internal phy clock stable */
  HAL_Delay(2);
}
#endif


//static void set_rx_fifo(USB_OTG_GlobalTypeDef *USBx, uint16_t size)
//{
//  USBx->GRXFSIZ = size;
//}

//static void set_tx_fifo(USB_OTG_GlobalTypeDef *USBx, uint8_t ep, uint16_t offset, uint16_t size)
//{
//  if(ep == 0){
//    USBx->DIEPTXF0_HNPTXFSIZ = (uint32_t)(((uint32_t)size << 16) | offset);
//  }else{
//    USBx->DIEPTXF[ep - 1] = (uint32_t)(((uint32_t)size << 16) | offset);
//  }
//}

void tusb_close_device(tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef* USBx = dev->handle;
  USBx->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
  
  uint32_t i;
  /* Clear Pending interrupt */
  for (i = 0; i < EP_NUM ; i++){
    USBx_INEP(i)->DIEPINT  = 0xFF;
    USBx_OUTEP(i)->DOEPINT  = 0xFF;
  }
  USBx_DEVICE->DAINT = 0xFFFFFFFF;
  /* Clear interrupt masks */
  USBx_DEVICE->DIEPMSK  = 0;
  USBx_DEVICE->DOEPMSK  = 0;
  USBx_DEVICE->DAINTMSK = 0;

  /* Flush the FIFO */
  flush_rx(USBx);
  flush_tx(USBx ,  0x10 );
  
  // disconnect
  USBx_DEVICE->DCTL |= USB_OTG_DCTL_SDIS ;
  
  if(USBx == USB_OTG_FS){
    __HAL_RCC_USB_OTG_FS_CLK_DISABLE();
    NVIC_DisableIRQ(OTG_FS_IRQn);
    // maybe need de-init the IOs
  }else if(USBx == USB_OTG_HS){
    __HAL_RCC_USB_OTG_HS_CLK_DISABLE();
    NVIC_DisableIRQ(OTG_HS_IRQn);
  }
}

void tusb_open_device(tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef* USBx = dev->handle;
  uint32_t i;
  
  if(USBx == USB_OTG_FS){
    // Init the FS core
#if defined(OTG_FS_EMBEDDED_PHY)
    // open the OTG FS core
    // 1.  setup IO pins
    __HAL_RCC_GPIOA_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_InitStruct;
  
    /**USB_OTG_FS GPIO Configuration    
    PA8     ------> USB_OTG_FS_SOF
    PA9     ------> USB_OTG_FS_VBUS
    PA10     ------> USB_OTG_FS_ID
    PA11     ------> USB_OTG_FS_DM
    PA12     ------> USB_OTG_FS_DP 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_11|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_OTG_FS;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
#if defined(ENABLE_VBUS_DETECT)
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
#endif

    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();
    NVIC_SetPriority(OTG_FS_IRQn, 0);
    NVIC_EnableIRQ(OTG_FS_IRQn);
    
    
    // 2. Init the core
    /* Select FS Embedded PHY */
    USBx->GUSBCFG |= USB_OTG_GUSBCFG_PHYSEL;
    
    /* Reset after a PHY select and set Host mode */
    Wait_CoreReset(USBx);
    /* Deactivate the power down*/
    USBx->GCCFG = USB_OTG_GCCFG_PWRDWN;
#endif
  }else if(USBx == USB_OTG_HS){
    // Init the HS core
    __HAL_RCC_USB_OTG_HS_CLK_ENABLE();
    NVIC_SetPriority(OTG_HS_IRQn, 0);
    NVIC_EnableIRQ(OTG_HS_IRQn);
    
    // open the OTG HS core
#if defined(OTG_HS_EMBEDDED_PHY)
    USBx->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
    /* Init The UTMI Interface */
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS | USB_OTG_GUSBCFG_ULPIFSLS | USB_OTG_GUSBCFG_PHYSEL);
    /* Select vbus source */
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_ULPIEVBUSD | USB_OTG_GUSBCFG_ULPIEVBUSI);
    /* Select UTMI Interace */
    USBx->GUSBCFG &= ~ USB_OTG_GUSBCFG_ULPI_UTMI_SEL;
    USBx->GCCFG |= USB_OTG_GCCFG_PHYHSEN;
    /* Enables control of a High Speed USB PHY */
    USB_HS_PHYCInit(USBx);
#endif
#if defined(OTG_HS_EXTERNAL_PHY)
    USBx->GCCFG &= ~(USB_OTG_GCCFG_PWRDWN);
    /* Init The ULPI Interface */
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_TSDPS | USB_OTG_GUSBCFG_ULPIFSLS | USB_OTG_GUSBCFG_PHYSEL);
    /* Select vbus source */
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_ULPIEVBUSD | USB_OTG_GUSBCFG_ULPIEVBUSI);
#endif

#if defined(ENABLE_VBUS_DETECT)
    USBx->GUSBCFG |= USB_OTG_GUSBCFG_ULPIEVBUSD;
#endif
    /* Reset after a PHY select  */
    Wait_CoreReset(USBx);
  }

#if defined(ENABLE_DMA)
    USBx->GAHBCFG |= USB_OTG_GAHBCFG_HBSTLEN_2;
    USBx->GAHBCFG |= USB_OTG_GAHBCFG_DMAEN;
#endif
  
    // Force to device mode
    USBx->GUSBCFG &= ~(USB_OTG_GUSBCFG_FHMOD | USB_OTG_GUSBCFG_FDMOD);
    USBx->GUSBCFG |= USB_OTG_GUSBCFG_FDMOD;
  
#if defined(ENABLE_VBUS_DETECT)
    USBx->GCCFG |= USB_OTG_GCCFG_VBDEN;
#else
    USBx->GCCFG &= ~ USB_OTG_GCCFG_VBDEN;
    USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOEN;
    USBx->GOTGCTL |= USB_OTG_GOTGCTL_BVALOVAL;
#endif
  
  USBx_PCGCCTL = 0;
  USBx_DEVICE->DCFG |= DCFG_FRAME_INTERVAL_80;
  
  
  USBx_DEVICE->DCFG |= USBx == USB_OTG_FS ? OTG_FS_SPEED : OTG_HS_SPEED;
  
  flush_tx(USBx, 0x10);
  flush_rx(USBx);
  USBx_DEVICE->DIEPMSK = 0;
  USBx_DEVICE->DOEPMSK = 0;
  USBx_DEVICE->DAINT = 0xFFFFFFFF;
  USBx_DEVICE->DAINTMSK = 0;
  
  uint32_t ep_count = USBx == USB_OTG_FS ? USB_OTG_FS_MAX_EP_NUM : USB_OTG_HS_MAX_EP_NUM;
  
  for (i = 0; i < ep_count ; i++){
    if ((USBx_INEP(i)->DIEPCTL & USB_OTG_DIEPCTL_EPENA) == USB_OTG_DIEPCTL_EPENA){
      USBx_INEP(i)->DIEPCTL = (USB_OTG_DIEPCTL_EPDIS | USB_OTG_DIEPCTL_SNAK);
    }else{
      USBx_INEP(i)->DIEPCTL = 0;
    }
    USBx_INEP(i)->DIEPINT = 0xFF;
    USBx_INEP(i)->DIEPCTL &= ~USB_OTG_DIEPCTL_STALL;
    
    if ((USBx_OUTEP(i)->DOEPCTL & USB_OTG_DOEPCTL_EPENA) == USB_OTG_DOEPCTL_EPENA){
      USBx_OUTEP(i)->DOEPCTL = (USB_OTG_DOEPCTL_EPDIS | USB_OTG_DOEPCTL_SNAK);
    }else{
      USBx_OUTEP(i)->DOEPCTL = 0;
    }      
    USBx_OUTEP(i)->DOEPINT = 0xFF;
    USBx_OUTEP(i)->DOEPCTL &= ~USB_OTG_DOEPCTL_STALL;
  }
    
  USBx_DEVICE->DIEPMSK &= ~(USB_OTG_DIEPMSK_TXFURM);
  
  // disable global int
  USBx->GAHBCFG &= ~USB_OTG_GAHBCFG_GINT;
  
  USBx->GINTMSK = 0;
  USBx->GINTSTS = 0xBFFFFFFF;
  
  
  
  //TODO: support LPM, BCD feature
 
#if defined(ENABLE_DMA)
    USBx_DEVICE->DTHRCTL = (USB_OTG_DTHRCTL_TXTHRLEN_6 | USB_OTG_DTHRCTL_RXTHRLEN_6);
    USBx_DEVICE->DTHRCTL |= (USB_OTG_DTHRCTL_RXTHREN | USB_OTG_DTHRCTL_ISOTHREN | USB_OTG_DTHRCTL_NONISOTHREN);
    i = USBx_DEVICE->DTHRCTL;
#else
    USBx->GINTMSK |= USB_OTG_GINTMSK_RXFLVLM;
#endif

  /* Enable interrupts matching to the Device mode ONLY */
  USBx->GINTMSK |= (USB_OTG_GINTMSK_USBSUSPM | USB_OTG_GINTMSK_USBRST |
                    USB_OTG_GINTMSK_ENUMDNEM | USB_OTG_GINTMSK_IEPINT |
                    USB_OTG_GINTMSK_OEPINT   | USB_OTG_GINTMSK_IISOIXFRM|
                    USB_OTG_GINTMSK_PXFRM_IISOOXFRM | USB_OTG_GINTMSK_WUIM
#if defined(ENABLE_VBUS_DETECT)
              | (USB_OTG_GINTMSK_SRQIM | USB_OTG_GINTMSK_OTGINT)
#endif
                    );
  
  USBx_DEVICE->DCTL &= ~USB_OTG_DCTL_SDIS;
  USBx->GAHBCFG |= USB_OTG_GAHBCFG_GINT;
}

void tusb_ep_tx_handler(tusb_device_t* dev, uint8_t ep);
void tusb_fifo_empty(tusb_device_t* dev, uint8_t EPn);
void tusb_setup_handler(tusb_device_t* dev);
void tusb_read_data(tusb_device_t* dev, void* buf, uint32_t len);

void otg_handler(tusb_device_t* dev)
{
  USB_OTG_GlobalTypeDef *USBx = dev->handle;
  uint32_t MAX_EP_NUM = USBx == USB_OTG_FS ? USB_OTG_FS_MAX_EP_NUM : USB_OTG_HS_MAX_EP_NUM;
  
#define  INTR()   (USBx->GINTSTS & USBx->GINTMSK)
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
              if(dev->rx0_callback){
                dev->rx0_callback(dev);
                dev->rx0_callback = 0;
              }
              dev->Ep[0].rx_buf = 0;
            }else{
              if(tusb_on_rx_done(dev, ep, dev->Ep[ep].rx_buf, dev->Ep[ep].rx_count) == 0){
                dev->Ep[ep].rx_count = 0;
                set_rx_valid(dev, ep);
              }else{
                dev->Ep[ep].rx_count = dev->Ep[ep].rx_size;
              }
            }
          }
          if(( epint & USB_OTG_DOEPINT_STUP) == USB_OTG_DOEPINT_STUP){
            // Do it in USB_OTG_GINTSTS_RXFLVL interrupt
            tusb_setup_handler(dev);
          }
          // clear all interrupt flags
          USBx_OUTEP(ep)->DOEPINT = epint;
          if(ep == 0){
            set_rx_valid(dev, 0);
          }
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
            tusb_ep_tx_handler(dev, ep);
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
#if defined(ENABLE_DMA)
      USBx_OUTEP(0)->DOEPDMA = (uint32_t)&dev->setup;
      /* EP enable */
      USBx_OUTEP(0)->DOEPCTL = 0x80008000;
#endif
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
            tusb_read_data(dev, ep->rx_buf + ep->rx_count, len);
            ep->rx_count += len;
          }else{
            // drop the data because no memory to handle them
            tusb_read_data(dev,0, len);
          }
        }else if(((sts & USB_OTG_GRXSTSP_PKTSTS) >> 17) ==  STS_SETUP_UPDT){
          // copy setup packet
          tusb_read_data(dev, &dev->setup, len);
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


#if defined(USB_OTG_FS)
extern tusb_device_t tusb_dev_otg_fs;
void OTG_FS_IRQHandler(void)
{
  otg_handler(&tusb_dev_otg_fs);
}
#endif


#if defined(USB_OTG_HS)
extern tusb_device_t tusb_dev_otg_hs;
void OTG_HS_IRQHandler(void)
{
  otg_handler(&tusb_dev_otg_hs);
}
#endif




