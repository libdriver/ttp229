[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TTP229
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ttp229/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

The TTP229 TonTouch IC is capacitive sensing design specifically for touch pad controls.The device built in regulator for touch sensor. Stable sensing method can cover diversity conditions.Human interfaces control panel links through non-conductive dielectric material. The main applicationis focused at replacing of the mechanical switch or button. The ASSP can independently handle the 8 touch pads or up to 16 touch pads.

LibDriver TTP229 is the full function driver of ttp229  launched by LibDriver. TTP229 provides touch reading and other functions. LibDriver complies with MISRA.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TTP229 source files.

/interface includes LibDriver TTP229 SPI platform independent template.

/test includes LibDriver TTP229 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TTP229 sample code.

/doc includes LibDriver TTP229 offline document.

/datasheet includes TTP229 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface SPI platform independent template and finish your platform SPI driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

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

### Document

Online documents: [https://www.libdriver.com/docs/ttp229/index.html](https://www.libdriver.com/docs/ttp229/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.
