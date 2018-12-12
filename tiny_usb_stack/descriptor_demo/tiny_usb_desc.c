/*
 * Name   :  tiny_usb_desc.c
 * Author :  admin@xtoolbox.org
 * Date   :  2018-12-12 16:47:47
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
    bMaxPacketSize = 8,
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
    bMaxPacketSize = 8,
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
#include "tiny_usb.h"
/////////////////////////////////////////////////////////////////////
//// Descriptor for device1 define begin
/////////////////////////////////////////////////////////////////////
#define  BULK_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t BULK_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0x00,                                         /* bDeviceClass */
    0x00,                                         /* bDeviceSubClass */
    0x00,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(BULK_VID), HIBYTE(BULK_VID),           /* idVendor */
    LOBYTE(BULK_PID), HIBYTE(BULK_PID),           /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define  BULK_CONFIG_DESCRIPTOR_SIZE  (32)
__ALIGN_BEGIN const uint8_t BULK_ConfigDescriptor [32] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0x20, 0x00,                                   /* wTotalLength */
    0x01,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0xe0,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0xff,                                         /* bInterfaceClass */
    0xff,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x04,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x02,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define BULK_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define BULK_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define BULK_DEV_STATUS    ((BULK_DEV_STATUS0) |(BULK_DEV_STATUS1) )

BULK_TXEP_MAX_SIZE
BULK_RXEP_MAX_SIZE

// Strings 
#define BULK_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define BULK_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  BULK_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define BULK_STRING_DESCRIPTOR1_STR          "teeny usb"
#define BULK_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  BULK_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define BULK_STRING_DESCRIPTOR2_STR          "teeny usb bulk demo"
#define BULK_STRING_DESCRIPTOR2_SIZE          (40)
WEAK __ALIGN_BEGIN const uint8_t  BULK_StringDescriptor2 [40] __ALIGN_END = {
    0x28,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    'b', 0x00,                                    /* wcChar10 */
    'u', 0x00,                                    /* wcChar11 */
    'l', 0x00,                                    /* wcChar12 */
    'k', 0x00,                                    /* wcChar13 */
    ' ', 0x00,                                    /* wcChar14 */
    'd', 0x00,                                    /* wcChar15 */
    'e', 0x00,                                    /* wcChar16 */
    'm', 0x00,                                    /* wcChar17 */
    'o', 0x00,                                    /* wcChar18 */
};
#define BULK_STRING_DESCRIPTOR3_STR          "tu123456"
#define BULK_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  BULK_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
#define BULK_STRING_DESCRIPTOR4_STR          "TeenyUsb2"
#define BULK_STRING_DESCRIPTOR4_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  BULK_StringDescriptor4 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'T', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    'U', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    '2', 0x00,                                    /* wcChar8 */
};
const uint8_t* const BULK_StringDescriptors[BULK_STRING_COUNT] = {
BULK_StringDescriptor0,
BULK_StringDescriptor1,
BULK_StringDescriptor2,
BULK_StringDescriptor3,
BULK_StringDescriptor4,
};



#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'M', 0x00,                                    /* wcChar0 */
    'S', 0x00,                                    /* wcChar1 */
    'F', 0x00,                                    /* wcChar2 */
    'T', 0x00,                                    /* wcChar3 */
    '1', 0x00,                                    /* wcChar4 */
    '0', 0x00,                                    /* wcChar5 */
    '0', 0x00,                                    /* wcChar6 */
    WCID_VENDOR_CODE,                             /* bVendorCode */
    0x00,                                         /* bReserved */
};
#endif

#define  BULK_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t BULK_WCIDDescriptor [40] __ALIGN_END = {
    0x28, 0x00, 0x00, 0x00,                       /* dwLength */
    0x00, 0x01,                                   /* bcdVersion */
    0x04, 0x00,                                   /* wIndex */
    0x01,                                         /* bCount */
    0,0,0,0,0,0,0,                                /* Reserved */
    /* WCID Function  */
    0x00,                                         /* bFirstInterfaceNumber */
    0x01,                                         /* bReserved */
    /* CID */
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00, 
    /* sub CID */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0,0,0,0,0,0,                                  /* Reserved */
};

