/*
 * Name   :  tiny_usb_init.h
 * Author :  admin@xtoolbox.org
 * Date   :  2018-12-13 16:00:10
 * Desc   :  This file is auto generate by the tiny_usb script tool
 *           Visit https://github.com/xtoolbox/tiny_usb for more info
 */

/*
  Input source name:  ..\tiny_usb_stack\descriptor_demo\demo.lua  
  Content type is lua script:
  ------------- lua script begin ------------
-- DEMO USB descriptor for teeny USB stack
return {
-- Demo descriptor of Bulk device
Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb bulk demo",
    strSerial = "tu123456",
    idVendor = 0x4322,
    idProduct = 0x4321,
    prefix = "BULK",
    bMaxPacketSize = 64,
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        --Interface{
        --    WCID = WinUSB,
        --    EndPoint(IN(1),  BulkDouble, 64),
        --    EndPoint(OUT(2), BulkDouble, 64),
        --    strInterface = "teenyUsb1",
        --},
        Interface{
            WCID = WinUSB,
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(2), BulkDouble, 64),
            strInterface = "TeenyUsb2",
        },
   }
},


Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb iso demo",
    strSerial = "tu123456",
    idVendor = 0x4322,
    idProduct = 0x4322,
    prefix = "ISO",
    bMaxPacketSize = 64,
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        Interface{
            WCID = WinUSB,
            EndPoint(IN(1),  ISO, 64),
            EndPoint(OUT(2), ISO, 64),
            strInterface = "TeenyUsb2",
        },
   }
},

-- Demo descriptor of CDC device
Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb cdc demo",
    strSerial = "tu123456",
    idVendor = 0x03EB,    -- VID PID for Ateml CDC
    idProduct = 0x6124,
    prefix = "CDC",
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        CDC_ACM{
            CtrlEp =  EndPoint(IN(3),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(1),  BulkDouble, 64),
            WriteEp = EndPoint(OUT(2), BulkDouble, 64),
        },
    },
},

-- Demo descriptor of 7 CDC device
Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb cdc7 demo",
    strSerial = "tu123456",
    idVendor = 0x2017,   -- Win10 can drive the multiple CDC, VID PID can be any one
    idProduct = 0x0926,
    prefix = "CDC7",
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        CDC_ACM{
            CtrlEp =  EndPoint(IN(8),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(1),  BulkDouble, 64),
            WriteEp = EndPoint(OUT(1), BulkDouble, 64),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(9),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(2),  BulkDouble, 32),
            WriteEp = EndPoint(OUT(2), BulkDouble, 32),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(10),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(3),  BulkDouble, 32),
            WriteEp = EndPoint(OUT(3), BulkDouble, 32),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(11),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(4),  BulkDouble, 32),
            WriteEp = EndPoint(OUT(4), BulkDouble, 32),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(12),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(5),  BulkDouble, 16),
            WriteEp = EndPoint(OUT(5), BulkDouble, 16),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(13),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(6),  BulkDouble, 16),
            WriteEp = EndPoint(OUT(6), BulkDouble, 16),
        },
        CDC_ACM{
            CtrlEp =  EndPoint(IN(14),  Interrupt,  8, 1),
            ReadEp =  EndPoint(IN(7),  BulkDouble, 16),
            WriteEp = EndPoint(OUT(7), BulkDouble, 16),
        },
    },
},

-- Demo descriptor of HID device
Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb HID demo",
    strSerial = "tu123456",
    idVendor = 0x2017,
    idProduct = 0x0927,
    prefix = "HID",
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        USB_HID{
            isKey = false,
            isMouse = false,
            isBoot = false,
            ReadEp = EndPoint(IN(1),  Interrupt, 64),
            WriteEp = EndPoint(OUT(1), Interrupt, 64),
            report = HID_InOut(64),
        },
   }
},

-- Demo descriptor of 7 HID device
Device {
    strManufacture = "teeny usb",
    strProduct = "teeny usb 7 HID demo",
    strSerial = "tu123456",
    idVendor = 0x2017,
    idProduct = 0x0928,
    prefix = "HID7",
    Config {
        USB_HID{
            ReadEp = EndPoint(IN(1),  Interrupt, 64),
            WriteEp = EndPoint(OUT(1), Interrupt, 64),
            report = HID_InOut(64),
        },
        USB_HID{
            ReadEp = EndPoint(IN(2),  Interrupt, 32),
            WriteEp = EndPoint(OUT(2), Interrupt, 32),
            report = HID_InOut(32),
        },
        USB_HID{
            ReadEp = EndPoint(IN(3),  Interrupt, 32),
            WriteEp = EndPoint(OUT(3), Interrupt, 32),
            report = HID_InOut(32),
        },
        USB_HID{
            ReadEp = EndPoint(IN(4),  Interrupt, 32),
            WriteEp = EndPoint(OUT(4), Interrupt, 32),
            report = HID_InOut(32),
        },
        USB_HID{
            ReadEp = EndPoint(IN(5),  Interrupt, 16),
            WriteEp = EndPoint(OUT(5), Interrupt, 16),
            report = HID_InOut(16),
        },
        USB_HID{
            ReadEp = EndPoint(IN(6),  Interrupt, 16),
            WriteEp = EndPoint(OUT(6), Interrupt, 16),
            report = HID_InOut(16),
        },
        USB_HID{
            ReadEp = EndPoint(IN(7),  Interrupt, 16),
            WriteEp = EndPoint(OUT(7), Interrupt, 16),
            report = HID_InOut(16),
        },
   }
},
}  

  ------------- lua script end   ------------
 */
#ifndef ____TINY_USB_STACK_DESCRIPTOR_DEMO_TINY_USB_INIT_H_
#define ____TINY_USB_STACK_DESCRIPTOR_DEMO_TINY_USB_INIT_H_// include this file in "usbd_conf.h"

// forward declare the tusb_descriptors struct
typedef struct _tusb_descriptors tusb_descriptors;
/////////////////////////////////////////////////////////////////////
//// EndPoint for device1 define begin
/////////////////////////////////////////////////////////////////////
#define BULK_VID                                            0x4322
#define BULK_PID                                            0x4321
#define BULK_STRING_COUNT                                   (5)
// Endpoint usage:
#ifdef BULK_BTABLE_ADDRESS
#undef BULK_BTABLE_ADDRESS
#endif
#define BULK_BTABLE_ADDRESS                                 (0)
#define BULK_MAX_EP                                         (2)
#define BULK_EP_NUM                                         (BULK_MAX_EP + 1)
#define BULK_EP_BUF_DESC_TABLE_SIZE                         (8)

// PMA buffer reserved for buffer description table  
#define BULK_USB_BUF_START                                  (BULK_EP_BUF_DESC_TABLE_SIZE * BULK_EP_NUM)

// EndPoints 0 defines
#define BULK_EP0_RX_SIZE                                    (64)
#define BULK_EP0_RX_ADDR                                    (BULK_USB_BUF_START + 0)
#define BULK_EP0_TX_SIZE                                    (64)
#define BULK_EP0_TX_ADDR                                    (BULK_USB_BUF_START + 64)
#define BULK_EP0_TYPE                                       USB_EP_CONTROL

