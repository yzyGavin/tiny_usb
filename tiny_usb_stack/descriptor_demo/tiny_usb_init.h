/*
 * Name   :  tiny_usb_init.h
 * Author :  admin@xtoolbox.org
 * Date   :  2018-11-16 17:58:46
 * Desc   :  This file is auto generate by the tiny_usb script tool
 *           Visit https://github.com/xtoolbox/tiny_usb for more info
 */

/*
  Input source name:  ..\tiny_usb_stack\descriptor_demo\demo.lua  
  Content type is lua script:
  ------------- lua script begin ------------
-- DEMO USB descriptor for tiny USB stack
require("usb_cdc_acm")
require("usb_hid")
require("usb_wcid")
return {
-- Demo descriptor of Bulk device
Device {
    strManufacture = "tiny usb",
    strProduct = "tiny usb bulk demo",
    strSerial = "tu123456",
    idVendor = 0x4322,
    idProduct = 0x4321,
    prefix = "BULK",
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        Interface{
            WCID = WinUSB,
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(2), BulkDouble, 64),
            strInterface = "TinyUsb1",
        },
        Interface{
            WCID = WinUSB,
            EndPoint(IN(3),  Bulk, 64),
            EndPoint(OUT(4), Bulk, 64),
            strInterface = "TinyUsb2",
        },
   }
},

-- Demo descriptor of CDC device
Device {
    strManufacture = "tiny usb",
    strProduct = "tiny usb cdc demo",
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
    strManufacture = "tiny usb",
    strProduct = "tiny usb cdc7 demo",
    strSerial = "tu123456",
    idVendor = 0x1234,   -- Win10 can drive the multiple CDC, VID PID can be any one
    idProduct = 0x0007,
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
    strManufacture = "tiny usb",
    strProduct = "tiny usb HID demo",
    strSerial = "tu123456",
    idVendor = 0x1234,
    idProduct = 0x0011,
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
    strManufacture = "tiny usb",
    strProduct = "tiny usb 7 HID demo",
    strSerial = "tu123456",
    idVendor = 0x1234,
    idProduct = 0x0017,
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
#define ____TINY_USB_STACK_DESCRIPTOR_DEMO_TINY_USB_INIT_H_
#include "tiny_usb.h"
/////////////////////////////////////////////////////////////////////
//// EndPoint for device1 define begin
/////////////////////////////////////////////////////////////////////
#define BULK_VID                                            0x4322
#define BULK_PID                                            0x4321
#define BULK_STRING_COUNT                                   (6)
// Endpoint usage:
#ifdef BULK_BTABLE_ADDRESS
#undef BULK_BTABLE_ADDRESS
#endif
#define BULK_BTABLE_ADDRESS                                 (0)
#define BULK_MAX_EP                                         (4)
#define BULK_EP_NUM                                         (BULK_MAX_EP + 1)
#define BULK_EP_BUF_DESC_TABLE_SIZE                         (8)

// PMA buffer reserved for buffer description table  
#define BULK_USB_BUF_START                                  (BULK_EP_BUF_DESC_TABLE_SIZE * BULK_EP_NUM)

// EndPoints 0 defines
#define BULK_EP0_RX_SIZE                                    (8)
#define BULK_EP0_RX_ADDR                                    (BULK_USB_BUF_START + 0)
#define BULK_EP0_TX_SIZE                                    (8)
#define BULK_EP0_TX_ADDR                                    (BULK_USB_BUF_START + 8)
#define BULK_EP0_TYPE                                       USB_EP_CONTROL

// EndPoints 1 defines
#define BULK_EP1_TX_SIZE                                    (64)
#define BULK_EP1_TX0_ADDR                                   (BULK_USB_BUF_START + 16)
#define BULK_EP1_TX1_ADDR                                   (BULK_USB_BUF_START + 80)
#define BULK_EP1_TYPE                                       USB_EP_BULK

// EndPoints 2 defines
#define BULK_EP2_RX_SIZE                                    (64)
#define BULK_EP2_RX0_ADDR                                   (BULK_USB_BUF_START + 144)
#define BULK_EP2_RX1_ADDR                                   (BULK_USB_BUF_START + 208)
#define BULK_EP2_TYPE                                       USB_EP_BULK

// EndPoints 3 defines
#define BULK_EP3_TX_SIZE                                    (64)
#define BULK_EP3_TX_ADDR                                    (BULK_USB_BUF_START + 272)
#define BULK_EP3_TYPE                                       USB_EP_BULK

// EndPoints 4 defines
#define BULK_EP4_RX_SIZE                                    (64)
#define BULK_EP4_RX_ADDR                                    (BULK_USB_BUF_START + 336)
#define BULK_EP4_TYPE                                       USB_EP_BULK

// EndPoint max packed sizes
extern const uint8_t BULK_txEpMaxSize[];
#define BULK_TXEP_MAX_SIZE                                  \
const uint8_t BULK_txEpMaxSize[] = \
{BULK_EP0_TX_SIZE, BULK_EP1_TX_SIZE, 0, BULK_EP3_TX_SIZE, 0, };
extern const uint8_t BULK_rxEpMaxSize[];
#define BULK_RXEP_MAX_SIZE                                  \
const uint8_t BULK_rxEpMaxSize[] = \
{BULK_EP0_RX_SIZE, 0, BULK_EP2_RX_SIZE, 0, BULK_EP4_RX_SIZE, };

// EndPoints init function
#define BULK_TUSB_INIT(dev) \
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
    /* Init ep3 */ \
    INIT_EP_TxOnly(dev, PCD_ENDP3, BULK_EP3_TYPE);       \
    SET_TX_ADDR(dev, PCD_ENDP3, BULK_EP3_TX_ADDR);  \
    /* Init ep4 */ \
    INIT_EP_RxOnly(dev, PCD_ENDP4, BULK_EP4_TYPE);       \
    SET_RX_ADDR(dev, PCD_ENDP4, BULK_EP4_RX_ADDR);  \
    SET_RX_CNT(dev, PCD_ENDP4, BULK_EP4_RX_SIZE);  \
    /* Init device features */       \
    memset(dev, 0, sizeof(*dev));    \
    dev->status = BULK_DEV_STATUS;         \
    dev->rx_max_size = BULK_rxEpMaxSize;         \
    dev->tx_max_size = BULK_txEpMaxSize;         \
    dev->descriptors = &BULK_descriptors;         \
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
/////////////////////////////////////////////////////////////////////
//// EndPoint for device1 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device2 define begin
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

