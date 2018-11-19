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


#define  INTERFACE_CNT   7
#define  MAX_EP          7

struct{
  uint8_t  recv_buf[64];
  uint32_t recv_count;
}interface_buffer[INTERFACE_CNT];

void tusb_on_tx_done(tusb_device_t* dev, uint8_t EPn)
{
  if(EPn > 0 && EPn <= MAX_EP){
    set_rx_valid(dev, EPn);
  }
}

int tusb_on_rx_done(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len)
{
  if(EPn > 0 && EPn <= MAX_EP){
    EPn--;
    interface_buffer[EPn].recv_count = len;
    return len;
  }
  return 0;
}

void tusb_reconfig(tusb_device_t* dev)
{
  uint32_t i;
  CDC7_TUSB_INIT(dev);
  for(i=0;i<INTERFACE_CNT;i++){
    tusb_set_recv_buffer(dev, i+1, interface_buffer[i].recv_buf, CDC7_rxEpMaxSize[i+1]);
  }
}

tusb_device_t tusb_dev;
void delay_ms(uint32_t ms)
{
  uint32_t i,j;
  for(i=0;i<ms;++i)
    for(j=0;j<20;++j);
}
int main(void)
{
  tusb_close_device(&tusb_dev);
  
  delay_ms(100);
  
  tusb_open_device(&tusb_dev);
  
  while(1){
    int i;
    for(i=0;i<INTERFACE_CNT;++i){
      uint32_t recv_count = interface_buffer[i].recv_count;
      uint8_t* buf = interface_buffer[i].recv_buf;
      if(recv_count){
        for(int j=0;j<recv_count;j++){
          buf[j]+= (i+1);
        }
        tusb_send_data(&tusb_dev, i+1, buf, recv_count);
        interface_buffer[i].recv_count = 0;
      }
    }
  }
}

