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
#include "string.h"
#include "tiny_usb_desc.c"

#define  RX_EP   PCD_ENDP2
#define  TX_EP   PCD_ENDP1

uint8_t buf[4096];
__IO uint32_t recv_count = 0;


#define  RX_EP1   PCD_ENDP4
#define  TX_EP1   PCD_ENDP3

uint8_t buf1[4096];
__IO uint32_t recv_count1 = 0;

// if data tx done, set rx valid again
void tusb_on_tx_done(tusb_device_t* dev, uint8_t EPn)
{
  if(EPn == TX_EP){
    set_rx_valid(dev, RX_EP);
  }else if(EPn == TX_EP1){
    set_rx_valid(dev, RX_EP1);
  }
}

int tusb_on_rx_done(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len)
{
  if(EPn == RX_EP){
    recv_count = len;
    if(recv_count == 0){
      // recv 0 length packet, no data need process
      return 0;
    }
    // otherwise, return -1 means data need process, recv buffer is busy
    return -1;
  }else if(EPn == RX_EP1){
    recv_count1 = len;
    return recv_count1;
  }
  return 0;
}
uint32_t get_max_in_packet_size(PCD_TypeDef* USBx, uint8_t EPn);
void tusb_reconfig(tusb_device_t* dev)
{
  // call the BULK device init macro
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
  INIT_EP_BiDirection(dev, PCD_ENDP0, BULK_EP0_TYPE, BULK_EP0_TX_SIZE);
  SET_RX_ADDR(dev, PCD_ENDP0, BULK_EP0_RX_ADDR, 512);
  SET_TX_ADDR(dev, PCD_ENDP0, 512, 256);
  
  INIT_EP_Tx(dev, PCD_ENDP1, BULK_EP1_TYPE, BULK_EP3_TX_SIZE);
  SET_TX_ADDR(dev, PCD_ENDP1, 512+256*1, 256);
  
  INIT_EP_Rx(dev, PCD_ENDP2, BULK_EP2_TYPE, BULK_EP4_RX_SIZE);
  
  INIT_EP_Tx(dev, PCD_ENDP3, BULK_EP3_TYPE, BULK_EP3_TX_SIZE);
  SET_TX_ADDR(dev, PCD_ENDP3, 512+256*2, 256);
  
  INIT_EP_Rx(dev, PCD_ENDP4, BULK_EP4_TYPE, BULK_EP4_RX_SIZE);
  
  memset(dev, 0, DEV_SIZE);
  dev->status = BULK_DEV_STATUS;
  dev->rx_max_size = BULK_rxEpMaxSize;
  dev->tx_max_size = BULK_txEpMaxSize;
  dev->descriptors = &BULK_descriptors;
#else
  BULK_TUSB_INIT(dev);
#endif
  
  // setup recv buffer for rx end point
  tusb_set_recv_buffer(dev, RX_EP, buf, sizeof(buf));
  tusb_set_recv_buffer(dev, RX_EP1, buf1, sizeof(buf1));
  
#if defined(USB_OTG_FS) || defined(USB_OTG_HS)  
  // OTG core need enable rx ep after buffer set
  set_rx_valid(dev, RX_EP);
  set_rx_valid(dev, RX_EP1);
#endif
}

void delay_ms(uint32_t ms)
{
  uint32_t i,j;
  for(i=0;i<ms;++i)
    for(j=0;j<20;++j);
}

#if defined(USB_OTG_FS)
tusb_device_t tusb_dev_otg_fs;
#endif
#if defined(USB_OTG_HS)
tusb_device_t tusb_dev_otg_hs;
#endif
tusb_device_t tusb_dev;

int main(void)
{
  tusb_device_t* dev = &tusb_dev;
#if defined(USB_OTG_HS)
  tusb_dev_otg_hs.handle = USB_OTG_HS;
  dev = &tusb_dev_otg_hs;
#endif
#if defined(USB_OTG_FS)
  tusb_dev_otg_fs.handle = USB_OTG_FS;
  dev = &tusb_dev_otg_fs;
#endif
  tusb_close_device(dev);
  delay_ms(100);  
  tusb_open_device(dev);
  while(1){
    if(recv_count){
      // every data plus 1 and echo back
      for(int i=0;i<recv_count;i++){
        buf[i]++;
      }
      tusb_send_data(dev, TX_EP, buf, recv_count);
      recv_count = 0; 
    }
    
    if(recv_count1){
      // every data plus 1 and echo back
      for(int i=0;i<recv_count1;i++){
        buf1[i]+=2;
      }
      tusb_send_data(dev, TX_EP1, buf1, recv_count1);
      recv_count1 = 0; 
    }
  }
}


