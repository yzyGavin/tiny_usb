-- xtoolbox ui init file
require("usb_hid")
require("usb_cdc_acm")
require("gen_decriptor")

local tr = tr or function(s, ctx) return s end

class "EPView" (QFrame)
function EPView:__init(name, optional)
    QFrame.__init(self)
    name = name or ""
    local w = 40
    self.packetSize = QLineEdit("64"){maxW = w, minW = w}
    self.attrMap = {
        "Interrupt",
        "Control",
        "Bulk",
        "BulkDouble",
        "ISO",
    }
    self.optional = optional
    self.attr = QComboBox{ self.attrMap }
    self.dir = QComboBox{{
        "IN",
        "OUT",
    }}
    self.holder = QLabel(""){maxW = 30, minW = 30}
    if optional then
        self.holder.maxW = 1
        self.holder.minW = 1
        self.name = QCheckBox(name) {maxW = 89, minW = 89}
        self.name.checked = true
    else
        self.name = QLabel(name) {maxW = 60, minW = 60}
    end
    self.attr.currentIndex = 0
    self.addr = QLineEdit("1"){maxW = w, minW = w}
    self.interval = QLineEdit("1") {maxW = w, minW = w}
    self.name.toggled = function()
        local e = self.name.checked
        self.addr.enabled = e
        self.dir.enabled = e
        self.attr.enabled = e
        self.packetSize.enabled = e
        self.interval.enabled = e
    end
    self.layout = QHBoxLayout {
            self.holder,
            self.name,
            --QLabel(tr("Addr","EP")), 
            self.addr, self.dir,
            --QLabel(tr("Type","EP")),
            self.attr,
            QLabel(tr("Max Pkt","EP")), self.packetSize,
            QLabel(tr("Interval", "EP")), self.interval
    }
    self.layout.contentsMargins = QMargins(0,0,0,0)
end
function EPView:setEp(addr, attr, pktSize, interval)
    pktSize = pktSize or 64
    interval = interval or 1
    self.addr.text = tostring(addr&0x7f)
    if (addr & 0x80) == 0 then
        self.dir.currentIndex = 1
    else
        self.dir.currentIndex = 0
    end
    for i,v in ipairs(self.attrMap) do
        if attr == v then self.attr.currentIndex = i - 1 end
    end
    self.packetSize.text = tostring(pktSize)
    self.interval.text = tostring(interval)
end
function EPView:getAddr()
    return (tonumber(self.addr.text) & 0x7f) + (self.dir.currentIndex == 1 and 0 or 0x80)
end
function EPView:makeDesc()
    return EndPoint{
        bEndpointAddress = self:getAddr(),
        bmAttributes = _G[self.attr.currentText],
        wMaxPacketSize = tonumber(self.packetSize.text),
        bInterval = tonumber(self.interval.text),
    }
end

local minEp = nil
function freeEp(ep)
    if minEp and minEp[ep] then minEp[ep] = false end
end
function getMinEp()
    if not minEp then
        minEp = {}
        for i=1, 64 do minEp[i] = false end
    end
    for i=1,#minEp do
        if not minEp[i] then
            minEp[i] = true
            return i
        end
    end
end

class "IfView" (QFrame)
function IfView:__init(p, name)
    QFrame.__init(self,p)
    name = name or "Generic"
    self.ifname = QLabel("")
    self.name = QLineEdit(){ placeHolderText = tr("Set Interface Name or leave empty") }
    self.btnRemove = QPushButton(tr("Remove")) {maxH = 30}
    self.layout = QVBoxLayout{
        QHBoxLayout{self.ifname,QLabel(" - " .. name), self.name, self.btnRemove},
    }
    self.btnRemove.clicked = function()
        if self.removeEp then self.removeEp() end
        if self.removeCallback then
            self.removeCallback(self)
        end
    end
    self.layout.contentsMargins = QMargins(0,0,0,0)