// EndPoint max packed sizes
extern const uint8_t CDC_txEpMaxSize[];
#define CDC_TXEP_MAX_SIZE                                   \
const uint8_t CDC_txEpMaxSize[] = \
{CDC_EP0_TX_SIZE, CDC_EP1_TX_SIZE, 0, CDC_EP3_TX_SIZE, };
extern const uint8_t CDC_rxEpMaxSize[];
#define CDC_RXEP_MAX_SIZE                                   \
const uint8_t CDC_rxEpMaxSize[] = \
{CDC_EP0_RX_SIZE, 0, CDC_EP2_RX_SIZE, 0, };

// EndPoints init function
#define CDC_TUSB_INIT(dev) \
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
    /* Init device features */       \
    memset(dev, 0, sizeof(*dev));    \
    dev->status = CDC_DEV_STATUS;         \
    dev->rx_max_size = CDC_rxEpMaxSize;         \
    dev->tx_max_size = CDC_txEpMaxSize;         \
    dev->descriptors = &CDC_descriptors;         \
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


/////////////////////////////////////////////////////////////////////
//// EndPoint for device2 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device3 define begin
/////////////////////////////////////////////////////////////////////
#define CDC7_VID                                            0x1234
#define CDC7_PID                                            0x0007
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

// EndPoint max packed sizes
extern const uint8_t CDC7_txEpMaxSize[];
#define CDC7_TXEP_MAX_SIZE                                  \
const uint8_t CDC7_txEpMaxSize[] = \
{CDC7_EP0_TX_SIZE, CDC7_EP1_TX_SIZE, CDC7_EP2_TX_SIZE, CDC7_EP3_TX_SIZE, CDC7_EP4_TX_SIZE, CDC7_EP5_TX_SIZE, CDC7_EP6_TX_SIZE, CDC7_EP7_TX_SIZE, };
extern const uint8_t CDC7_rxEpMaxSize[];
#define CDC7_RXEP_MAX_SIZE                                  \
const uint8_t CDC7_rxEpMaxSize[] = \
{CDC7_EP0_RX_SIZE, CDC7_EP1_RX_SIZE, CDC7_EP2_RX_SIZE, CDC7_EP3_RX_SIZE, CDC7_EP4_RX_SIZE, CDC7_EP5_RX_SIZE, CDC7_EP6_RX_SIZE, CDC7_EP7_RX_SIZE, };

