#include "teeny_usb_host.h"



void tusb_host_init_channel(tusb_host_t* host, uint8_t hc_num, uint8_t dev_addr, uint8_t ep_addr, uint8_t ep_type, uint16_t mps);

void tusb_host_deinit_channel(tusb_host_t* host, uint8_t hc_num);

uint8_t  tusb_otg_host_get_free_ch(tusb_host_t* host);

uint32_t tusb_otg_host_xfer_data(tusb_host_t* host, uint8_t hc_num, uint8_t is_data, uint8_t* data, uint32_t len);

int tusb_pipe_open(tusb_host_t* host, tusb_pipe_t* pipe, uint8_t dev_addr, uint8_t ep_addr, uint8_t ep_type, uint16_t mps)
{
  uint8_t hc_num = tusb_otg_host_get_free_ch(host);
  if(hc_num < MAX_HC_NUM){
    pipe->host = host;
    pipe->hc_num = hc_num;
    pipe->dev_addr = dev_addr;
    pipe->ep_addr = ep_addr;
    tusb_host_init_channel(host, hc_num, dev_addr, ep_addr, ep_type, mps);
    return 0;
  }
  return -1;
}

int tusb_pipe_close(tusb_pipe_t* pipe)
{
  if(pipe->host && pipe->hc_num < MAX_HC_NUM){
    tusb_host_deinit_channel(pipe->host, pipe->hc_num);
    pipe->host = 0;
    pipe->hc_num = 0xff;
  }
  return 0;
}

void tusb_pipe_setup(tusb_pipe_t* pipe, tusb_setup_packet* setup)
{
  tusb_otg_host_xfer_data(pipe->host, pipe->hc_num, 0, (uint8_t*)setup, 8);
}

void tusb_pipe_xfer_data(tusb_pipe_t* pipe, void* data, uint32_t len)
{
  tusb_otg_host_xfer_data(pipe->host, pipe->hc_num, 0, (uint8_t*)data, len);
}