#define  BULK_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t BULK_WCIDProperties [142] __ALIGN_END = {
    0x8e, 0x00, 0x00, 0x00,                       /* dwLength */
    0x00, 0x01,                                   /* bcdVersion */
    0x05, 0x00,                                   /* wIndex */
    0x01, 0x00,                                   /* wCount */
    /*WCID property field */
  /* DeviceInterfaceGUID = 
       {32d68452-31d6-bac8-855a-27c822ee4f86}  */
    0x84, 0x00, 0x00, 0x00,                       /* dwSize */
    0x01, 0x00, 0x00, 0x00,                       /* dwPropertyDataType */
    0x28, 0x00,                                   /* wPropertyNameLength */
    'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 
    'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00, 
    't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00, 
    'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 
    'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00, 
    
    0x4e, 0x00, 0x00, 0x00,                       /* dwPropertyDataLength */
    '{', 0x00, '3', 0x00, '2', 0x00, 'd', 0x00, 
    '6', 0x00, '8', 0x00, '4', 0x00, '5', 0x00, 
    '2', 0x00, '-', 0x00, '3', 0x00, '1', 0x00, 
    'd', 0x00, '6', 0x00, '-', 0x00, 'b', 0x00, 
    'a', 0x00, 'c', 0x00, '8', 0x00, '-', 0x00, 
    '8', 0x00, '5', 0x00, '5', 0x00, 'a', 0x00, 
    '-', 0x00, '2', 0x00, '7', 0x00, 'c', 0x00, 
    '8', 0x00, '2', 0x00, '2', 0x00, 'e', 0x00, 
    'e', 0x00, '4', 0x00, 'f', 0x00, '8', 0x00, 
    '6', 0x00, '}', 0x00, 0x00, 0x00, 
};


#endif

//  Device descriptors
const tusb_descriptors BULK_descriptors = {
  .device = BULK_DeviceDescriptor,
  .config = BULK_ConfigDescriptor,
  .strings = BULK_StringDescriptors,
  .string_cnt = BULK_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(BULK_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = BULK_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // BULK_WCID_DESCRIPTOR_SIZE)

#if defined(BULK_WCID_PROPERTIES_SIZE)
  .wcid_properties = BULK_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // BULK_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device1  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device2 define begin
/////////////////////////////////////////////////////////////////////
#define  ISO_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t ISO_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0x00,                                         /* bDeviceClass */
    0x00,                                         /* bDeviceSubClass */
    0x00,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(ISO_VID), HIBYTE(ISO_VID),             /* idVendor */
    LOBYTE(ISO_PID), HIBYTE(ISO_PID),             /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define  ISO_CONFIG_DESCRIPTOR_SIZE  (32)
__ALIGN_BEGIN const uint8_t ISO_ConfigDescriptor [32] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0x20, 0x00,                                   /* wTotalLength */
    0x01,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0xe0,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0xff,                                         /* bInterfaceClass */
    0xff,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x04,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x01,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x02,                                         /* bEndpointAddress */
    0x01,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define ISO_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define ISO_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define ISO_DEV_STATUS    ((ISO_DEV_STATUS0) |(ISO_DEV_STATUS1) )

ISO_TXEP_MAX_SIZE
ISO_RXEP_MAX_SIZE

// Strings 
#define ISO_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define ISO_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  ISO_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define ISO_STRING_DESCRIPTOR1_STR          "teeny usb"
#define ISO_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  ISO_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define ISO_STRING_DESCRIPTOR2_STR          "teeny usb iso demo"
#define ISO_STRING_DESCRIPTOR2_SIZE          (38)
WEAK __ALIGN_BEGIN const uint8_t  ISO_StringDescriptor2 [38] __ALIGN_END = {
    0x26,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    'i', 0x00,                                    /* wcChar10 */
    's', 0x00,                                    /* wcChar11 */
    'o', 0x00,                                    /* wcChar12 */
    ' ', 0x00,                                    /* wcChar13 */
    'd', 0x00,                                    /* wcChar14 */
    'e', 0x00,                                    /* wcChar15 */
    'm', 0x00,                                    /* wcChar16 */
    'o', 0x00,                                    /* wcChar17 */
};
#define ISO_STRING_DESCRIPTOR3_STR          "tu123456"
#define ISO_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  ISO_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
#define ISO_STRING_DESCRIPTOR4_STR          "TeenyUsb2"
#define ISO_STRING_DESCRIPTOR4_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  ISO_StringDescriptor4 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'T', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    'U', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    '2', 0x00,                                    /* wcChar8 */
};
const uint8_t* const ISO_StringDescriptors[ISO_STRING_COUNT] = {
ISO_StringDescriptor0,
ISO_StringDescriptor1,
ISO_StringDescriptor2,
ISO_StringDescriptor3,
ISO_StringDescriptor4,
};



#if defined(HAS_WCID)

// Define WCID os string descriptor 
#ifndef WCID_MSOS_STRING
#define WCID_MSOS_STRING
#define WCID_STRING_DESCRIPTOR_MSOS_STR          "MSFT100"
#define WCID_STRING_DESCRIPTOR_MSOS_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  WCID_StringDescriptor_MSOS [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    'M', 0x00,                                    /* wcChar0 */
    'S', 0x00,                                    /* wcChar1 */
    'F', 0x00,                                    /* wcChar2 */
    'T', 0x00,                                    /* wcChar3 */
    '1', 0x00,                                    /* wcChar4 */
    '0', 0x00,                                    /* wcChar5 */
    '0', 0x00,                                    /* wcChar6 */
    WCID_VENDOR_CODE,                             /* bVendorCode */
    0x00,                                         /* bReserved */
};
#endif