// EndPoints 1 defines
#define BULK_EP1_TX_SIZE                                    (64)
#define BULK_EP1_TX0_ADDR                                   (BULK_USB_BUF_START + 128)
#define BULK_EP1_TX1_ADDR                                   (BULK_USB_BUF_START + 192)
#define BULK_EP1_TYPE                                       USB_EP_BULK

// EndPoints 2 defines
#define BULK_EP2_RX_SIZE                                    (64)
#define BULK_EP2_RX0_ADDR                                   (BULK_USB_BUF_START + 256)
#define BULK_EP2_RX1_ADDR                                   (BULK_USB_BUF_START + 320)
#define BULK_EP2_TYPE                                       USB_EP_BULK


// Endpoint define for OTG core
#define BULK_OTG_MAX_OUT_SIZE                               (64)
#define BULK_OTG_CONTROL_EP_NUM                             (1)
#define BULK_OTG_OUT_EP_NUM                                 (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33
#define BULK_OTG_RX_FIFO_SIZE                               (256)
#define BULK_OTG_RX_FIFO_ADDR                               (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define BULK_EP0_TX_FIFO_ADDR                               (256)
#define BULK_EP0_TX_FIFO_SIZE                               (BULK_EP0_TX_SIZE * 7)
#define BULK_EP1_TX_FIFO_ADDR                               (704)
#define BULK_EP1_TX_FIFO_SIZE                               (BULK_EP1_TX_SIZE * 7)

// EndPoint max packed sizes
extern const uint8_t BULK_txEpMaxSize[];
#define BULK_TXEP_MAX_SIZE                                  \
const uint8_t BULK_txEpMaxSize[] = \
{BULK_EP0_TX_SIZE, BULK_EP1_TX_SIZE, 0, };
extern const uint8_t BULK_rxEpMaxSize[];
#define BULK_RXEP_MAX_SIZE                                  \
const uint8_t BULK_rxEpMaxSize[] = \
{BULK_EP0_RX_SIZE, 0, BULK_EP2_RX_SIZE, };

// EndPoints init function for USB FS core
#define BULK_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, BULK_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, BULK_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, BULK_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, BULK_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_TxDouble(dev, PCD_ENDP1, BULK_EP1_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP1, BULK_EP1_TX0_ADDR, BULK_EP1_TX1_ADDR);  \
    SET_DBL_TX_CNT(dev, PCD_ENDP1, 0);     \
    /* Init ep2 */ \
    INIT_EP_RxDouble(dev, PCD_ENDP2, BULK_EP2_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP2, BULK_EP2_RX0_ADDR, BULK_EP2_RX1_ADDR);     \
    SET_DBL_RX_CNT(dev, PCD_ENDP2, BULK_EP2_RX_SIZE);     \
  }while(0)


// EndPoints init function for USB OTG core
#define BULK_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, BULK_OTG_RX_FIFO_ADDR, BULK_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, BULK_EP0_TYPE, BULK_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, BULK_EP0_TX_FIFO_ADDR, BULK_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, BULK_EP0_TYPE, BULK_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, BULK_EP1_TYPE, BULK_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, BULK_EP1_TX_FIFO_ADDR, BULK_EP1_TX_FIFO_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_Rx(dev, PCD_ENDP2, BULK_EP2_TYPE, BULK_EP2_RX_SIZE);  \
  }while(0)


#if defined(USB)
#define BULK_TUSB_INIT_EP(dev) BULK_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define BULK_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = BULK_DEV_STATUS;         \
    dev->rx_max_size = BULK_rxEpMaxSize;         \
    dev->tx_max_size = BULK_txEpMaxSize;         \
    dev->descriptors = &BULK_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define BULK_TUSB_INIT_EP(dev) BULK_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define BULK_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = BULK_DEV_STATUS;         \
    dev->descriptors = &BULK_descriptors;         \
  }while(0)

#endif

#define BULK_TUSB_INIT(dev) \
  do{\
    BULK_TUSB_INIT_EP(dev);   \
    BULK_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if BULK_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  BULK_EP_NUM
#endif


// Enable double buffer related code
#define  HAS_DOUBLE_BUFFER


// Enable WCID related code
#define  HAS_WCID


#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif

// Descriptor declare
#define  BULK_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t BULK_DeviceDescriptor [18];
#define  BULK_CONFIG_DESCRIPTOR_SIZE  (32)
extern const uint8_t BULK_ConfigDescriptor [32];
#define BULK_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define BULK_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define BULK_DEV_STATUS    ((BULK_DEV_STATUS0) |(BULK_DEV_STATUS1) )

extern const uint8_t* const BULK_StringDescriptors[BULK_STRING_COUNT];
extern const tusb_descriptors BULK_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device1 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device2 define begin
/////////////////////////////////////////////////////////////////////
#define ISO_VID                                             0x4322
#define ISO_PID                                             0x4322
#define ISO_STRING_COUNT                                    (5)
// Endpoint usage:
#ifdef ISO_BTABLE_ADDRESS
#undef ISO_BTABLE_ADDRESS
#endif
#define ISO_BTABLE_ADDRESS                                  (0)
#define ISO_MAX_EP                                          (2)
#define ISO_EP_NUM                                          (ISO_MAX_EP + 1)
#define ISO_EP_BUF_DESC_TABLE_SIZE                          (8)

// PMA buffer reserved for buffer description table  
#define ISO_USB_BUF_START                                   (ISO_EP_BUF_DESC_TABLE_SIZE * ISO_EP_NUM)

// EndPoints 0 defines
#define ISO_EP0_RX_SIZE                                     (64)
#define ISO_EP0_RX_ADDR                                     (ISO_USB_BUF_START + 0)
#define ISO_EP0_TX_SIZE                                     (64)
#define ISO_EP0_TX_ADDR                                     (ISO_USB_BUF_START + 64)
#define ISO_EP0_TYPE                                        USB_EP_CONTROL

// EndPoints 1 defines
#define ISO_EP1_TX_SIZE                                     (64)
#define ISO_EP1_TX0_ADDR                                    (ISO_USB_BUF_START + 128)
#define ISO_EP1_TX1_ADDR                                    (ISO_USB_BUF_START + 192)
#define ISO_EP1_TYPE                                        USB_EP_ISOCHRONOUS

// EndPoints 2 defines
#define ISO_EP2_RX_SIZE                                     (64)
#define ISO_EP2_RX0_ADDR                                    (ISO_USB_BUF_START + 256)
#define ISO_EP2_RX1_ADDR                                    (ISO_USB_BUF_START + 320)
#define ISO_EP2_TYPE                                        USB_EP_ISOCHRONOUS


// Endpoint define for OTG core
#define ISO_OTG_MAX_OUT_SIZE                                (64)
#define ISO_OTG_CONTROL_EP_NUM                              (1)
#define ISO_OTG_OUT_EP_NUM                                  (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33
#define ISO_OTG_RX_FIFO_SIZE                                (256)
#define ISO_OTG_RX_FIFO_ADDR                                (0)
// Sum of IN ep max packet size is 128
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define ISO_EP0_TX_FIFO_ADDR                                (256)
#define ISO_EP0_TX_FIFO_SIZE                                (ISO_EP0_TX_SIZE * 7)
#define ISO_EP1_TX_FIFO_ADDR                                (704)
#define ISO_EP1_TX_FIFO_SIZE                                (ISO_EP1_TX_SIZE * 7)

// EndPoint max packed sizes
extern const uint8_t ISO_txEpMaxSize[];
#define ISO_TXEP_MAX_SIZE                                   \
const uint8_t ISO_txEpMaxSize[] = \
{ISO_EP0_TX_SIZE, ISO_EP1_TX_SIZE, 0, };
extern const uint8_t ISO_rxEpMaxSize[];
#define ISO_RXEP_MAX_SIZE                                   \
const uint8_t ISO_rxEpMaxSize[] = \
{ISO_EP0_RX_SIZE, 0, ISO_EP2_RX_SIZE, };

// EndPoints init function for USB FS core
#define ISO_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, ISO_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, ISO_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, ISO_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, ISO_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_TxDouble(dev, PCD_ENDP1, ISO_EP1_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP1, ISO_EP1_TX0_ADDR, ISO_EP1_TX1_ADDR);  \
    SET_DBL_TX_CNT(dev, PCD_ENDP1, 0);     \
    /* Init ep2 */ \
    INIT_EP_RxDouble(dev, PCD_ENDP2, ISO_EP2_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP2, ISO_EP2_RX0_ADDR, ISO_EP2_RX1_ADDR);     \
    SET_DBL_RX_CNT(dev, PCD_ENDP2, ISO_EP2_RX_SIZE);     \
  }while(0)