end

function IfView:initIf(iInterface, removeCallback)
    self.ifname.text = "Interface " .. (iInterface - 1)
    self.ifIndex = iInterface
    self.removeCallback = removeCallback
end
function IfView:strInterface()
    if self.name.text == "" then return nil end
    return self.name.text
end


class "CDCView"(IfView)
function CDCView:__init(p)
    IfView.__init(self,p, "CDC")
    self.cdcCtrl = EPView(tr("Control","CDC"))
    self.cdcRead = EPView(tr("Read","CDC"))
    self.cdcWrite = EPView(tr("Write","CDC"))
    self.layout:addWidget(self.cdcCtrl)
    self.layout:addWidget(self.cdcRead)
    self.layout:addWidget(self.cdcWrite)
    local e = getMinEp()
    self.cdcCtrl:setEp(0x80 + getMinEp(), "Interrupt", 8)
    self.cdcRead:setEp(0x80 + e, "Bulk")
    self.cdcWrite:setEp(e, "Bulk")
    self.removeEp = function()
        freeEp(self.cdcCtrl:getAddr()&0x7f)
        freeEp(self.cdcRead:getAddr()&0x7f)
        freeEp(self.cdcWrite:getAddr()&0x7f)
    end
end

function CDCView:makeDesc()
    return CDC_ACM{
        strFunction = self:strInterface(),
        CtrlEp = self.cdcCtrl:makeDesc(),
        ReadEp = self.cdcRead:makeDesc(),
        WriteEp = self.cdcWrite:makeDesc(),
    }
end

class "HIDView"(IfView)
function HIDView:__init(p)
    IfView.__init(self,p,"HID")
    self.epRead = EPView(tr("Read","HID"))
    self.epWrite = EPView(tr("Write","HID"), true)
    self.rptType = QComboBox{{
        "InOut",
        "BootMouse",
        "BootKeyBoard",
        "UserDefine",
    }}
    self.ioSize = QLineEdit("64") {maxW = 40, minW = 40}
    self.btnEditRpt = QPushButton(tr("Edit...", "HID")){enabled = false, maxH = 30}
    self.userRpt = HID_ReportTemp()
    
    self.rptType.currentIndexChanged = function()
        local idx = self.rptType.currentText
        self.ioSize.enabled = idx == "InOut"
        self.btnEditRpt.enabled = idx == "UserDefine"
    end
    self.rptType.currentIndex = 0
    
    self.btnEditRpt.clicked = function()
        local dlg = QDialog(self)
        local t = QLuaEdit(){minW = 1000, minH = 600}
        local btnOk = QPushButton(tr("OK"))
        btnOk.clicked = function() dlg:accept() end
        t.plainText = self.userRpt
        dlg.layout = QVBoxLayout{t, QHBoxLayout{ btnOk }}
        if dlg:exec() == 1 then self.userRpt = t.plainText end
    end
    
    local e = getMinEp()
    self.epRead:setEp(0x80+e, "Interrupt", 64, 1)
    self.epWrite:setEp(e, "Interrupt", 64, 1)
    self.layout:addWidget(self.epRead)
    self.layout:addWidget(self.epWrite)
    self.layout:addLayout(QHBoxLayout{
        QLabel(tr("    Report desc")), self.rptType, QLabel("Size:"), self.ioSize, self.btnEditRpt
    })
    self.removeEp = function()
        freeEp(self.epRead:getAddr() & 0x7f)
        freeEp(self.epWrite:getAddr() & 0x7f)
    end
end

function HIDView:makeDesc()
    local r = {
        strInterface = self:strInterface(),
        ReadEp = self.epRead:makeDesc(),
        WriteEp = self.epWrite:makeDesc(),
    }
    if self.rptType.currentText == "InOut" then
        r.report = HID_InOut(tonumber(self.ioSize.text) or 0x40)
    elseif self.rptType.currentText == "BootKeyBoard" then
        r.report = HID_BootKeyBoard()
    elseif self.rptType.currentText == "BootMouse" then
        r.report = HID_BootMouse()
    else
        r.report = loadstring(self.userRpt)() or {0}
    end
    return USB_HID(r)