#define  ISO_WCID_DESCRIPTOR_SIZE  (40)
WEAK __ALIGN_BEGIN const uint8_t ISO_WCIDDescriptor [40] __ALIGN_END = {
    0x28, 0x00, 0x00, 0x00,                       /* dwLength */
    0x00, 0x01,                                   /* bcdVersion */
    0x04, 0x00,                                   /* wIndex */
    0x01,                                         /* bCount */
    0,0,0,0,0,0,0,                                /* Reserved */
    /* WCID Function  */
    0x00,                                         /* bFirstInterfaceNumber */
    0x01,                                         /* bReserved */
    /* CID */
    'W', 'I', 'N', 'U', 'S', 'B', 0x00, 0x00, 
    /* sub CID */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0,0,0,0,0,0,                                  /* Reserved */
};

#define  ISO_WCID_PROPERTIES_SIZE  (142)
WEAK __ALIGN_BEGIN const uint8_t ISO_WCIDProperties [142] __ALIGN_END = {
    0x8e, 0x00, 0x00, 0x00,                       /* dwLength */
    0x00, 0x01,                                   /* bcdVersion */
    0x05, 0x00,                                   /* wIndex */
    0x01, 0x00,                                   /* wCount */
    /*WCID property field */
  /* DeviceInterfaceGUID = 
       {6cced06e-5f80-fbc8-6458-a4ce5de288b0}  */
    0x84, 0x00, 0x00, 0x00,                       /* dwSize */
    0x01, 0x00, 0x00, 0x00,                       /* dwPropertyDataType */
    0x28, 0x00,                                   /* wPropertyNameLength */
    'D', 0x00, 'e', 0x00, 'v', 0x00, 'i', 0x00, 
    'c', 0x00, 'e', 0x00, 'I', 0x00, 'n', 0x00, 
    't', 0x00, 'e', 0x00, 'r', 0x00, 'f', 0x00, 
    'a', 0x00, 'c', 0x00, 'e', 0x00, 'G', 0x00, 
    'U', 0x00, 'I', 0x00, 'D', 0x00, 0x00, 0x00, 
    
    0x4e, 0x00, 0x00, 0x00,                       /* dwPropertyDataLength */
    '{', 0x00, '6', 0x00, 'c', 0x00, 'c', 0x00, 
    'e', 0x00, 'd', 0x00, '0', 0x00, '6', 0x00, 
    'e', 0x00, '-', 0x00, '5', 0x00, 'f', 0x00, 
    '8', 0x00, '0', 0x00, '-', 0x00, 'f', 0x00, 
    'b', 0x00, 'c', 0x00, '8', 0x00, '-', 0x00, 
    '6', 0x00, '4', 0x00, '5', 0x00, '8', 0x00, 
    '-', 0x00, 'a', 0x00, '4', 0x00, 'c', 0x00, 
    'e', 0x00, '5', 0x00, 'd', 0x00, 'e', 0x00, 
    '2', 0x00, '8', 0x00, '8', 0x00, 'b', 0x00, 
    '0', 0x00, '}', 0x00, 0x00, 0x00, 
};


