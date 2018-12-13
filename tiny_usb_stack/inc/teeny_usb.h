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

#ifndef __CDC_H__
#define __CDC_H__

#include "teeny_usb_platform.h"

typedef struct _tusb_setup_packet{
  uint8_t  bmRequestType;
  uint8_t  bRequest;
  uint16_t wValue;
  uint16_t wIndex;
  uint16_t wLength;
} tusb_setup_packet;

#define LO_BYTE(x)   (uint8_t)(x)
#define HI_BYTE(x)  (uint8_t)((x)>>8)

typedef struct _tusb_ep_data
{
  const uint8_t*  tx_buf;       // tx buffer
  uint8_t*        rx_buf;       // rx buffer
  uint16_t        tx_size;      // data remain to transfer
  uint16_t        rx_size;      // rx buffer size
  uint16_t        rx_count;     // current received data
  uint16_t        tx_last_size; // last tx data length
#if defined(USB)
  uint32_t        tx_pushed;    // data packet number in the PMA buffer
#endif
}tusb_ep_data;

typedef const uint8_t* desc_t;

typedef struct _tusb_descriptors
{
  desc_t  device;
  desc_t  config;
  const desc_t*  strings;
  uint32_t string_cnt;
#if defined(HAS_WCID)
  desc_t  wcid_desc;
  desc_t  wcid_properties;
#endif
}tusb_descriptors;


typedef struct _tusb_device tusb_device_t;
typedef void(*tusb_callback_t)(tusb_device_t* dev);
struct _tusb_device{
  uint8_t   config;                       // device config
  uint8_t   addr;                         // device addr
  uint8_t   alt_cfg;                      // device alg config
  uint8_t   padding;                      // padding
  uint16_t  status;                       // device status
  tusb_callback_t status_callback;        // status transfer done callback
  tusb_callback_t rx0_callback;           // ep0 rx callback
#if defined(NEED_MAX_PACKET)
  const uint8_t* rx_max_size;             // RX max size buffer
  const uint8_t* tx_max_size;             // TX max size buffer
#endif
  tusb_setup_packet  setup;               // setup packet buffer
  tusb_ep_data   Ep[EP_NUM];              // end point
  const tusb_descriptors*  descriptors;   // device descriptors, can be override at runtime
#if defined(USB_CORE_HANDLE_TYPE)
  USB_CORE_HANDLE_TYPE  handle;           // USB hardware handle
#endif
};


#if defined(USB_CORE_HANDLE_TYPE)
#define  TUSB_DEVICE_SIZE   (sizeof(tusb_device_t) - sizeof(USB_CORE_HANDLE_TYPE))
#else
#define  TUSB_DEVICE_SIZE   sizeof(tusb_device_t)
#endif



// open USB device, implement by platform
void tusb_open_device(tusb_device_t* dev);

// close USB device, implement by platform
void tusb_close_device(tusb_device_t* dev);

// return 0 for success, -1 for end point not ready or data is on going
int tusb_send_data(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len);

// set the recv buffer for end point, should be called in tusb_reconfig
// param  len must large then the end point packet size
// return value: 0 - means success
//              -1 - means fail
int tusb_set_recv_buffer(tusb_device_t* dev, uint8_t EPn, void* data, uint16_t len);

// set rx valid, when tusb_on_rx_done return value is not 0, the rx end point will hang
// use the method to enable it again
void set_rx_valid(tusb_device_t* dev, uint8_t EPn);

//////////////////////////////////
// user callback functions
//////////////////////////////////

// called when data transfer done
// WEAK function, default do nothing
void tusb_on_tx_done(tusb_device_t* dev, uint8_t EPn);

// called when data receive done
// there are two conditions to trigger this callback
// 1. Received data is large or equal to the buffer length set by tusb_set_recv_buffer
// 2. Received data packed size is less than the end point max packet size
// return value:  0 - means received data processed, the previous set received buffer can be used
//        otherwise - means the data will be processed later, call set_rx_valid to enable receive again
//        in case of ISO out endpoint, return 0 will use current receive buffer to rx data again
//                                     otherwise the follow data will be dropped untill call set_rx_valid
// WEAK function, default return 0
int tusb_on_rx_done(tusb_device_t* dev, uint8_t EPn, const void* data, uint16_t len);

// called when USB device reset
// Setup the end point and device initial status here
void tusb_reconfig(tusb_device_t* dev);

// called when got class specified request
// WEAK function, default send a zero length IN packet (which means status IN)
void tusb_class_request(tusb_device_t* dev, tusb_setup_packet* setup_req);

// get device report descripor when need
// WEAK function, default return 0, set length to 0
const uint8_t* tusb_get_report_descriptor(tusb_device_t* dev, tusb_setup_packet *req, uint16_t* len);


#endif
