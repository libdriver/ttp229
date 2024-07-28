[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TTP229

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ttp229/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TTP229 TonTouch IC は、タッチパッド コントロール専用の静電容量式センシング設計です。デバイスにはタッチ センサー用のレギュレーターが組み込まれています。安定したセンシング方式により、さまざまな条件に対応できます。ヒューマン インターフェイス コントロール パネルは、非導電性の誘電体を介してリンクします。主な用途は、機械式スイッチまたはボタンの置き換えに重点を置いています。ASSP は、8 個のタッチパッドまたは最大 16 個のタッチパッドを個別に処理できます。

LibDriver TTP229 は、LibDriver がリリースした ttp229 のフル機能ドライバーです。TTP229 はタッチ読み取りなどの機能を提供します。LibDriver は MISRA に準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver TTP229のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver TTP229用のプラットフォームに依存しないSPIバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver TTP229ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver TTP229プログラミング例が含まれています。

/ docディレクトリには、LibDriver TTP229オフラインドキュメントが含まれています。

/ datasheetディレクトリには、TTP229データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないSPIバステンプレートを参照して、指定したプラットフォームのSPIバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ttp229/index.html](https://www.libdriver.com/docs/ttp229/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。