end

class "GenericView" (IfView)
function GenericView:__init(p)
    IfView.__init(self, p)
    self.btnAdd = QPushButton(tr("Add EndPoint")){maxH = 30}
    self.chkWCIDWinUSB = QCheckBox(tr("WCID WinUSB"))
    self.layout:addLayout(QHBoxLayout{
        self.btnAdd, self.chkWCIDWinUSB, QLabel(""), strech = "0,0,1",
    })
    self.eps = {
        EPView(tr("Generic")),
    }
    self.eps[1]:setEp(getMinEp(), "Bulk", 64, 0)
    self.layout:addWidget(self.eps[1])
    self.btnAdd.clicked = function()
        local epv = EPView(tr("Generic"), true)
        epv:setEp(getMinEp(), "Bulk", 64, 0)
        epv.name.toggled = function()
            if not epv.name.checked then
                local idx
                for i, v in ipairs(self.eps) do
                    if v == epv then
                        idx = i
                        break
                    end
                end
                local v = table.remove(self.eps, idx)
                if v then
                    v:close()
                    self.layout:removeWidget(v)
                    self:resize(self.sizeHint)
                    if self.reset_back then self.reset_back() end
                end
            end
        end
        self.layout:addWidget(epv)
        self.eps[#self.eps+1] = epv
        self:resize(self.sizeHint)
        if self.reset_back then self.reset_back() end
    end
end

function GenericView:makeDesc()
    local param = {
        strInterface = self:strInterface(),
    }
    if self.chkWCIDWinUSB.checked then param.WCID = WinUSB end
    for i,v in ipairs(self.eps) do
        param[#param+1] = v:makeDesc()
    end
    return Interface(param)
end

class "UsbDescView" (QFrame)
function UsbDescView:__init(parent)
    QFrame.__init(self, parent)
    self.ifs = parent.ifs
    self.editVid = QLineEdit("0x1234"){
       placeHolderText = "VID",
    }
    self.editPid = QLineEdit("0x1234"){
       placeHolderText = "PID",
    }
    self.editVendor = QLineEdit("Tiny USB Desc Tool"){
       placeHolderText = tr("Manufacture string or leave empty"),
    }
    self.editProduct = QLineEdit("Tiny USB DEMO"){
       placeHolderText = tr("Product string or leave empty"),
    }
    self.editSerial = QLineEdit("TinyUSB000001"){
       placeHolderText = tr("Serial string or leave empty"),
    }
    self.chkSelfPower = QCheckBox(tr("Self Power"))
    self.chkRemoteWakeup = QCheckBox(tr("Remote Wakeup"))
    self.maxPower = QLineEdit("100"){inputMask = "999"}
    self.chkSelfPower.toggled = function()
        self.maxPower.enabled = not self.chkSelfPower.checked
    end
    self.btnViewDesc = QPushButton(tr("View &Desc...")){maxH = 30}
    self.btnViewEpInit = QPushButton(tr("View &EP...")){maxH = 30}
    self.layout = QVBoxLayout{
        QHBoxLayout{
            QLabel("VID"), self.editVid, QLabel("PID"), self.editPid,
        },
        QFormLayout{
            {tr("Vendor Str"), self.editVendor},
            {tr("Product Str"), self.editProduct},
            {tr("Serial Str"), self.editSerial},
        },
        --QHBoxLayout{QLabel(tr("Vendor Str")), self.editVendor},
        --QHBoxLayout{QLabel(tr("Product Str")), self.editProduct},
        --QHBoxLayout{QLabel(tr("Serial Str")), self.editSerial},
        QHBoxLayout{
            self.chkSelfPower, self.chkRemoteWakeup,
            QLabel(tr("Max Power")), self.maxPower, QLabel("x2mA"),
        },
        QHBoxLayout{
            self.btnViewDesc, self.btnViewEpInit
        },
    }
    self.layout.contentsMargins = QMargins(0,0,0,0)
    
    self.btnViewDesc.clicked = function()
        local t = QTextEdit()
        t.plainText = tostring(self:makeDesc())
        mdiArea:addSubWindow(t):showMaximized()
    end
    
    self.btnViewEpInit.clicked = function()
        local desc = self:makeDesc()
        local t = QTextEdit()
        local ep = EndPointInfo(desc, 7, 1024):getInitCode()
        t.plainText = ep
        mdiArea:addSubWindow(t):showMaximized()
    end
end
local function str(edit)
        if edit.text == "" then return nil end
        return edit.text
end
function UsbDescView:makeDesc()
    local cfg = {}
    cfg.bMaxPower = tonumber(self.maxPower.text)
    cfg.SelfPower = self.chkSelfPower.checked
    cfg.RemoteWakeup = self.chkRemoteWakeup.checked
    for i,v in ipairs(self.ifs) do
        cfg[#cfg+1] = v:makeDesc()
    end
    local desc = Device {
        strManufacture = str(self.editVendor),
        strProduct = str(self.editProduct),
        strSerial = str(self.editSerial),
        idVendor = tonumber(self.editVid.text) or 0,
        idProduct = tonumber(self.editPid.text) or 0,
        prefix = "TinyUI",
        Config (cfg)
    }
    return desc
end

local log = function(...)
    local r = ""
    for i,v in ipairs({...}) do r = r .. tostring(v) .. "  " end
    logEdit:append(r)
end


local addView
local back = QFrame()
back.ifs = {}
local sa = QScrollArea()
local udv = UsbDescView(back)
local btnAddIf = QPushButton(tr("Add Interface"), back){w = 160}
btnAddIf.menu = QMenu{
    QAction(tr("CDC")) {
        triggered = function() addView(CDCView) end
    },
    QAction(tr("HID")){
        triggered = function() addView(HIDView) end
    },
    QAction(tr("Generic")){
        triggered = function() addView(GenericView) end
    },
}

local udvSize = udv.sizeHint
udv.x = 10
udv.y = 10
udv:resize(udvSize)
local btnSize = btnAddIf.sizeHint
local function reset_back()
    local w = udvSize.w + udv.x
    local h = udvSize.h + udv.y
    local margin = 10
    local lMargin = 5
    for i,v in ipairs(back.ifs) do
        h = h + margin
        v.x = lMargin
        v.y = h
        h = h + v.sizeHint.h
        if v.sizeHint.w > w then w = v.sizeHint.w end
    end
    h = h + margin + 10
    btnAddIf.x = 5
    btnAddIf.y = h
    h = h + btnSize.h
    back:resize(  QSize(w + lMargin*2, h+30) )
    --sa:ensureWidgetVisible(btnAddIf)
end

local function onRemove(view)
    local idx
    for i,v in ipairs(back.ifs) do
        if v == view then idx = i end
    end
    local v = table.remove(back.ifs, idx)
    if v then
        v:close()
        reset_back()
    end
    for i,v in ipairs(back.ifs) do
        if v.initIf then v:initIf(i, onRemove) end
    end
end

addView = function(view)
    local v = view(back)
    v.visible = true
    v.reset_back = reset_back
    back.ifs[#back.ifs+1] = v
    if v.initIf then v:initIf(#back.ifs, onRemove) end
    reset_back()
end

reset_back()



sa.widget = back
--logEdit:append(""..udv.sizeHint.w ..",".. udv.sizeHint.h)



local sw = mdiArea:addSubWindow(sa)
sw.w = 800
sw.h = 600
sw:showMaximized()