// EndPoints init function for USB OTG core
#define ISO_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, ISO_OTG_RX_FIFO_ADDR, ISO_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, ISO_EP0_TYPE, ISO_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, ISO_EP0_TX_FIFO_ADDR, ISO_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, ISO_EP0_TYPE, ISO_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, ISO_EP1_TYPE, ISO_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, ISO_EP1_TX_FIFO_ADDR, ISO_EP1_TX_FIFO_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_Rx(dev, PCD_ENDP2, ISO_EP2_TYPE, ISO_EP2_RX_SIZE);  \
  }while(0)


#if defined(USB)
#define ISO_TUSB_INIT_EP(dev) ISO_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define ISO_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = ISO_DEV_STATUS;         \
    dev->rx_max_size = ISO_rxEpMaxSize;         \
    dev->tx_max_size = ISO_txEpMaxSize;         \
    dev->descriptors = &ISO_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define ISO_TUSB_INIT_EP(dev) ISO_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define ISO_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = ISO_DEV_STATUS;         \
    dev->descriptors = &ISO_descriptors;         \
  }while(0)

#endif

#define ISO_TUSB_INIT(dev) \
  do{\
    ISO_TUSB_INIT_EP(dev);   \
    ISO_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if ISO_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  ISO_EP_NUM
#endif


// Enable iso ep related code
#define  HAS_ISO_EP


// Enable WCID related code
#define  HAS_WCID


#ifndef WCID_VENDOR_CODE
#define  WCID_VENDOR_CODE       0x17
extern const uint8_t WCID_StringDescriptor_MSOS[];
#endif

// Descriptor declare
#define  ISO_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t ISO_DeviceDescriptor [18];
#define  ISO_CONFIG_DESCRIPTOR_SIZE  (32)
extern const uint8_t ISO_ConfigDescriptor [32];
#define ISO_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define ISO_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define ISO_DEV_STATUS    ((ISO_DEV_STATUS0) |(ISO_DEV_STATUS1) )

extern const uint8_t* const ISO_StringDescriptors[ISO_STRING_COUNT];
extern const tusb_descriptors ISO_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device2 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device3 define begin
/////////////////////////////////////////////////////////////////////
#define CDC_VID                                             0x03eb
#define CDC_PID                                             0x6124
#define CDC_STRING_COUNT                                    (4)
// Endpoint usage:
#ifdef CDC_BTABLE_ADDRESS
#undef CDC_BTABLE_ADDRESS
#endif
#define CDC_BTABLE_ADDRESS                                  (0)
#define CDC_MAX_EP                                          (3)
#define CDC_EP_NUM                                          (CDC_MAX_EP + 1)
#define CDC_EP_BUF_DESC_TABLE_SIZE                          (8)

// PMA buffer reserved for buffer description table  
#define CDC_USB_BUF_START                                   (CDC_EP_BUF_DESC_TABLE_SIZE * CDC_EP_NUM)

// EndPoints 0 defines
#define CDC_EP0_RX_SIZE                                     (8)
#define CDC_EP0_RX_ADDR                                     (CDC_USB_BUF_START + 0)
#define CDC_EP0_TX_SIZE                                     (8)
#define CDC_EP0_TX_ADDR                                     (CDC_USB_BUF_START + 8)
#define CDC_EP0_TYPE                                        USB_EP_CONTROL

// EndPoints 1 defines
#define CDC_EP1_TX_SIZE                                     (64)
#define CDC_EP1_TX0_ADDR                                    (CDC_USB_BUF_START + 16)
#define CDC_EP1_TX1_ADDR                                    (CDC_USB_BUF_START + 80)
#define CDC_EP1_TYPE                                        USB_EP_BULK

// EndPoints 2 defines
#define CDC_EP2_RX_SIZE                                     (64)
#define CDC_EP2_RX0_ADDR                                    (CDC_USB_BUF_START + 144)
#define CDC_EP2_RX1_ADDR                                    (CDC_USB_BUF_START + 208)
#define CDC_EP2_TYPE                                        USB_EP_BULK

// EndPoints 3 defines
#define CDC_EP3_TX_SIZE                                     (8)
#define CDC_EP3_TX_ADDR                                     (CDC_USB_BUF_START + 272)
#define CDC_EP3_TYPE                                        USB_EP_INTERRUPT


// Endpoint define for OTG core
#define CDC_OTG_MAX_OUT_SIZE                                (64)
#define CDC_OTG_CONTROL_EP_NUM                              (1)
#define CDC_OTG_OUT_EP_NUM                                  (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33
#define CDC_OTG_RX_FIFO_SIZE                                (256)
#define CDC_OTG_RX_FIFO_ADDR                                (0)
// Sum of IN ep max packet size is 80
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define CDC_EP0_TX_FIFO_ADDR                                (256)
#define CDC_EP0_TX_FIFO_SIZE                                (CDC_EP0_TX_SIZE * 7)
#define CDC_EP1_TX_FIFO_ADDR                                (312)
#define CDC_EP1_TX_FIFO_SIZE                                (CDC_EP1_TX_SIZE * 7)
#define CDC_EP3_TX_FIFO_ADDR                                (760)
#define CDC_EP3_TX_FIFO_SIZE                                (CDC_EP3_TX_SIZE * 7)

// EndPoint max packed sizes
extern const uint8_t CDC_txEpMaxSize[];
#define CDC_TXEP_MAX_SIZE                                   \
const uint8_t CDC_txEpMaxSize[] = \
{CDC_EP0_TX_SIZE, CDC_EP1_TX_SIZE, 0, CDC_EP3_TX_SIZE, };
extern const uint8_t CDC_rxEpMaxSize[];
#define CDC_RXEP_MAX_SIZE                                   \
const uint8_t CDC_rxEpMaxSize[] = \
{CDC_EP0_RX_SIZE, 0, CDC_EP2_RX_SIZE, 0, };

// EndPoints init function for USB FS core
#define CDC_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, CDC_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, CDC_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, CDC_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, CDC_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_TxDouble(dev, PCD_ENDP1, CDC_EP1_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP1, CDC_EP1_TX0_ADDR, CDC_EP1_TX1_ADDR);  \
    SET_DBL_TX_CNT(dev, PCD_ENDP1, 0);     \
    /* Init ep2 */ \
    INIT_EP_RxDouble(dev, PCD_ENDP2, CDC_EP2_TYPE);     \
    SET_DOUBLE_ADDR(dev, PCD_ENDP2, CDC_EP2_RX0_ADDR, CDC_EP2_RX1_ADDR);     \
    SET_DBL_RX_CNT(dev, PCD_ENDP2, CDC_EP2_RX_SIZE);     \
    /* Init ep3 */ \
    INIT_EP_TxOnly(dev, PCD_ENDP3, CDC_EP3_TYPE);       \
    SET_TX_ADDR(dev, PCD_ENDP3, CDC_EP3_TX_ADDR);  \
  }while(0)