// EndPoints init function
#define CDC7_TUSB_INIT(dev) \
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
    /* Init device features */       \
    memset(dev, 0, sizeof(*dev));    \
    dev->status = CDC7_DEV_STATUS;         \
    dev->rx_max_size = CDC7_rxEpMaxSize;         \
    dev->tx_max_size = CDC7_txEpMaxSize;         \
    dev->descriptors = &CDC7_descriptors;         \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if CDC7_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  CDC7_EP_NUM
#endif


/////////////////////////////////////////////////////////////////////
//// EndPoint for device3 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device4 define begin
/////////////////////////////////////////////////////////////////////
#define HID_VID                                             0x1234
#define HID_PID                                             0x0011
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

// EndPoint max packed sizes
extern const uint8_t HID_txEpMaxSize[];
#define HID_TXEP_MAX_SIZE                                   \
const uint8_t HID_txEpMaxSize[] = \
{HID_EP0_TX_SIZE, HID_EP1_TX_SIZE, };
extern const uint8_t HID_rxEpMaxSize[];
#define HID_RXEP_MAX_SIZE                                   \
const uint8_t HID_rxEpMaxSize[] = \
{HID_EP0_RX_SIZE, HID_EP1_RX_SIZE, };

// EndPoints init function
#define HID_TUSB_INIT(dev) \
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
    /* Init device features */       \
    memset(dev, 0, sizeof(*dev));    \
    dev->status = HID_DEV_STATUS;         \
    dev->rx_max_size = HID_rxEpMaxSize;         \
    dev->tx_max_size = HID_txEpMaxSize;         \
    dev->descriptors = &HID_descriptors;         \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if HID_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  HID_EP_NUM
#endif


/////////////////////////////////////////////////////////////////////
//// EndPoint for device4 define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// EndPoint for device5 define begin
/////////////////////////////////////////////////////////////////////
#define HID7_VID                                            0x1234
#define HID7_PID                                            0x0017
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

// EndPoint max packed sizes
extern const uint8_t HID7_txEpMaxSize[];
#define HID7_TXEP_MAX_SIZE                                  \
const uint8_t HID7_txEpMaxSize[] = \
{HID7_EP0_TX_SIZE, HID7_EP1_TX_SIZE, HID7_EP2_TX_SIZE, HID7_EP3_TX_SIZE, HID7_EP4_TX_SIZE, HID7_EP5_TX_SIZE, HID7_EP6_TX_SIZE, HID7_EP7_TX_SIZE, };
extern const uint8_t HID7_rxEpMaxSize[];
#define HID7_RXEP_MAX_SIZE                                  \
const uint8_t HID7_rxEpMaxSize[] = \
{HID7_EP0_RX_SIZE, HID7_EP1_RX_SIZE, HID7_EP2_RX_SIZE, HID7_EP3_RX_SIZE, HID7_EP4_RX_SIZE, HID7_EP5_RX_SIZE, HID7_EP6_RX_SIZE, HID7_EP7_RX_SIZE, };

// EndPoints init function
#define HID7_TUSB_INIT(dev) \
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
    /* Init device features */       \
    memset(dev, 0, sizeof(*dev));    \
    dev->status = HID7_DEV_STATUS;         \
    dev->rx_max_size = HID7_rxEpMaxSize;         \
    dev->tx_max_size = HID7_txEpMaxSize;         \
    dev->descriptors = &HID7_descriptors;         \
  }while(0)

// Get End Point count
#ifndef  EP_NUM
#define  EP_NUM 1
#endif
#if HID7_EP_NUM > EP_NUM
#undef   EP_NUM
#define  EP_NUM  HID7_EP_NUM
#endif


/////////////////////////////////////////////////////////////////////
//// EndPoint for device5 define end
/////////////////////////////////////////////////////////////////////




#endif

