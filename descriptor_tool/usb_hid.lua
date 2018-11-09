--[[ 
 Author:  admin@xtoolbox.org
 USB HID descriptor class
--]]
require("usb_common_desc")


function HIDDescriptor(param)
    local varData = {}
    param.bNumDescriptors = #param
    for i,v in ipairs(param) do
        local t = {}
        t["bDescriptorType"..i] = 0x22
        varData[#varData+1] = t
        t = {}
        t["wDescriptorLength"..i] = #v
        varData[#varData+1] = t
    end
    param.varData = varData
    
    local desc = Descriptor{
        {bLength              = DUMMY                        },
        {bDescriptorType      = 0x21                         },
        {bcdHID               = 0x111                        },
        {bCountryCode         = 0                            },
        {bNumDescriptors      = DUMMY                        },
    }(param)
    
    desc.outputHeader = desc.ident .. "/* HID descriptor " .. (param.alias or "") .. " */\n"
    desc.outputTail = ""
    return desc
end

local TAG = "HID: "

local function outputReportDescriptor(hid)
    local r = ""
    if hid.report then
        r = r .. string.gsub([[
#define $prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$ $size$
WEAK __ALIGN(2) const uint8_t $prefix$ReportDescriptor_if$ifn$[$prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$] = {
]], "%$(%w+)%$", {prefix = hid.prefix, ifn = hid.bInterfaceNumber, size = #hid.report })
        for i,v in ipairs(hid.report) do
            r = r .. string.format("0x%02x, ", v)
            if (i & 0xf) == 0 then r = r .."\n" end
        end
        r = r .. "};\n\n"
    end
    return r
end


function HID_InOut(size)
    local r = {-- report descriptor
        0x06, 0x00, 0xFF,  -- Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        -- Usage (0x01)
        0xA1, 0x01,        -- Collection (Application)
        0x09, 0x02,        --   Usage (0x02)
        0x15, 0x00,        --   Logical Minimum (0)
        0x25, 0xFF,        --   Logical Maximum (255)
        0x75, 0x08,        --   Report Size (8)
        0x95, size,        --   Report Count (64)
        0x81, 0x02,        --   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        --   Usage (0x03)
        0x91, 0x02,        --   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               -- End Collection
    }
    return r
end

function USB_HID(param)
    local Hid
    local ReadEp = param.ReadEp or param[1]
    local WriteEp = param.WriteEp or param[2]
    
    Hid = Interface{
        bInterfaceClass = 3,
        bInterfaceSubClass = param.isBoot and 1 or 0,
        bInterfaceProtocol = param.isKey and 1 or (param.isMouse and 2 or 0),
        HIDDescriptor{
            param.report,
            param.physical,
        },
        ReadEp,
        WriteEp,
    }
    Hid.report = param.report
    Hid.physical = param.physical
    Hid.extraDesc = outputReportDescriptor
    Hid.hasReport = true
    return Hid
end