// EndPoints init function for USB OTG core
#define CDC_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, CDC_OTG_RX_FIFO_ADDR, CDC_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, CDC_EP0_TYPE, CDC_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, CDC_EP0_TX_FIFO_ADDR, CDC_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, CDC_EP0_TYPE, CDC_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, CDC_EP1_TYPE, CDC_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, CDC_EP1_TX_FIFO_ADDR, CDC_EP1_TX_FIFO_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_Rx(dev, PCD_ENDP2, CDC_EP2_TYPE, CDC_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_Tx(dev, PCD_ENDP3, CDC_EP3_TYPE, CDC_EP3_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP3, CDC_EP3_TX_FIFO_ADDR, CDC_EP3_TX_FIFO_SIZE);  \
  }while(0)


#if defined(USB)
#define CDC_TUSB_INIT_EP(dev) CDC_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define CDC_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_DEV_STATUS;         \
    dev->rx_max_size = CDC_rxEpMaxSize;         \
    dev->tx_max_size = CDC_txEpMaxSize;         \
    dev->descriptors = &CDC_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define CDC_TUSB_INIT_EP(dev) CDC_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define CDC_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC_DEV_STATUS;         \
    dev->descriptors = &CDC_descriptors;         \
  }while(0)

#endif

#define CDC_TUSB_INIT(dev) \
  do{\
    CDC_TUSB_INIT_EP(dev);   \
    CDC_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC_EP_NUM
#endif


// Enable double buffer related code
#define  HAS_DOUBLE_BUFFER


#define  CDC_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t CDC_DeviceDescriptor [18];
#define  CDC_CONFIG_DESCRIPTOR_SIZE  (67)
extern const uint8_t CDC_ConfigDescriptor [67];
#define CDC_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define CDC_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define CDC_DEV_STATUS    ((CDC_DEV_STATUS0) |(CDC_DEV_STATUS1) )

extern const uint8_t* const CDC_StringDescriptors[CDC_STRING_COUNT];
extern const tusb_descriptors CDC_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device3 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device4 define begin
/////////////////////////////////////////////////////////////////////
#define CDC7_VID                                            0x2017
#define CDC7_PID                                            0x0926
#define CDC7_STRING_COUNT                                   (4)
// Endpoint usage:
#ifdef CDC7_BTABLE_ADDRESS
#undef CDC7_BTABLE_ADDRESS
#endif
#define CDC7_BTABLE_ADDRESS                                 (0)
#define CDC7_MAX_EP                                         (7)
#define CDC7_EP_NUM                                         (CDC7_MAX_EP + 1)
#define CDC7_EP_BUF_DESC_TABLE_SIZE                         (8)

// PMA buffer reserved for buffer description table  
#define CDC7_USB_BUF_START                                  (CDC7_EP_BUF_DESC_TABLE_SIZE * CDC7_EP_NUM)

// EndPoints 0 defines
#define CDC7_EP0_RX_SIZE                                    (8)
#define CDC7_EP0_RX_ADDR                                    (CDC7_USB_BUF_START + 0)
#define CDC7_EP0_TX_SIZE                                    (8)
#define CDC7_EP0_TX_ADDR                                    (CDC7_USB_BUF_START + 8)
#define CDC7_EP0_TYPE                                       USB_EP_CONTROL

// EndPoints 1 defines
#define CDC7_EP1_RX_SIZE                                    (64)
#define CDC7_EP1_RX_ADDR                                    (CDC7_USB_BUF_START + 16)
#define CDC7_EP1_TX_SIZE                                    (64)
#define CDC7_EP1_TX_ADDR                                    (CDC7_USB_BUF_START + 80)
#define CDC7_EP1_TYPE                                       USB_EP_BULK

// EndPoints 2 defines
#define CDC7_EP2_RX_SIZE                                    (32)
#define CDC7_EP2_RX_ADDR                                    (CDC7_USB_BUF_START + 144)
#define CDC7_EP2_TX_SIZE                                    (32)
#define CDC7_EP2_TX_ADDR                                    (CDC7_USB_BUF_START + 176)
#define CDC7_EP2_TYPE                                       USB_EP_BULK

// EndPoints 3 defines
#define CDC7_EP3_RX_SIZE                                    (32)
#define CDC7_EP3_RX_ADDR                                    (CDC7_USB_BUF_START + 208)
#define CDC7_EP3_TX_SIZE                                    (32)
#define CDC7_EP3_TX_ADDR                                    (CDC7_USB_BUF_START + 240)
#define CDC7_EP3_TYPE                                       USB_EP_BULK

// EndPoints 4 defines
#define CDC7_EP4_RX_SIZE                                    (32)
#define CDC7_EP4_RX_ADDR                                    (CDC7_USB_BUF_START + 272)
#define CDC7_EP4_TX_SIZE                                    (32)
#define CDC7_EP4_TX_ADDR                                    (CDC7_USB_BUF_START + 304)
#define CDC7_EP4_TYPE                                       USB_EP_BULK

// EndPoints 5 defines
#define CDC7_EP5_RX_SIZE                                    (16)
#define CDC7_EP5_RX_ADDR                                    (CDC7_USB_BUF_START + 336)
#define CDC7_EP5_TX_SIZE                                    (16)
#define CDC7_EP5_TX_ADDR                                    (CDC7_USB_BUF_START + 352)
#define CDC7_EP5_TYPE                                       USB_EP_BULK

// EndPoints 6 defines
#define CDC7_EP6_RX_SIZE                                    (16)
#define CDC7_EP6_RX_ADDR                                    (CDC7_USB_BUF_START + 368)
#define CDC7_EP6_TX_SIZE                                    (16)
#define CDC7_EP6_TX_ADDR                                    (CDC7_USB_BUF_START + 384)
#define CDC7_EP6_TYPE                                       USB_EP_BULK

// EndPoints 7 defines
#define CDC7_EP7_RX_SIZE                                    (16)
#define CDC7_EP7_RX_ADDR                                    (CDC7_USB_BUF_START + 400)
#define CDC7_EP7_TX_SIZE                                    (16)
#define CDC7_EP7_TX_ADDR                                    (CDC7_USB_BUF_START + 416)
#define CDC7_EP7_TYPE                                       USB_EP_BULK


// Endpoint define for OTG core
#define CDC7_OTG_MAX_OUT_SIZE                               (64)
#define CDC7_OTG_CONTROL_EP_NUM                             (1)
#define CDC7_OTG_OUT_EP_NUM                                 (7)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 45
#define CDC7_OTG_RX_FIFO_SIZE                               (256)
#define CDC7_OTG_RX_FIFO_ADDR                               (0)
// Sum of IN ep max packet size is 216
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define CDC7_EP0_TX_FIFO_ADDR                               (256)
#define CDC7_EP0_TX_FIFO_SIZE                               (CDC7_EP0_TX_SIZE * 5)
#define CDC7_EP1_TX_FIFO_ADDR                               (296)
#define CDC7_EP1_TX_FIFO_SIZE                               (CDC7_EP1_TX_SIZE * 5)
#define CDC7_EP2_TX_FIFO_ADDR                               (616)
#define CDC7_EP2_TX_FIFO_SIZE                               (CDC7_EP2_TX_SIZE * 5)
#define CDC7_EP3_TX_FIFO_ADDR                               (776)
#define CDC7_EP3_TX_FIFO_SIZE                               (CDC7_EP3_TX_SIZE * 5)
#define CDC7_EP4_TX_FIFO_ADDR                               (936)
#define CDC7_EP4_TX_FIFO_SIZE                               (CDC7_EP4_TX_SIZE * 5)
#define CDC7_EP5_TX_FIFO_ADDR                               (1096)
#define CDC7_EP5_TX_FIFO_SIZE                               (CDC7_EP5_TX_SIZE * 5)
#define CDC7_EP6_TX_FIFO_ADDR                               (1176)
#define CDC7_EP6_TX_FIFO_SIZE                               (CDC7_EP6_TX_SIZE * 5)
#define CDC7_EP7_TX_FIFO_ADDR                               (1256)
#define CDC7_EP7_TX_FIFO_SIZE                               (CDC7_EP7_TX_SIZE * 5)

// EndPoint max packed sizes
extern const uint8_t CDC7_txEpMaxSize[];
#define CDC7_TXEP_MAX_SIZE                                  \
const uint8_t CDC7_txEpMaxSize[] = \
{CDC7_EP0_TX_SIZE, CDC7_EP1_TX_SIZE, CDC7_EP2_TX_SIZE, CDC7_EP3_TX_SIZE, CDC7_EP4_TX_SIZE, CDC7_EP5_TX_SIZE, CDC7_EP6_TX_SIZE, CDC7_EP7_TX_SIZE, };
extern const uint8_t CDC7_rxEpMaxSize[];
#define CDC7_RXEP_MAX_SIZE                                  \
const uint8_t CDC7_rxEpMaxSize[] = \
{CDC7_EP0_RX_SIZE, CDC7_EP1_RX_SIZE, CDC7_EP2_RX_SIZE, CDC7_EP3_RX_SIZE, CDC7_EP4_RX_SIZE, CDC7_EP5_RX_SIZE, CDC7_EP6_RX_SIZE, CDC7_EP7_RX_SIZE, };

// EndPoints init function for USB FS core
#define CDC7_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, CDC7_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, CDC7_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, CDC7_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, CDC7_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, CDC7_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, CDC7_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, CDC7_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, CDC7_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, CDC7_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, CDC7_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, CDC7_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, CDC7_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, CDC7_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, CDC7_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, CDC7_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, CDC7_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP4, CDC7_EP4_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP4, CDC7_EP4_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP4, CDC7_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, CDC7_EP4_RX_SIZE);  \
    /* Init ep5 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP5, CDC7_EP5_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP5, CDC7_EP5_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP5, CDC7_EP5_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP5, CDC7_EP5_RX_SIZE);  \
    /* Init ep6 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP6, CDC7_EP6_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP6, CDC7_EP6_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP6, CDC7_EP6_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP6, CDC7_EP6_RX_SIZE);  \
    /* Init ep7 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP7, CDC7_EP7_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP7, CDC7_EP7_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP7, CDC7_EP7_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP7, CDC7_EP7_RX_SIZE);  \
  }while(0)


// EndPoints init function for USB OTG core
#define CDC7_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, CDC7_OTG_RX_FIFO_ADDR, CDC7_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, CDC7_EP0_TYPE, CDC7_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, CDC7_EP0_TX_FIFO_ADDR, CDC7_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, CDC7_EP0_TYPE, CDC7_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, CDC7_EP1_TYPE, CDC7_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, CDC7_EP1_TX_FIFO_ADDR, CDC7_EP1_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP1, CDC7_EP1_TYPE, CDC7_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_Tx(dev, PCD_ENDP2, CDC7_EP2_TYPE, CDC7_EP2_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP2, CDC7_EP2_TX_FIFO_ADDR, CDC7_EP2_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP2, CDC7_EP2_TYPE, CDC7_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_Tx(dev, PCD_ENDP3, CDC7_EP3_TYPE, CDC7_EP3_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP3, CDC7_EP3_TX_FIFO_ADDR, CDC7_EP3_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP3, CDC7_EP3_TYPE, CDC7_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_Tx(dev, PCD_ENDP4, CDC7_EP4_TYPE, CDC7_EP4_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP4, CDC7_EP4_TX_FIFO_ADDR, CDC7_EP4_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP4, CDC7_EP4_TYPE, CDC7_EP4_RX_SIZE);  \
    /* Init ep5 */ \
    INIT_EP_Tx(dev, PCD_ENDP5, CDC7_EP5_TYPE, CDC7_EP5_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP5, CDC7_EP5_TX_FIFO_ADDR, CDC7_EP5_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP5, CDC7_EP5_TYPE, CDC7_EP5_RX_SIZE);  \
    /* Init ep6 */ \
    INIT_EP_Tx(dev, PCD_ENDP6, CDC7_EP6_TYPE, CDC7_EP6_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP6, CDC7_EP6_TX_FIFO_ADDR, CDC7_EP6_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP6, CDC7_EP6_TYPE, CDC7_EP6_RX_SIZE);  \
    /* Init ep7 */ \
    INIT_EP_Tx(dev, PCD_ENDP7, CDC7_EP7_TYPE, CDC7_EP7_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP7, CDC7_EP7_TX_FIFO_ADDR, CDC7_EP7_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP7, CDC7_EP7_TYPE, CDC7_EP7_RX_SIZE);  \
  }while(0)


