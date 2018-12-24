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

#include "teeny_usb.h"
#include "string.h"


#define  RX_EP   PCD_ENDP2
#define  TX_EP   PCD_ENDP1

uint8_t buf[4096];
__IO uint32_t recv_count = 0;


#define  RX_EP1   PCD_ENDP4
#define  TX_EP1   PCD_ENDP3

uint8_t buf1[4096];
__IO uint32_t recv_count1 = 0;




void delay_ms(uint32_t ms)
{
  uint32_t i,j;
  for(i=0;i<ms;++i)
    for(j=0;j<20;++j);
}

#if defined(USB_OTG_FS)
tusb_host_t tusb_host_otg_fs;
tusb_device_t tusb_dev_otg_fs;
#endif
#if defined(USB_OTG_HS)
tusb_host_t tusb_host_otg_hs;
tusb_device_t tusb_dev_otg_hs;
#endif

int main(void)
{
  tusb_host_t* host;
#if defined(USB_OTG_HS)
  SetUSB(&tusb_host_otg_hs, USB_OTG_HS);
  host = &tusb_host_otg_hs;
#endif
#if defined(USB_OTG_FS)
  SetUSB(&tusb_host_otg_fs, USB_OTG_FS);
  host = &tusb_host_otg_fs;
#endif
  tusb_close_host(host);
  delay_ms(100);  
  tusb_open_host(host);
  while(1){
  }
}

// include the descriptors here instead of add to project
#include "teeny_usb_desc.c"
