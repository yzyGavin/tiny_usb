Tiny USB
==========
Not only a tiny USB stack for STM32 devices, but also a toolset to create USB descriptors and drivers.

## 特性
1. 支持中断传输，批量传输，批量双缓冲传输，同步传输。
2. 支持的例程：串口(CDC)，多串口(CDC x 7)，HID，多HID(HID x 7)，自定义批量(bulk)
3. 使用lua脚本生成USB相关描述符，并根据描述符自动生成初始化配置代码。


