/*
 * Name   :  tiny_usb_desc.c
 * Author :  admin@xtoolbox.org
 * Date   :  2018-11-09 17:37:12
 * Desc   :  This file is auto generate by the tiny_usb script tool
 *           Visit https://github.com/xtoolbox/tiny_usb for more info
 */

/*
  Input source name:  ../src/descriptor_demo/demo.lua  
  Content type is lua script:
  ------------- lua script begin ------------
-- DEMO USB descriptor for tiny USB stack
require("usb_cdc_acm")
require("usb_hid")
return {
-- Demo descriptor of Bulk device
Device {
    strManufacture = "tiny usb",
    strProduct = "tiny usb bulk demo",
    strSerial = "tu123456",
    idVendor = 0x0483,       -- VID PID for ST-link, it will install signed WinUSB driver
    idProduct = 0x3748,
    prefix = "BULK",
    Config {
        bMaxPower = 100,
        SelfPower = true,
        RemoteWakeup = true,
        Interface{
            EndPoint(IN(1),  BulkDouble, 64),
            EndPoint(OUT(2), BulkDouble, 64),
        },
   }
},

-- Demo descriptor of CDC device
Device {
    strManufacture = "tiny usb",
    strProduct = "tiny usb cdc demo",
    strSerial = "tu123456",
    idVendor = 0x03EB,
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
    idVendor = 0x1234,
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
/////////////////////////////////////////////////////////////////////
//// Descriptor for device1 define begin
/////////////////////////////////////////////////////////////////////
#define  BULK_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN(2)  const uint8_t BULK_DeviceDescriptor [18] = {
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
__ALIGN(2)  const uint8_t BULK_ConfigDescriptor [32] = {
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
#define BULK_DEV_STATUS0      USB_CONFIG_SELF_POWERED
#define BULK_DEV_STATUS1      USB_CONFIG_REMOTE_WAKEUP
#define BULK_DEV_STATUS    ((BULK_DEV_STATUS0) |(BULK_DEV_STATUS1) )

BULK_TXEP_MAX_SIZE
BULK_RXEP_MAX_SIZE

// Strings 
#define BULK_STRING_DESCRIPTOR0_STR          "\x09\x04"
#define BULK_STRING_DESCRIPTOR0_SIZE          (4)
WEAK __ALIGN(2) const uint8_t  BULK_StringDescriptor0 [4]= {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define BULK_STRING_DESCRIPTOR1_STR          "tiny usb"
#define BULK_STRING_DESCRIPTOR1_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  BULK_StringDescriptor1 [18]= {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
};
#define BULK_STRING_DESCRIPTOR2_STR          "tiny usb bulk demo"
#define BULK_STRING_DESCRIPTOR2_SIZE          (38)
WEAK __ALIGN(2) const uint8_t  BULK_StringDescriptor2 [38]= {
    0x26,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    ' ', 0x00,                                    /* wcChar8 */
    'b', 0x00,                                    /* wcChar9 */
    'u', 0x00,                                    /* wcChar10 */
    'l', 0x00,                                    /* wcChar11 */
    'k', 0x00,                                    /* wcChar12 */
    ' ', 0x00,                                    /* wcChar13 */
    'd', 0x00,                                    /* wcChar14 */
    'e', 0x00,                                    /* wcChar15 */
    'm', 0x00,                                    /* wcChar16 */
    'o', 0x00,                                    /* wcChar17 */
};
#define BULK_STRING_DESCRIPTOR3_STR          "tu123456"
#define BULK_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  BULK_StringDescriptor3 [18]= {
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
const uint8_t* const BULK_StringDescriptors[BULK_STRING_COUNT] = {
BULK_StringDescriptor0,
BULK_StringDescriptor1,
BULK_StringDescriptor2,
BULK_StringDescriptor3,
};

