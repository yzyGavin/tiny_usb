-- usb_hid.lua
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
    hid.declare = ""
    if hid.report then
        hid.declare = string.gsub([[
#define $prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$ $size$
extern const uint8_t $prefix$ReportDescriptor_if$ifn$[$prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$];
]], "%$(%w+)%$", {prefix = hid.prefix, ifn = hid.bInterfaceNumber, size = #hid.report })
        
        r = r .. string.gsub([[
#define $prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$ $size$
WEAK __ALIGN_BEGIN const uint8_t $prefix$ReportDescriptor_if$ifn$[$prefix$REPORT_DESCRIPTOR_SIZE_IF$ifn$] __ALIGN_END = {
]], "%$(%w+)%$", {prefix = hid.prefix, ifn = hid.bInterfaceNumber, size = #hid.report })
        if hid.report.text then
        r = r .. "\n" .. hid.report.text .. "\n"
        else
        for i,v in ipairs(hid.report) do
            r = r .. string.format("0x%02x, ", v)
            if (i & 0xf) == 0 then r = r .."\n" end
        end
        end
        r = r .. "};\n\n"
    end
    return r
end

function HID_BuildReport(str)
    str = string.gsub(str, "//", "--")
    local r = load( "return { ".. str .. "}")() or {0}
    r.text = string.gsub(str, "%-%-", "//")
    return r
end

function HID_InOut(size)
    local str = string.format("0x95, 0x%02x,", size)
    local r = [[
        -- report descriptor for general input/output
        0x06, 0x00, 0xFF,  -- Usage Page (Vendor Defined 0xFF00)
        0x09, 0x01,        -- Usage (0x01)
        0xA1, 0x01,        -- Collection (Application)
        0x09, 0x02,        --   Usage (0x02)
        0x15, 0x00,        --   Logical Minimum (0)
        0x25, 0xFF,        --   Logical Maximum (255)
        0x75, 0x08,        --   Report Size (8)
        ]]..str..
                 [[        --   Report Count (]]..tostring(size)..[[)
        0x81, 0x02,        --   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
        0x09, 0x03,        --   Usage (0x03)
        0x91, 0x02,        --   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
        0xC0               -- End Collection
    ]]
    return HID_BuildReport(r)
end

function HID_BootKeyBoard()
    local r = [[
        --  Boot keyboad report descriptor
        0x05, 0x01,     -- USAGE_PAGE (Generic Desktop)
        0x09, 0x06,     -- USAGE (Keyboard)
        0xa1, 0x01,     -- COLLECTION (Application)
        0x05, 0x07,     --   USAGE_PAGE (Keyboard)
        0x19, 0xe0,     --   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,     --   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,     --   LOGICAL_MINIMUM (0)
        0x25, 0x01,     --   LOGICAL_MAXIMUM (1)
        0x75, 0x01,     --   REPORT_SIZE (1)
        0x95, 0x08,     --   REPORT_COUNT (8)
        0x81, 0x02,     --   INPUT (Data,Var,Abs)
        0x95, 0x01,     --   REPORT_COUNT (1)
        0x75, 0x08,     --   REPORT_SIZE (8)
        0x81, 0x03,     --   INPUT (Cnst,Var,Abs)
        0x95, 0x05,     --   REPORT_COUNT (5)
        0x75, 0x01,     --   REPORT_SIZE (1)
        0x05, 0x08,     --   USAGE_PAGE (LEDs)
        0x19, 0x01,     --   USAGE_MINIMUM (Num Lock)
        0x29, 0x05,     --   USAGE_MAXIMUM (Kana)
        0x91, 0x02,     --   OUTPUT (Data,Var,Abs)
        0x95, 0x01,     --   REPORT_COUNT (1)
        0x75, 0x03,     --   REPORT_SIZE (3)
        0x91, 0x03,     --   OUTPUT (Cnst,Var,Abs)
        0x95, 0x06,     --   REPORT_COUNT (6)
        0x75, 0x08,     --   REPORT_SIZE (8)
        0x15, 0x00,     --   LOGICAL_MINIMUM (0)
        0x25, 0x65,     --   LOGICAL_MAXIMUM (101)
        0x05, 0x07,     --   USAGE_PAGE (Keyboard)
        0x19, 0x00,     --   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,     --   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,     --   INPUT (Data,Ary,Abs)
        0xc0            -- END_COLLECTION
    ]]
    return HID_BuildReport(r) 
end
function HID_BootMouse()
    local r = [[
        --  Boot Mouse report descriptor
        0x05, 0x01,     -- USAGE_PAGE (Generic Desktop)
        0x09, 0x02,     -- USAGE (Mouse)
        0xa1, 0x01,     -- COLLECTION (Application)
        0x09, 0x01,     --   USAGE (Pointer)
        0xa1, 0x00,     --   COLLECTION (Physical)
        0x05, 0x09,     --     USAGE_PAGE (Button)
        0x19, 0x01,     --     USAGE_MINIMUM (Button 1)
        0x29, 0x03,     --     USAGE_MAXIMUM (Button 3)
        0x15, 0x00,     --     LOGICAL_MINIMUM (0)
        0x25, 0x01,     --     LOGICAL_MAXIMUM (1)
        0x95, 0x03,     --     REPORT_COUNT (3)
        0x75, 0x01,     --     REPORT_SIZE (1)
        0x81, 0x02,     --     INPUT (Data,Var,Abs)
        0x95, 0x01,     --     REPORT_COUNT (1)
        0x75, 0x05,     --     REPORT_SIZE (5)
        0x81, 0x03,     --     INPUT (Cnst,Var,Abs)
        0x05, 0x01,     --     USAGE_PAGE (Generic Desktop)
        0x09, 0x30,     --     USAGE (X)
        0x09, 0x31,     --     USAGE (Y)
        0x15, 0x81,     --     LOGICAL_MINIMUM (-127)
        0x25, 0x7f,     --     LOGICAL_MAXIMUM (127)
        0x75, 0x08,     --     REPORT_SIZE (8)
        0x95, 0x02,     --     REPORT_COUNT (2)
        0x81, 0x06,     --     INPUT (Data,Var,Rel)
        0xc0,           --   END_COLLECTION
        0xc0            -- END_COLLECTION
    ]]
    return HID_BuildReport(r)
end
function HID_ReportTemp()
local r = [[
    -- Temaple report
    0x06, 0x00, 0xFF,  -- Usage Page (Vendor Defined 0xFF00)
    0x09, 0x01,        -- Usage (0x01)
    0xA1, 0x01,        -- Collection (Application)
    0x09, 0x02,        --   Usage (0x02)
    0x15, 0x00,        --   Logical Minimum (0)
    0x25, 0xFF,        --   Logical Maximum (255)
    0x75, 0x08,        --   Report Size (8)
    0x95, 0x40,        --   Report Count (64)
    0x81, 0x02,        --   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x03,        --   Usage (0x03)
    0x91, 0x02,        --   Output (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0               -- End Collection
]]
    return HID_BuildReport(r)
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