#if defined(USB)
#define CDC7_TUSB_INIT_EP(dev) CDC7_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define CDC7_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC7_DEV_STATUS;         \
    dev->rx_max_size = CDC7_rxEpMaxSize;         \
    dev->tx_max_size = CDC7_txEpMaxSize;         \
    dev->descriptors = &CDC7_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define CDC7_TUSB_INIT_EP(dev) CDC7_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define CDC7_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = CDC7_DEV_STATUS;         \
    dev->descriptors = &CDC7_descriptors;         \
  }while(0)

#endif

#define CDC7_TUSB_INIT(dev) \
  do{\
    CDC7_TUSB_INIT_EP(dev);   \
    CDC7_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC7_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC7_EP_NUM
#endif


#define  CDC7_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t CDC7_DeviceDescriptor [18];
#define  CDC7_CONFIG_DESCRIPTOR_SIZE  (471)
extern const uint8_t CDC7_ConfigDescriptor [471];
#define CDC7_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define CDC7_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define CDC7_DEV_STATUS    ((CDC7_DEV_STATUS0) |(CDC7_DEV_STATUS1) )

extern const uint8_t* const CDC7_StringDescriptors[CDC7_STRING_COUNT];
extern const tusb_descriptors CDC7_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device4 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device5 define begin
/////////////////////////////////////////////////////////////////////
#define HID_VID                                             0x2017
#define HID_PID                                             0x0927
#define HID_STRING_COUNT                                    (4)
// Endpoint usage:
#ifdef HID_BTABLE_ADDRESS
#undef HID_BTABLE_ADDRESS
#endif
#define HID_BTABLE_ADDRESS                                  (0)
#define HID_MAX_EP                                          (1)
#define HID_EP_NUM                                          (HID_MAX_EP + 1)
#define HID_EP_BUF_DESC_TABLE_SIZE                          (8)

// PMA buffer reserved for buffer description table  
#define HID_USB_BUF_START                                   (HID_EP_BUF_DESC_TABLE_SIZE * HID_EP_NUM)

// EndPoints 0 defines
#define HID_EP0_RX_SIZE                                     (8)
#define HID_EP0_RX_ADDR                                     (HID_USB_BUF_START + 0)
#define HID_EP0_TX_SIZE                                     (8)
#define HID_EP0_TX_ADDR                                     (HID_USB_BUF_START + 8)
#define HID_EP0_TYPE                                        USB_EP_CONTROL

// EndPoints 1 defines
#define HID_EP1_RX_SIZE                                     (64)
#define HID_EP1_RX_ADDR                                     (HID_USB_BUF_START + 16)
#define HID_EP1_TX_SIZE                                     (64)
#define HID_EP1_TX_ADDR                                     (HID_USB_BUF_START + 80)
#define HID_EP1_TYPE                                        USB_EP_INTERRUPT


// Endpoint define for OTG core
#define HID_OTG_MAX_OUT_SIZE                                (64)
#define HID_OTG_CONTROL_EP_NUM                              (1)
#define HID_OTG_OUT_EP_NUM                                  (1)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 33
#define HID_OTG_RX_FIFO_SIZE                                (256)
#define HID_OTG_RX_FIFO_ADDR                                (0)
// Sum of IN ep max packet size is 72
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define HID_EP0_TX_FIFO_ADDR                                (256)
#define HID_EP0_TX_FIFO_SIZE                                (HID_EP0_TX_SIZE * 7)
#define HID_EP1_TX_FIFO_ADDR                                (312)
#define HID_EP1_TX_FIFO_SIZE                                (HID_EP1_TX_SIZE * 7)

// EndPoint max packed sizes
extern const uint8_t HID_txEpMaxSize[];
#define HID_TXEP_MAX_SIZE                                   \
const uint8_t HID_txEpMaxSize[] = \
{HID_EP0_TX_SIZE, HID_EP1_TX_SIZE, };
extern const uint8_t HID_rxEpMaxSize[];
#define HID_RXEP_MAX_SIZE                                   \
const uint8_t HID_rxEpMaxSize[] = \
{HID_EP0_RX_SIZE, HID_EP1_RX_SIZE, };

// EndPoints init function for USB FS core
#define HID_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, HID_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, HID_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, HID_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, HID_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, HID_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, HID_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, HID_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, HID_EP1_RX_SIZE);  \
  }while(0)


