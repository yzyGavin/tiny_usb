-- language.lua
local chs = {
["&USB Descriptor"] =  "USB������(&U)", 
["&New Device"] =  "�½��豸(&N)",
["Preview &Descriptor"] =  "Ԥ��������(&D)",
["Preview &EP Define"] =  "Ԥ���˵㶨��(&E)",
["&Generate Code"]     =  "���ɴ���(&G)",
["Generate Code &All"] =  "����ȫ������(&A)",
["USB &Driver"] =  "USB����(&D)",
["Priview &Inf"] =  "Ԥ��INF�ļ�(&I)",
["Priview &Inf All"] =  "Ԥ��ȫ��INF�ļ�(&)",
["Generate &Inf"] =  "����INF�ļ�(&I)",
["Generate Inf &All"] =  "����ȫ��INF�ļ�(&I)",
["&Window"] =  "����(&W)",
["&Cascade"] =  "���(&C)",
["&Tile"] =  "ƽ��(&T)",
["Clear &Log"] =  "�����־(&L)",
["Manufacture string or leave empty"] =  "���������� �� ����",
["Product string or leave empty"] =  "��Ʒ���� �� ����",
["Serial string or leave empty"] =  "���к� �� ����",
["Self Power"] =  "�Թ���",
["Remote Wakeup"] =  "Զ�̻���",
["Max EP No."] =  "���˵��",
["USB Memory size"] =  "USBģ���ڴ��С",
["Vendor Str"] =  "��������",
["Product Str"] =  "��Ʒ��",
["Serial Str"] =  "���к�",
["Max Power"] =  "������",
["Add Interface"] =  "����豸�ӿ�",
["CDC"] =  "CDC����",
["HID"] =  "HID�����豸",
["Generic"] =  "�Զ���ͨ���豸",
["Set Interface Name or leave empty"] = "�ӿ����� �� ����",
["Remove"] =  "ɾ���ӿ�",
["Control"] =  "���ƶ˵�",
["Max Pkt"] =  "������",
["Interval"] =  "���",
["Read"] =  "���˵�",
["Write"] =  "д�˵�",
["Edit..."] =  "�༭...",
["    Report desc"] =  "    ����������",
["Add EndPoint"] =  "��Ӷ˵�",
["WCID WinUSB"] =  "WinUSB����",
["PktSize"] = "�˵�0������",
["What is WCID ?"] = "ʲô��WCID�����豸?",
["GenEp"] = "ͨ�ö˵�",
["Trans/Frame"] = "��ÿ֡",
__name__ = "CHS",
__context__ = {},
}

local curLang = chs

local logI = function(...)
    local r = ""
    for i,v in pairs({...}) do
        r = r .. tostring(v) .. " "
    end
    logEdit:append(r)
end


local s1,s2 = QDate.currentDate():toString("dddd"):find("����")
if s1 then
    curLang = chs
else
    curLang = nil
end

_G.tr = function(text, context)
    local trans = curLang
    if not trans then return text end
    if trans and context and trans.__context__[context] then
        trans = trans.__context__[context]
    end
    if trans[text] then return trans[text] end
    trans[text] = text
    logI('["'..text..'"] = ', "not translate in language", curLang.__name__,"with context: ", context)
    return text
end