//  Device descriptors
const tusb_descriptors BULK_descriptors = {
  .device = BULK_DeviceDescriptor,
  .config = BULK_ConfigDescriptor,
  .strings = BULK_StringDescriptors,
  .string_cnt = BULK_STRING_COUNT,
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device1  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device2 define begin
/////////////////////////////////////////////////////////////////////
#define  CDC_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN(2)  const uint8_t CDC_DeviceDescriptor [18] = {
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
__ALIGN(2)  const uint8_t CDC_ConfigDescriptor [67] = {
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
WEAK __ALIGN(2) const uint8_t  CDC_StringDescriptor0 [4]= {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define CDC_STRING_DESCRIPTOR1_STR          "tiny usb"
#define CDC_STRING_DESCRIPTOR1_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  CDC_StringDescriptor1 [18]= {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
};
#define CDC_STRING_DESCRIPTOR2_STR          "tiny usb cdc demo"
#define CDC_STRING_DESCRIPTOR2_SIZE          (36)
WEAK __ALIGN(2) const uint8_t  CDC_StringDescriptor2 [36]= {
    0x24,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    ' ', 0x00,                                    /* wcChar8 */
    'c', 0x00,                                    /* wcChar9 */
    'd', 0x00,                                    /* wcChar10 */
    'c', 0x00,                                    /* wcChar11 */
    ' ', 0x00,                                    /* wcChar12 */
    'd', 0x00,                                    /* wcChar13 */
    'e', 0x00,                                    /* wcChar14 */
    'm', 0x00,                                    /* wcChar15 */
    'o', 0x00,                                    /* wcChar16 */
};
#define CDC_STRING_DESCRIPTOR3_STR          "tu123456"
#define CDC_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  CDC_StringDescriptor3 [18]= {
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
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device2  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device3 define begin
/////////////////////////////////////////////////////////////////////
#define  CDC7_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN(2)  const uint8_t CDC7_DeviceDescriptor [18] = {
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
__ALIGN(2)  const uint8_t CDC7_ConfigDescriptor [471] = {
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
WEAK __ALIGN(2) const uint8_t  CDC7_StringDescriptor0 [4]= {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define CDC7_STRING_DESCRIPTOR1_STR          "tiny usb"
#define CDC7_STRING_DESCRIPTOR1_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  CDC7_StringDescriptor1 [18]= {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
};
#define CDC7_STRING_DESCRIPTOR2_STR          "tiny usb cdc7 demo"
#define CDC7_STRING_DESCRIPTOR2_SIZE          (38)
WEAK __ALIGN(2) const uint8_t  CDC7_StringDescriptor2 [38]= {
    0x26,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    ' ', 0x00,                                    /* wcChar8 */
    'c', 0x00,                                    /* wcChar9 */
    'd', 0x00,                                    /* wcChar10 */
    'c', 0x00,                                    /* wcChar11 */
    '7', 0x00,                                    /* wcChar12 */
    ' ', 0x00,                                    /* wcChar13 */
    'd', 0x00,                                    /* wcChar14 */
    'e', 0x00,                                    /* wcChar15 */
    'm', 0x00,                                    /* wcChar16 */
    'o', 0x00,                                    /* wcChar17 */
};
#define CDC7_STRING_DESCRIPTOR3_STR          "tu123456"
#define CDC7_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  CDC7_StringDescriptor3 [18]= {
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
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device3  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device4 define begin
/////////////////////////////////////////////////////////////////////
#define  HID_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN(2)  const uint8_t HID_DeviceDescriptor [18] = {
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
WEAK __ALIGN(2) const uint8_t HID_ReportDescriptor_if0[HID_REPORT_DESCRIPTOR_SIZE_IF0] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x40, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define  HID_CONFIG_DESCRIPTOR_SIZE  (41)
__ALIGN(2)  const uint8_t HID_ConfigDescriptor [41] = {
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
WEAK __ALIGN(2) const uint8_t  HID_StringDescriptor0 [4]= {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define HID_STRING_DESCRIPTOR1_STR          "tiny usb"
#define HID_STRING_DESCRIPTOR1_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  HID_StringDescriptor1 [18]= {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
};
#define HID_STRING_DESCRIPTOR2_STR          "tiny usb HID demo"
#define HID_STRING_DESCRIPTOR2_SIZE          (36)
WEAK __ALIGN(2) const uint8_t  HID_StringDescriptor2 [36]= {
    0x24,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    ' ', 0x00,                                    /* wcChar8 */
    'H', 0x00,                                    /* wcChar9 */
    'I', 0x00,                                    /* wcChar10 */
    'D', 0x00,                                    /* wcChar11 */
    ' ', 0x00,                                    /* wcChar12 */
    'd', 0x00,                                    /* wcChar13 */
    'e', 0x00,                                    /* wcChar14 */
    'm', 0x00,                                    /* wcChar15 */
    'o', 0x00,                                    /* wcChar16 */
};
#define HID_STRING_DESCRIPTOR3_STR          "tu123456"
#define HID_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  HID_StringDescriptor3 [18]= {
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
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device4  define end
/////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////
//// Descriptor for device5 define begin
/////////////////////////////////////////////////////////////////////
#define  HID7_DEVICE_DESCRIPTOR_SIZE  (18)
__ALIGN(2)  const uint8_t HID7_DeviceDescriptor [18] = {
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
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if0[HID7_REPORT_DESCRIPTOR_SIZE_IF0] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x40, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF1 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if1[HID7_REPORT_DESCRIPTOR_SIZE_IF1] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x20, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF2 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if2[HID7_REPORT_DESCRIPTOR_SIZE_IF2] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x20, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF3 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if3[HID7_REPORT_DESCRIPTOR_SIZE_IF3] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x20, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF4 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if4[HID7_REPORT_DESCRIPTOR_SIZE_IF4] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x10, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF5 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if5[HID7_REPORT_DESCRIPTOR_SIZE_IF5] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x10, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define HID7_REPORT_DESCRIPTOR_SIZE_IF6 24
WEAK __ALIGN(2) const uint8_t HID7_ReportDescriptor_if6[HID7_REPORT_DESCRIPTOR_SIZE_IF6] = {
0x06, 0x00, 0xff, 0x09, 0x01, 0xa1, 0x01, 0x09, 0x02, 0x15, 0x00, 0x25, 0xff, 0x75, 0x08, 0x95, 
0x10, 0x81, 0x02, 0x09, 0x03, 0x91, 0x02, 0xc0, };

#define  HID7_CONFIG_DESCRIPTOR_SIZE  (233)
__ALIGN(2)  const uint8_t HID7_ConfigDescriptor [233] = {
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
WEAK __ALIGN(2) const uint8_t  HID7_StringDescriptor0 [4]= {
    0x04,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    0x09, 0x04,                                   /* wLangID0 */
};
#define HID7_STRING_DESCRIPTOR1_STR          "tiny usb"
#define HID7_STRING_DESCRIPTOR1_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  HID7_StringDescriptor1 [18]= {
    0x12,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
};
#define HID7_STRING_DESCRIPTOR2_STR          "tiny usb 7 HID demo"
#define HID7_STRING_DESCRIPTOR2_SIZE          (40)
WEAK __ALIGN(2) const uint8_t  HID7_StringDescriptor2 [40]= {
    0x28,                                         /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   /* bDescriptorType */
    't', 0x00,                                    /* wcChar0 */
    'i', 0x00,                                    /* wcChar1 */
    'n', 0x00,                                    /* wcChar2 */
    'y', 0x00,                                    /* wcChar3 */
    ' ', 0x00,                                    /* wcChar4 */
    'u', 0x00,                                    /* wcChar5 */
    's', 0x00,                                    /* wcChar6 */
    'b', 0x00,                                    /* wcChar7 */
    ' ', 0x00,                                    /* wcChar8 */
    '7', 0x00,                                    /* wcChar9 */
    ' ', 0x00,                                    /* wcChar10 */
    'H', 0x00,                                    /* wcChar11 */
    'I', 0x00,                                    /* wcChar12 */
    'D', 0x00,                                    /* wcChar13 */
    ' ', 0x00,                                    /* wcChar14 */
    'd', 0x00,                                    /* wcChar15 */
    'e', 0x00,                                    /* wcChar16 */
    'm', 0x00,                                    /* wcChar17 */
    'o', 0x00,                                    /* wcChar18 */
};
#define HID7_STRING_DESCRIPTOR3_STR          "tu123456"
#define HID7_STRING_DESCRIPTOR3_SIZE          (18)
WEAK __ALIGN(2) const uint8_t  HID7_StringDescriptor3 [18]= {
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
};
/////////////////////////////////////////////////////////////////////
//// Descriptor for device5  define end
/////////////////////////////////////////////////////////////////////





