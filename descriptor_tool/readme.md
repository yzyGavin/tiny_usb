# Tiny USB描述符工具

## 特性 Features

1. 根据配置自动生成USB描述符和端点初始化代码 Auto generate USB descriptors and Endpoint initial codes.
2. 根据配置生成驱动inf文件并签名 Auto generate driver's inf file and self sign.
3. 驱动生成功能依赖libwdi项目

## 说明

* 支持命令行和图形化工具生成描述符和端点初始化代码，支持图形化工具生成驱动inf文件并签名。
* 通过解析描述符的配置文件，自动分析设备中的接口，并为接口分配编号。
* 自动分析描述符中的字符串，生成字符描述符及序号，合并相同的字符。
* 根据需要生成IAD描述符
* 根据配置生成WCID相关描述符
* 根据配置生成设备驱动inf文件，支持的类型与libwdi项目相同
* 生成驱动自签名文件，签名功能调用libwdi完成

## 图形化工具 GUI tool

图形化工具采用[XToolbox][xtoolbox_download]开发，XToolbox是一个[lua脚本驱动的Qt应用程序原型开发框架][xtoolbox_intro]，用lua封装了常见的Qt界面元素。



## 命令行工具 command line tool

命令行工具通过[lua 5.3][lua_download]生成描述符

### 命令行格式

```batch
lua gen_decriptor.lua <config-file>
```
config-file是USB设备配置文件，用来生成描述符的C语言代码，其格式见下。执行后会在config-file相同目录下生成tiny_usb_desc.c和tiny_usb_init.h文件。tiny_usb_desc.c是设备描述符文件，包含USB设备的各种描述符。tiny_usb_init.h是端点定义文件，对于STM32F1xx和STM32F0xx芯片，会根据描述符中的端点信息，生成相应的端点初始化代码。查看生成的代码示例：[tiny_usb_desc.c][tiny_usb_desc_demo], [tiny_usb_init.h][tiny_usb_init_demo]

### 配置文件格式

```lua
return Device {
    strManufacture = "tiny usb",
    strProduct = "tiny usb bulk demo",
    strSerial = "tu123456",
    idVendor = 0x2017,
    idProduct = 0x0924,
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
}
```
上面是一个USB设备配置文件的示例，lua格式，定义了一个USB设备的VID PID以及相应的字符串。这个设备有两个接口，每个接口有两个Endpoint，分别作为收发端点。其中Interface 0的端点为bulk双缓冲模式，Interface 1的端点为bulk普通模式。prefix属性定义了设备的名称，在生成相关代码时会加上这个名称作为前缀。Interface中的WCID([什么是WCID?][what_is_wcid])属性，表示此接口支持WCID，后面的WinUSB表示其支持WinUSB兼容设备。也可以定义为其他设备。

也可以一次定义多个设备的配置，用不同的前缀进行区分
```lua
-- DEMO USB descriptor multiple device
return {
-- config device 1
Device {
    prefix = "Device1",
     ...
},
-- config device 2
Device {
    prefix = "Device2",
     ...
},
...
-- config device N
Device {
    prefix = "DeviceN",
     ...
}
}
```

设备配置的示例在[demo.lua][desc_demo]




[lua_download]: https://www.lua.org/download.html
[xtoolbox_download]: https://github.com/xtoolbox/Introduction/releases
[xtoolbox_intro]: https://github.com/xtoolbox/Introduction
[desc_demo]: https://github.com/xtoolbox/tiny_usb/blob/master/tiny_usb_stack/descriptor_demo/demo.lua
[what_is_wcid]: https://github.com/xtoolbox/tiny_usb/wiki/WCID-Device
[tiny_usb_desc_demo]: https://github.com/xtoolbox/tiny_usb/blob/master/tiny_usb_stack/descriptor_demo/tiny_usb_desc.c
[tiny_usb_init_demo]: https://github.com/xtoolbox/tiny_usb/blob/master/tiny_usb_stack/descriptor_demo/tiny_usb_init.h
