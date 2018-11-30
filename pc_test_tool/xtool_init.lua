function tr(x) return x end
function log(...)
    local r = ""
    for i,v in ipairs({...}) do
        r = r .. tostring(v) .. " "
    end
end
require("hidview")
require("usbview")
hv = HIDView(0x1720,0x2410)
hid = hv.param.hid
--mdiArea:addSubWindow(hv):show()

mdiArea:addSubWindow(USBView(0x0483)):show()