// EndPoints init function for USB OTG core
#define HID_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, HID_OTG_RX_FIFO_ADDR, HID_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, HID_EP0_TYPE, HID_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, HID_EP0_TX_FIFO_ADDR, HID_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, HID_EP0_TYPE, HID_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, HID_EP1_TYPE, HID_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, HID_EP1_TX_FIFO_ADDR, HID_EP1_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP1, HID_EP1_TYPE, HID_EP1_RX_SIZE);  \
  }while(0)


#if defined(USB)
#define HID_TUSB_INIT_EP(dev) HID_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define HID_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = HID_DEV_STATUS;         \
    dev->rx_max_size = HID_rxEpMaxSize;         \
    dev->tx_max_size = HID_txEpMaxSize;         \
    dev->descriptors = &HID_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define HID_TUSB_INIT_EP(dev) HID_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define HID_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = HID_DEV_STATUS;         \
    dev->descriptors = &HID_descriptors;         \
  }while(0)

#endif

#define HID_TUSB_INIT(dev) \
  do{\
    HID_TUSB_INIT_EP(dev);   \
    HID_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if HID_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  HID_EP_NUM
#endif


#define  HID_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t HID_DeviceDescriptor [18];
#define HID_REPORT_DESCRIPTOR_SIZE_IF0 24
extern const uint8_t HID_ReportDescriptor_if0[HID_REPORT_DESCRIPTOR_SIZE_IF0];
#define  HID_CONFIG_DESCRIPTOR_SIZE  (41)
extern const uint8_t HID_ConfigDescriptor [41];
#define HID_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define HID_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define HID_DEV_STATUS    ((HID_DEV_STATUS0) |(HID_DEV_STATUS1) )

extern const uint8_t* const HID_StringDescriptors[HID_STRING_COUNT];
extern const tusb_descriptors HID_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device5 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device6 define begin
/////////////////////////////////////////////////////////////////////
#define HID7_VID                                            0x2017
#define HID7_PID                                            0x0928
#define HID7_STRING_COUNT                                   (4)
// Endpoint usage:
#ifdef HID7_BTABLE_ADDRESS
#undef HID7_BTABLE_ADDRESS
#endif
#define HID7_BTABLE_ADDRESS                                 (0)
#define HID7_MAX_EP                                         (7)
#define HID7_EP_NUM                                         (HID7_MAX_EP + 1)
#define HID7_EP_BUF_DESC_TABLE_SIZE                         (8)

// PMA buffer reserved for buffer description table  
#define HID7_USB_BUF_START                                  (HID7_EP_BUF_DESC_TABLE_SIZE * HID7_EP_NUM)

// EndPoints 0 defines
#define HID7_EP0_RX_SIZE                                    (8)
#define HID7_EP0_RX_ADDR                                    (HID7_USB_BUF_START + 0)
#define HID7_EP0_TX_SIZE                                    (8)
#define HID7_EP0_TX_ADDR                                    (HID7_USB_BUF_START + 8)
#define HID7_EP0_TYPE                                       USB_EP_CONTROL

// EndPoints 1 defines
#define HID7_EP1_RX_SIZE                                    (64)
#define HID7_EP1_RX_ADDR                                    (HID7_USB_BUF_START + 16)
#define HID7_EP1_TX_SIZE                                    (64)
#define HID7_EP1_TX_ADDR                                    (HID7_USB_BUF_START + 80)
#define HID7_EP1_TYPE                                       USB_EP_INTERRUPT

// EndPoints 2 defines
#define HID7_EP2_RX_SIZE                                    (32)
#define HID7_EP2_RX_ADDR                                    (HID7_USB_BUF_START + 144)
#define HID7_EP2_TX_SIZE                                    (32)
#define HID7_EP2_TX_ADDR                                    (HID7_USB_BUF_START + 176)
#define HID7_EP2_TYPE                                       USB_EP_INTERRUPT

// EndPoints 3 defines
#define HID7_EP3_RX_SIZE                                    (32)
#define HID7_EP3_RX_ADDR                                    (HID7_USB_BUF_START + 208)
#define HID7_EP3_TX_SIZE                                    (32)
#define HID7_EP3_TX_ADDR                                    (HID7_USB_BUF_START + 240)
#define HID7_EP3_TYPE                                       USB_EP_INTERRUPT

// EndPoints 4 defines
#define HID7_EP4_RX_SIZE                                    (32)
#define HID7_EP4_RX_ADDR                                    (HID7_USB_BUF_START + 272)
#define HID7_EP4_TX_SIZE                                    (32)
#define HID7_EP4_TX_ADDR                                    (HID7_USB_BUF_START + 304)
#define HID7_EP4_TYPE                                       USB_EP_INTERRUPT

// EndPoints 5 defines
#define HID7_EP5_RX_SIZE                                    (16)
#define HID7_EP5_RX_ADDR                                    (HID7_USB_BUF_START + 336)
#define HID7_EP5_TX_SIZE                                    (16)
#define HID7_EP5_TX_ADDR                                    (HID7_USB_BUF_START + 352)
#define HID7_EP5_TYPE                                       USB_EP_INTERRUPT

// EndPoints 6 defines
#define HID7_EP6_RX_SIZE                                    (16)
#define HID7_EP6_RX_ADDR                                    (HID7_USB_BUF_START + 368)
#define HID7_EP6_TX_SIZE                                    (16)
#define HID7_EP6_TX_ADDR                                    (HID7_USB_BUF_START + 384)
#define HID7_EP6_TYPE                                       USB_EP_INTERRUPT

// EndPoints 7 defines
#define HID7_EP7_RX_SIZE                                    (16)
#define HID7_EP7_RX_ADDR                                    (HID7_USB_BUF_START + 400)
#define HID7_EP7_TX_SIZE                                    (16)
#define HID7_EP7_TX_ADDR                                    (HID7_USB_BUF_START + 416)
#define HID7_EP7_TYPE                                       USB_EP_INTERRUPT


// Endpoint define for OTG core
#define HID7_OTG_MAX_OUT_SIZE                               (64)
#define HID7_OTG_CONTROL_EP_NUM                             (1)
#define HID7_OTG_OUT_EP_NUM                                 (7)
// RX FIFO size / 4 > (CONTROL_EP_NUM * 5 + 8) +  (MAX_OUT_SIZE / 4 + 1) + (OUT_EP_NUM*2) + 1 = 45
#define HID7_OTG_RX_FIFO_SIZE                               (256)
#define HID7_OTG_RX_FIFO_ADDR                               (0)
// Sum of IN ep max packet size is 216
// Remain Fifo size is 1104 in bytes, Rx Used 256 bytes 
#define HID7_EP0_TX_FIFO_ADDR                               (256)
#define HID7_EP0_TX_FIFO_SIZE                               (HID7_EP0_TX_SIZE * 5)
#define HID7_EP1_TX_FIFO_ADDR                               (296)
#define HID7_EP1_TX_FIFO_SIZE                               (HID7_EP1_TX_SIZE * 5)
#define HID7_EP2_TX_FIFO_ADDR                               (616)
#define HID7_EP2_TX_FIFO_SIZE                               (HID7_EP2_TX_SIZE * 5)
#define HID7_EP3_TX_FIFO_ADDR                               (776)
#define HID7_EP3_TX_FIFO_SIZE                               (HID7_EP3_TX_SIZE * 5)
#define HID7_EP4_TX_FIFO_ADDR                               (936)
#define HID7_EP4_TX_FIFO_SIZE                               (HID7_EP4_TX_SIZE * 5)
#define HID7_EP5_TX_FIFO_ADDR                               (1096)
#define HID7_EP5_TX_FIFO_SIZE                               (HID7_EP5_TX_SIZE * 5)
#define HID7_EP6_TX_FIFO_ADDR                               (1176)
#define HID7_EP6_TX_FIFO_SIZE                               (HID7_EP6_TX_SIZE * 5)
#define HID7_EP7_TX_FIFO_ADDR                               (1256)
#define HID7_EP7_TX_FIFO_SIZE                               (HID7_EP7_TX_SIZE * 5)

// EndPoint max packed sizes
extern const uint8_t HID7_txEpMaxSize[];
#define HID7_TXEP_MAX_SIZE                                  \
const uint8_t HID7_txEpMaxSize[] = \
{HID7_EP0_TX_SIZE, HID7_EP1_TX_SIZE, HID7_EP2_TX_SIZE, HID7_EP3_TX_SIZE, HID7_EP4_TX_SIZE, HID7_EP5_TX_SIZE, HID7_EP6_TX_SIZE, HID7_EP7_TX_SIZE, };
extern const uint8_t HID7_rxEpMaxSize[];
#define HID7_RXEP_MAX_SIZE                                  \
const uint8_t HID7_rxEpMaxSize[] = \
{HID7_EP0_RX_SIZE, HID7_EP1_RX_SIZE, HID7_EP2_RX_SIZE, HID7_EP3_RX_SIZE, HID7_EP4_RX_SIZE, HID7_EP5_RX_SIZE, HID7_EP6_RX_SIZE, HID7_EP7_RX_SIZE, };

// EndPoints init function for USB FS core
#define HID7_TUSB_INIT_EP_FS(dev) \
  do{\
    /* Init ep0 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP0, HID7_EP0_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP0, HID7_EP0_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP0, HID7_EP0_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP0, HID7_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP1, HID7_EP1_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP1, HID7_EP1_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP1, HID7_EP1_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP1, HID7_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP2, HID7_EP2_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP2, HID7_EP2_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP2, HID7_EP2_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP2, HID7_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP3, HID7_EP3_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP3, HID7_EP3_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP3, HID7_EP3_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP3, HID7_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP4, HID7_EP4_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP4, HID7_EP4_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP4, HID7_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, HID7_EP4_RX_SIZE);  \
    /* Init ep5 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP5, HID7_EP5_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP5, HID7_EP5_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP5, HID7_EP5_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP5, HID7_EP5_RX_SIZE);  \
    /* Init ep6 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP6, HID7_EP6_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP6, HID7_EP6_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP6, HID7_EP6_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP6, HID7_EP6_RX_SIZE);  \
    /* Init ep7 */ \
    INIT_EP_BiDirection(dev, PCD_ENDP7, HID7_EP7_TYPE);  \
    SET_TX_ADDR(dev, PCD_ENDP7, HID7_EP7_TX_ADDR);  \
    SET_RX_ADDR(dev, PCD_ENDP7, HID7_EP7_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP7, HID7_EP7_RX_SIZE);  \
  }while(0)


// EndPoints init function for USB OTG core
#define HID7_TUSB_INIT_EP_OTG(dev) \
  do{\
    SET_RX_FIFO(dev, HID7_OTG_RX_FIFO_ADDR, HID7_OTG_RX_FIFO_SIZE);  \
    /* Init ep0 */ \
    INIT_EP_Tx(dev, PCD_ENDP0, HID7_EP0_TYPE, HID7_EP0_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP0, HID7_EP0_TX_FIFO_ADDR, HID7_EP0_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP0, HID7_EP0_TYPE, HID7_EP0_RX_SIZE);  \
    /* Init ep1 */ \
    INIT_EP_Tx(dev, PCD_ENDP1, HID7_EP1_TYPE, HID7_EP1_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP1, HID7_EP1_TX_FIFO_ADDR, HID7_EP1_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP1, HID7_EP1_TYPE, HID7_EP1_RX_SIZE);  \
    /* Init ep2 */ \
    INIT_EP_Tx(dev, PCD_ENDP2, HID7_EP2_TYPE, HID7_EP2_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP2, HID7_EP2_TX_FIFO_ADDR, HID7_EP2_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP2, HID7_EP2_TYPE, HID7_EP2_RX_SIZE);  \
    /* Init ep3 */ \
    INIT_EP_Tx(dev, PCD_ENDP3, HID7_EP3_TYPE, HID7_EP3_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP3, HID7_EP3_TX_FIFO_ADDR, HID7_EP3_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP3, HID7_EP3_TYPE, HID7_EP3_RX_SIZE);  \
    /* Init ep4 */ \
    INIT_EP_Tx(dev, PCD_ENDP4, HID7_EP4_TYPE, HID7_EP4_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP4, HID7_EP4_TX_FIFO_ADDR, HID7_EP4_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP4, HID7_EP4_TYPE, HID7_EP4_RX_SIZE);  \
    /* Init ep5 */ \
    INIT_EP_Tx(dev, PCD_ENDP5, HID7_EP5_TYPE, HID7_EP5_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP5, HID7_EP5_TX_FIFO_ADDR, HID7_EP5_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP5, HID7_EP5_TYPE, HID7_EP5_RX_SIZE);  \
    /* Init ep6 */ \
    INIT_EP_Tx(dev, PCD_ENDP6, HID7_EP6_TYPE, HID7_EP6_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP6, HID7_EP6_TX_FIFO_ADDR, HID7_EP6_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP6, HID7_EP6_TYPE, HID7_EP6_RX_SIZE);  \
    /* Init ep7 */ \
    INIT_EP_Tx(dev, PCD_ENDP7, HID7_EP7_TYPE, HID7_EP7_TX_SIZE);  \
    SET_TX_FIFO(dev, PCD_ENDP7, HID7_EP7_TX_FIFO_ADDR, HID7_EP7_TX_FIFO_SIZE);  \
    INIT_EP_Rx(dev, PCD_ENDP7, HID7_EP7_TYPE, HID7_EP7_RX_SIZE);  \
  }while(0)


#if defined(USB)
#define HID7_TUSB_INIT_EP(dev) HID7_TUSB_INIT_EP_FS(dev)

// Tiny USB device init function for FS core
#define HID7_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = HID7_DEV_STATUS;         \
    dev->rx_max_size = HID7_rxEpMaxSize;         \
    dev->tx_max_size = HID7_txEpMaxSize;         \
    dev->descriptors = &HID7_descriptors;         \
  }while(0)

