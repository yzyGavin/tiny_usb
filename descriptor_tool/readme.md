# USB描述符工具

## 特性 Features

1. 根据配置自动生成USB描述符和端点初始化代码 Auto generate USB descriptors and Endpoint initial codes.
2. 根据配置生成驱动inf文件并签名 Auto generate driver's yiinf file and sign.
3. 驱动生成功能依赖

## 说明

* 命令行和图形化工具都使用lua脚本开发。

* 通过解析描述符的配置文件，自动分析设备中的接口，并为接口分配编号。

* 自动分析描述符中的字符串，生成字符描述符及序号，合并相同的字符。

* 根据需要生成IAD描述符

* 根据配置生成WCID相关描述符

* 根据配置生成设备驱动inf文件，支持的类型与libwdi项目相同

* 生成驱动自签名文件，签名功能调用libwdi完成

## 命令行工具 command line tool


## 图形化工具 GUI tool
