[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TTP229

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ttp229/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TTP229 TonTouch IC是专门用于触摸板控制的电容式传感设计。该设备内置触摸传感器调节器。稳定的传感方法可以覆盖多样性条件。人机界面控制面板通过非导电介电材料连接。主要应用集中在更换机械开关或按钮上。ASSP可以独立处理8个触摸板或最多16个触摸板。

LibDriver TTP229是LibDriver推出的TTP229的全功能驱动，该驱动提供触摸读取等功能并且它符合MISRA标准。

### 目录

  - [说明](#说明)
  - [安装](#安装)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [文档](#文档)
  - [贡献](#贡献)
  - [版权](#版权)
  - [联系我们](#联系我们)

### 说明

/src目录包含了LibDriver TTP229的源文件。

/interface目录包含了LibDriver TTP229与平台无关的SPI总线模板。

/test目录包含了LibDriver TTP229驱动测试程序，该程序可以简单的测试芯片必要功能。

/example目录包含了LibDriver TTP229编程范例。

/doc目录包含了LibDriver TTP229离线文档。

/datasheet目录包含了TTP229数据手册。

/project目录包含了常用Linux与单片机开发板的工程样例。所有工程均采用shell脚本作为调试方法，详细内容可参考每个工程里面的README.md。

/misra目录包含了LibDriver MISRA代码扫描结果。

### 安装

参考/interface目录下与平台无关的SPI总线模板，完成指定平台的SPI总线驱动。

将/src目录，您使用平台的接口驱动和您开发的驱动加入工程，如果您想要使用默认的范例驱动，可以将/example目录加入您的工程。

### 使用

您可以参考/example目录下的编程范例完成适合您的驱动，如果您想要使用默认的编程范例，以下是它们的使用方法。

#### example basic

```C
#include "driver_ttp229_basic.h"

uint8_t res;
uint32_t i;
uint8_t keys[16];

/* basic init */
res = ttp229_basic_init(TTP229_INTERFACE_SPI, TTP229_ACTIVE_LOW);
if (res != 0)
{
    return 1;
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    ttp229_interface_delay_ms(1000);

    /* read data */
    res = ttp229_basic_read_16_keys(keys);
    if (res != 0)
    {
        (void)ttp229_basic_deinit();

        return 1;
    }

    /* output */
    ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
    ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
    ttp229_interface_debug_print("ttp229: key[8] key[9] key[10] key[11] is %d %d %d %d.\n", keys[8], keys[9], keys[10], keys[11]);
    ttp229_interface_debug_print("ttp229: key[12] key[13] key[14] key[15] is %d %d %d %d.\n", keys[12], keys[13], keys[14], keys[15]);
    ttp229_interface_debug_print("----------------------------------------------------\n");
    
    ...
}

...
    
/* loop */
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    ttp229_interface_delay_ms(1000);

    /* read data */
    res = ttp229_basic_read_8_keys(keys);
    if (res != 0)
    {
        (void)ttp229_basic_deinit();

        return 1;
    }

    /* output */
    ttp229_interface_debug_print("ttp229: key[0] key[1] key[2] key[3] is %d %d %d %d.\n", keys[0], keys[1], keys[2], keys[3]);
    ttp229_interface_debug_print("ttp229: key[4] key[5] key[6] key[7] is %d %d %d %d.\n", keys[4], keys[5], keys[6], keys[7]);
    ttp229_interface_debug_print("----------------------------------------------------\n");
    
    ....
}

...
    
/* deinit */
(void)ttp229_basic_deinit();

return 0;
```

### 文档

在线文档: [https://www.libdriver.com/docs/ttp229/index.html](https://www.libdriver.com/docs/ttp229/index.html)。

离线文档: /doc/html/index.html。

### 贡献

请参考CONTRIBUTING.md。

### 版权

版权 (c) 2015 - 现在 LibDriver 版权所有

MIT 许可证（MIT）

特此免费授予任何获得本软件副本和相关文档文件（下称“软件”）的人不受限制地处置该软件的权利，包括不受限制地使用、复制、修改、合并、发布、分发、转授许可和/或出售该软件副本，以及再授权被配发了本软件的人如上的权利，须在下列条件下：

上述版权声明和本许可声明应包含在该软件的所有副本或实质成分中。

本软件是“如此”提供的，没有任何形式的明示或暗示的保证，包括但不限于对适销性、特定用途的适用性和不侵权的保证。在任何情况下，作者或版权持有人都不对任何索赔、损害或其他责任负责，无论这些追责来自合同、侵权或其它行为中，还是产生于、源于或有关于本软件以及本软件的使用或其它处置。

### 联系我们

请联系lishifenging@outlook.com。