#endif

#if defined(USB_OTG_FS) || defined(USB_OTG_HS)
#define HID7_TUSB_INIT_EP(dev) HID7_TUSB_INIT_EP_OTG(dev)

// Tiny USB device init function for OTG core
#define HID7_TUSB_INIT_DEVICE(dev) \
  do{\
    /* Init device features */       \
    memset(dev, 0, TUSB_DEVICE_SIZE);    \
    dev->status = HID7_DEV_STATUS;         \
    dev->descriptors = &HID7_descriptors;         \
  }while(0)

#endif

#define HID7_TUSB_INIT(dev) \
  do{\
    HID7_TUSB_INIT_EP(dev);   \
    HID7_TUSB_INIT_DEVICE(dev);   \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if HID7_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  HID7_EP_NUM
#endif


#define  HID7_DEVICE_DESCRIPTOR_SIZE  (18)
extern const uint8_t HID7_DeviceDescriptor [18];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF0 24
extern const uint8_t HID7_ReportDescriptor_if0[HID7_REPORT_DESCRIPTOR_SIZE_IF0];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF1 24
extern const uint8_t HID7_ReportDescriptor_if1[HID7_REPORT_DESCRIPTOR_SIZE_IF1];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF2 24
extern const uint8_t HID7_ReportDescriptor_if2[HID7_REPORT_DESCRIPTOR_SIZE_IF2];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF3 24
extern const uint8_t HID7_ReportDescriptor_if3[HID7_REPORT_DESCRIPTOR_SIZE_IF3];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF4 24
extern const uint8_t HID7_ReportDescriptor_if4[HID7_REPORT_DESCRIPTOR_SIZE_IF4];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF5 24
extern const uint8_t HID7_ReportDescriptor_if5[HID7_REPORT_DESCRIPTOR_SIZE_IF5];
#define HID7_REPORT_DESCRIPTOR_SIZE_IF6 24
extern const uint8_t HID7_ReportDescriptor_if6[HID7_REPORT_DESCRIPTOR_SIZE_IF6];
#define  HID7_CONFIG_DESCRIPTOR_SIZE  (233)
extern const uint8_t HID7_ConfigDescriptor [233];
#define HID7_DEV_STATUS0      (0)
#define HID7_DEV_STATUS1      (0)
#define HID7_DEV_STATUS    ((HID7_DEV_STATUS0) |(HID7_DEV_STATUS1) )

extern const uint8_t* const HID7_StringDescriptors[HID7_STRING_COUNT];
extern const tusb_descriptors HID7_descriptors;


/////////////////////////////////////////////////////////////////////
//// EndPoint for device6 define end
/////////////////////////////////////////////////////////////////////




#endif