#endif

//  Device descriptors
const tusb_descriptors ISO_descriptors = {
  .device = ISO_DeviceDescriptor,
  .config = ISO_ConfigDescriptor,
  .strings = ISO_StringDescriptors,
  .string_cnt = ISO_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(ISO_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = ISO_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // ISO_WCID_DESCRIPTOR_SIZE)

#if defined(ISO_WCID_PROPERTIES_SIZE)
  .wcid_properties = ISO_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // ISO_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device2  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device3 define begin
/////////////////////////////////////////////////////////////////////
#define  CDC_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t CDC_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0x00,                                         /* bDeviceClass */
    0x00,                                         /* bDeviceSubClass */
    0x00,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(CDC_VID), HIBYTE(CDC_VID),             /* idVendor */
    LOBYTE(CDC_PID), HIBYTE(CDC_PID),             /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define  CDC_CONFIG_DESCRIPTOR_SIZE  (67)
__ALIGN_BEGIN const uint8_t CDC_ConfigDescriptor [67] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0x43, 0x00,                                   /* wTotalLength */
    0x02,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0xe0,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x83,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x01,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x02,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define CDC_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define CDC_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define CDC_DEV_STATUS    ((CDC_DEV_STATUS0) |(CDC_DEV_STATUS1) )

CDC_TXEP_MAX_SIZE
CDC_RXEP_MAX_SIZE

// Strings 
#define CDC_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define CDC_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  CDC_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define CDC_STRING_DESCRIPTOR1_STR          "teeny usb"
#define CDC_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  CDC_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define CDC_STRING_DESCRIPTOR2_STR          "teeny usb cdc demo"
#define CDC_STRING_DESCRIPTOR2_SIZE          (38)
WEAK __ALIGN_BEGIN const uint8_t  CDC_StringDescriptor2 [38] __ALIGN_END = {
    0x26,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    'c', 0x00,                                    /* wcChar10 */
    'd', 0x00,                                    /* wcChar11 */
    'c', 0x00,                                    /* wcChar12 */
    ' ', 0x00,                                    /* wcChar13 */
    'd', 0x00,                                    /* wcChar14 */
    'e', 0x00,                                    /* wcChar15 */
    'm', 0x00,                                    /* wcChar16 */
    'o', 0x00,                                    /* wcChar17 */
};
#define CDC_STRING_DESCRIPTOR3_STR          "tu123456"
#define CDC_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  CDC_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
const uint8_t* const CDC_StringDescriptors[CDC_STRING_COUNT] = {
CDC_StringDescriptor0,
CDC_StringDescriptor1,
CDC_StringDescriptor2,
CDC_StringDescriptor3,
};

//  Device descriptors
const tusb_descriptors CDC_descriptors = {
  .device = CDC_DeviceDescriptor,
  .config = CDC_ConfigDescriptor,
  .strings = CDC_StringDescriptors,
  .string_cnt = CDC_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(CDC_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = CDC_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // CDC_WCID_DESCRIPTOR_SIZE)

#if defined(CDC_WCID_PROPERTIES_SIZE)
  .wcid_properties = CDC_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // CDC_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device3  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device4 define begin
/////////////////////////////////////////////////////////////////////
#define  CDC7_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t CDC7_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0xef,                                         /* bDeviceClass */
    0x02,                                         /* bDeviceSubClass */
    0x01,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(CDC7_VID), HIBYTE(CDC7_VID),           /* idVendor */
    LOBYTE(CDC7_PID), HIBYTE(CDC7_PID),           /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define  CDC7_CONFIG_DESCRIPTOR_SIZE  (471)
__ALIGN_BEGIN const uint8_t CDC7_ConfigDescriptor [471] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0xd7, 0x01,                                   /* wTotalLength */
    0x0e,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0xe0,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x00,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x88,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x01,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x01,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x02,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x02,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x89,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x03,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x82,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x02,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x04,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x04,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x8a,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x05,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x83,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x03,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x06,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x06,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x8b,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x07,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x84,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x04,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x08,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x08,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x8c,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x09,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x85,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x05,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x0a,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x0a,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x8d,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x0b,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x86,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x06,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
  /* IAD descriptor */
    0x08,                                         /* bLength */
    USB_IAD_DESCRIPTOR_TYPE,                      /* bDescriptorType */
    0x0c,                                         /* bFirstInterface */
    0x02,                                         /* bInterfaceCount */
    0x02,                                         /* bFunctionClass */
    0x02,                                         /* bFunctionSubClass */
    0x01,                                         /* bFunctionProtocol */
    0x00,                                         /* iFunction */
    /* Interface descriptor, len: 35*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x0c,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x01,                                         /* bNumEndpoints */
    0x02,                                         /* bInterfaceClass */
    0x02,                                         /* bInterfaceSubClass */
    0x01,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* Function descriptor Header */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x00,                                         /* bDescriptorSubtype */
    0x10, 0x01,                                   /* bcdCDC */
    /* Function descriptor Call Management */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x01,                                         /* bDescriptorSubtype */
    0x00,                                         /* bmCapabilities */
    0x01,                                         /* bDataInterface */
    /* Function descriptor ACM (Abstract Control Management) */
    0x04,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x02,                                         /* bDescriptorSubtype */
    0x02,                                         /* bmCapabilities */
    /* Function descriptor Union */
    0x05,                                         /* bLength */
    0x24,                                         /* bDescriptorType */
    0x06,                                         /* bDescriptorSubtype */
    0x00,                                         /* bMasterInterface */
    0x01,                                         /* bSlaveInterface0 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x8e,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x08, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 23*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x0d,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x0a,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x87,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x07,                                         /* bEndpointAddress */
    0x02,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define CDC7_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define CDC7_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define CDC7_DEV_STATUS    ((CDC7_DEV_STATUS0) |(CDC7_DEV_STATUS1) )

CDC7_TXEP_MAX_SIZE
CDC7_RXEP_MAX_SIZE

// Strings 
#define CDC7_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define CDC7_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  CDC7_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define CDC7_STRING_DESCRIPTOR1_STR          "teeny usb"
#define CDC7_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  CDC7_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define CDC7_STRING_DESCRIPTOR2_STR          "teeny usb cdc7 demo"
#define CDC7_STRING_DESCRIPTOR2_SIZE          (40)
WEAK __ALIGN_BEGIN const uint8_t  CDC7_StringDescriptor2 [40] __ALIGN_END = {
    0x28,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    'c', 0x00,                                    /* wcChar10 */
    'd', 0x00,                                    /* wcChar11 */
    'c', 0x00,                                    /* wcChar12 */
    '7', 0x00,                                    /* wcChar13 */
    ' ', 0x00,                                    /* wcChar14 */
    'd', 0x00,                                    /* wcChar15 */
    'e', 0x00,                                    /* wcChar16 */
    'm', 0x00,                                    /* wcChar17 */
    'o', 0x00,                                    /* wcChar18 */
};
#define CDC7_STRING_DESCRIPTOR3_STR          "tu123456"
#define CDC7_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  CDC7_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
const uint8_t* const CDC7_StringDescriptors[CDC7_STRING_COUNT] = {
CDC7_StringDescriptor0,
CDC7_StringDescriptor1,
CDC7_StringDescriptor2,
CDC7_StringDescriptor3,
};

//  Device descriptors
const tusb_descriptors CDC7_descriptors = {
  .device = CDC7_DeviceDescriptor,
  .config = CDC7_ConfigDescriptor,
  .strings = CDC7_StringDescriptors,
  .string_cnt = CDC7_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(CDC7_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = CDC7_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // CDC7_WCID_DESCRIPTOR_SIZE)

#if defined(CDC7_WCID_PROPERTIES_SIZE)
  .wcid_properties = CDC7_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // CDC7_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device4  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device5 define begin
/////////////////////////////////////////////////////////////////////
#define  HID_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t HID_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0x00,                                         /* bDeviceClass */
    0x00,                                         /* bDeviceSubClass */
    0x00,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(HID_VID), HIBYTE(HID_VID),             /* idVendor */
    LOBYTE(HID_PID), HIBYTE(HID_PID),             /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define HID_REPORT_DESCRIPTOR_SIZE_IF0 24
WEAK __ALIGN_BEGIN const uint8_t HID_ReportDescriptor_if0[HID_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x40,        //   Report Count (64)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define  HID_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN_BEGIN const uint8_t HID_ConfigDescriptor [41] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0x29, 0x00,                                   /* wTotalLength */
    0x01,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0xe0,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x01,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define HID_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define HID_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define HID_DEV_STATUS    ((HID_DEV_STATUS0) |(HID_DEV_STATUS1) )

HID_TXEP_MAX_SIZE
HID_RXEP_MAX_SIZE

// Strings 
#define HID_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define HID_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  HID_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define HID_STRING_DESCRIPTOR1_STR          "teeny usb"
#define HID_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  HID_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define HID_STRING_DESCRIPTOR2_STR          "teeny usb HID demo"
#define HID_STRING_DESCRIPTOR2_SIZE          (38)
WEAK __ALIGN_BEGIN const uint8_t  HID_StringDescriptor2 [38] __ALIGN_END = {
    0x26,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    'H', 0x00,                                    /* wcChar10 */
    'I', 0x00,                                    /* wcChar11 */
    'D', 0x00,                                    /* wcChar12 */
    ' ', 0x00,                                    /* wcChar13 */
    'd', 0x00,                                    /* wcChar14 */
    'e', 0x00,                                    /* wcChar15 */
    'm', 0x00,                                    /* wcChar16 */
    'o', 0x00,                                    /* wcChar17 */
};
#define HID_STRING_DESCRIPTOR3_STR          "tu123456"
#define HID_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  HID_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
const uint8_t* const HID_StringDescriptors[HID_STRING_COUNT] = {
HID_StringDescriptor0,
HID_StringDescriptor1,
HID_StringDescriptor2,
HID_StringDescriptor3,
};

//  Device descriptors
const tusb_descriptors HID_descriptors = {
  .device = HID_DeviceDescriptor,
  .config = HID_ConfigDescriptor,
  .strings = HID_StringDescriptors,
  .string_cnt = HID_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(HID_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = HID_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // HID_WCID_DESCRIPTOR_SIZE)

#if defined(HID_WCID_PROPERTIES_SIZE)
  .wcid_properties = HID_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // HID_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device5  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device6 define begin
/////////////////////////////////////////////////////////////////////
#define  HID7_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN_BEGIN  const uint8_t HID7_DeviceDescriptor [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x00, 0x02,                                   /* bcdUSB */
    0x00,                                         /* bDeviceClass */
    0x00,                                         /* bDeviceSubClass */
    0x00,                                         /* bDeviceProtocol */
    0x08,                                         /* bMaxPacketSize */
    LOBYTE(HID7_VID), HIBYTE(HID7_VID),           /* idVendor */
    LOBYTE(HID7_PID), HIBYTE(HID7_PID),           /* idProduct */
    0x00, 0x01,                                   /* bcdDevice */
    0x01,                                         /* iManufacture */
    0x02,                                         /* iProduct */
    0x03,                                         /* iSerial */
    0x01,                                         /* bNumConfigurations */
};

// Configs 
#define HID7_REPORT_DESCRIPTOR_SIZE_IF0 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if0[HID7_REPORT_DESCRIPTOR_SIZE_IF0] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x40,        //   Report Count (64)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF1 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if1[HID7_REPORT_DESCRIPTOR_SIZE_IF1] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x20,        //   Report Count (32)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF2 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if2[HID7_REPORT_DESCRIPTOR_SIZE_IF2] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x20,        //   Report Count (32)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF3 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if3[HID7_REPORT_DESCRIPTOR_SIZE_IF3] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x20,        //   Report Count (32)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF4 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if4[HID7_REPORT_DESCRIPTOR_SIZE_IF4] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF5 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if5[HID7_REPORT_DESCRIPTOR_SIZE_IF5] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define HID7_REPORT_DESCRIPTOR_SIZE_IF6 24
WEAK __ALIGN_BEGIN const uint8_t HID7_ReportDescriptor_if6[HID7_REPORT_DESCRIPTOR_SIZE_IF6] __ALIGN_END = {

        // report descriptor for general input/output
        0x06, 0x00, 0xFF,  // Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        // Usage (0x01)
        0xA1, 0x01,        // Collection (Application)
        0x09, 0x02,        //   Usage (0x02)
        0x15, 0x00,        //   Logical Minimum (0)
        0x25, 0xFF,        //   Logical Maximum (255)
        0x75, 0x08,        //   Report Size (8)
        0x95, 0x10,        //   Report Count (16)
        0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        //   Usage (0x03)
        0x91, 0x02,        //   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               // End Collection
    
};

#define  HID7_CONFIG_DESCRIPTOR_SIZE  (233)
__ALIGN_BEGIN const uint8_t HID7_ConfigDescriptor [233] __ALIGN_END = {
    0x09,                                         /* bLength */
    USB_CONFIGURATION_DESCRIPTOR_TYPE,            /* bDescriptorType */
    0xe9, 0x00,                                   /* wTotalLength */
    0x07,                                         /* bNumInterfaces */
    0x01,                                         /* bConfigurationValue */
    0x00,                                         /* iConfiguration */
    0x80,                                         /* bmAttributes */
    0x64,                                         /* bMaxPower */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x00,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x81,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x01,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x40, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x01,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x82,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x02,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x02,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x83,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x03,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x03,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x84,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x04,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x20, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x04,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x85,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x05,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x05,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x86,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x06,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* Interface descriptor, len: 32*/
    0x09,                                         /* bLength */
    USB_INTERFACE_DESCRIPTOR_TYPE,                /* bDescriptorType */
    0x06,                                         /* bInterfaceNumber */
    0x00,                                         /* bAlternateSetting */
    0x02,                                         /* bNumEndpoints */
    0x03,                                         /* bInterfaceClass */
    0x00,                                         /* bInterfaceSubClass */
    0x00,                                         /* bInterfaceProtocol */
    0x00,                                         /* iInterface */
    /* HID descriptor  */
    0x09,                                         /* bLength */
    0x21,                                         /* bDescriptorType */
    0x11, 0x01,                                   /* bcdHID */
    0x00,                                         /* bCountryCode */
    0x01,                                         /* bNumDescriptors */
    0x22,                                         /* bDescriptorType1 */
    0x18, 0x00,                                   /* wDescriptorLength1 */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x87,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
    /* EndPoint descriptor */
    0x07,                                         /* bLength */
    USB_ENDPOINT_DESCRIPTOR_TYPE,                 /* bDescriptorType */
    0x07,                                         /* bEndpointAddress */
    0x03,                                         /* bmAttributes */
    0x10, 0x00,                                   /* wMaxPacketSize */
    0x01,                                         /* bInterval */
};

// Power status
#define HID7_DEV_STATUS0      (0)
#define HID7_DEV_STATUS1      (0)
#define HID7_DEV_STATUS    ((HID7_DEV_STATUS0) |(HID7_DEV_STATUS1) )

HID7_TXEP_MAX_SIZE
HID7_RXEP_MAX_SIZE

// Strings 
#define HID7_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define HID7_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN_BEGIN const uint8_t  HID7_StringDescriptor0 [4] __ALIGN_END = {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define HID7_STRING_DESCRIPTOR1_STR          "teeny usb"
#define HID7_STRING_DESCRIPTOR1_SIZE          (20)
WEAK __ALIGN_BEGIN const uint8_t  HID7_StringDescriptor1 [20] __ALIGN_END = {
    0x14,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
};
#define HID7_STRING_DESCRIPTOR2_STR          "teeny usb 7 HID demo"
#define HID7_STRING_DESCRIPTOR2_SIZE          (42)
WEAK __ALIGN_BEGIN const uint8_t  HID7_StringDescriptor2 [42] __ALIGN_END = {
    0x2a,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'e', 0x00,                                    /* wcChar1 */
    'e', 0x00,                                    /* wcChar2 */
    'n', 0x00,                                    /* wcChar3 */
    'y', 0x00,                                    /* wcChar4 */
    ' ', 0x00,                                    /* wcChar5 */
    'u', 0x00,                                    /* wcChar6 */
    's', 0x00,                                    /* wcChar7 */
    'b', 0x00,                                    /* wcChar8 */
    ' ', 0x00,                                    /* wcChar9 */
    '7', 0x00,                                    /* wcChar10 */
    ' ', 0x00,                                    /* wcChar11 */
    'H', 0x00,                                    /* wcChar12 */
    'I', 0x00,                                    /* wcChar13 */
    'D', 0x00,                                    /* wcChar14 */
    ' ', 0x00,                                    /* wcChar15 */
    'd', 0x00,                                    /* wcChar16 */
    'e', 0x00,                                    /* wcChar17 */
    'm', 0x00,                                    /* wcChar18 */
    'o', 0x00,                                    /* wcChar19 */
};
#define HID7_STRING_DESCRIPTOR3_STR          "tu123456"
#define HID7_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN_BEGIN const uint8_t  HID7_StringDescriptor3 [18] __ALIGN_END = {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'u', 0x00,                                    /* wcChar1 */
    '1', 0x00,                                    /* wcChar2 */
    '2', 0x00,                                    /* wcChar3 */
    '3', 0x00,                                    /* wcChar4 */
    '4', 0x00,                                    /* wcChar5 */
    '5', 0x00,                                    /* wcChar6 */
    '6', 0x00,                                    /* wcChar7 */
};
const uint8_t* const HID7_StringDescriptors[HID7_STRING_COUNT] = {
HID7_StringDescriptor0,
HID7_StringDescriptor1,
HID7_StringDescriptor2,
HID7_StringDescriptor3,
};

//  Device descriptors
const tusb_descriptors HID7_descriptors = {
  .device = HID7_DeviceDescriptor,
  .config = HID7_ConfigDescriptor,
  .strings = HID7_StringDescriptors,
  .string_cnt = HID7_STRING_COUNT,
#if defined(HAS_WCID)
#if defined(HID7_WCID_DESCRIPTOR_SIZE)
  .wcid_desc = HID7_WCIDDescriptor,
#else
  .wcid_desc = 0,  
#endif // HID7_WCID_DESCRIPTOR_SIZE)

#if defined(HID7_WCID_PROPERTIES_SIZE)
  .wcid_properties = HID7_WCIDProperties,
#else
  .wcid_properties = 0,  
#endif // HID7_WCID_PROPERTIES_SIZE

#endif // HAS_WCID
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device6  define end
/////////////////////////////////////////////////////////////////////





