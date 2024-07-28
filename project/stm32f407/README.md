### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

SPI Pin: SCK/MISO PA5/PA6.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TTP229

#### 3.1 Command Instruction

1. Show ttp229 chip and driver information.

   ```shell
   ttp229 (-i | --information)
   ```

2. Show ttp229 help.

   ```shell
   ttp229 (-h | --help)
   ```

3. Show ttp229 pin connections of the current board.

   ```shell
   ttp229 (-p | --port)
   ```

5. Run ttp229 read test, num means the test times. 

   ```shell
   ttp229 (-t read | --test=read) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]
   ```

5. Run ttp229 read16 function, num means the read times. 

   ```shell
   ttp229 (-e read16 | --example=read16) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]
   ```

7. Run ttp229 read8 function, num means the read times.

   ```shell
   ttp229 (-e read8 | --example=read8) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]
   ```

#### 3.2 Command Example

```shell
ttp229 -i

ttp229: chip is Tontek TTP229.
ttp229: manufacturer is Tontek.
ttp229: interface is IIC SPI.
ttp229: driver version is 1.0.
ttp229: min supply voltage is 2.4V.
ttp229: max supply voltage is 5.5V.
ttp229: max current is 8.00mA.
ttp229: max temperature is 85.0C.
ttp229: min temperature is -40.0C.
```

```shell
ttp229 -p

ttp229: SPI interface SCK connected to GPIOA PIN5.
ttp229: SPI interface MISO connected to GPIOA PIN6.
ttp229: IIC interface SCL connected to GPIOB PIN8.
ttp229: IIC interface SDA connected to GPIOB PIN9.
```

```shell
ttp229 -t read --level=low --interface=spi --times=3

ttp229: chip is Tontek TTP229.
ttp229: manufacturer is Tontek.
ttp229: interface is IIC SPI.
ttp229: driver version is 1.0.
ttp229: min supply voltage is 2.4V.
ttp229: max supply voltage is 5.5V.
ttp229: max current is 8.00mA.
ttp229: max temperature is 85.0C.
ttp229: min temperature is -40.0C.
ttp229: start read test.
ttp229: read 16 keys test.
ttp229: key[0] key[1] key[2] key[3] is 1 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
ttp229: key[8] key[9] key[10] key[11] is 0 0 0 0.
ttp229: key[12] key[13] key[14] key[15] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 1 0 0.
ttp229: key[8] key[9] key[10] key[11] is 0 0 0 0.
ttp229: key[12] key[13] key[14] key[15] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
ttp229: key[8] key[9] key[10] key[11] is 0 0 1 0.
ttp229: key[12] key[13] key[14] key[15] is 0 0 0 0.
----------------------------------------------------
ttp229: read 8 keys test.
ttp229: key[0] key[1] key[2] key[3] is 1 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 1 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 1 0 0.
------------------------------------------------
ttp229: finish read test.
```

```shell
ttp229 -e read16 --level=low --interface=spi --times=3

ttp229: key[0] key[1] key[2] key[3] is 1 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
ttp229: key[8] key[9] key[10] key[11] is 0 0 0 0.
ttp229: key[12] key[13] key[14] key[15] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
ttp229: key[8] key[9] key[10] key[11] is 1 0 0 0.
ttp229: key[12] key[13] key[14] key[15] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
ttp229: key[8] key[9] key[10] key[11] is 0 0 0 0.
ttp229: key[12] key[13] key[14] key[15] is 0 1 0 0.
----------------------------------------------------
```

```shell
ttp229 -e read8 --level=low --interface=spi --times=3

ttp229: key[0] key[1] key[2] key[3] is 1 0 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 1 0 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
----------------------------------------------------
ttp229: key[0] key[1] key[2] key[3] is 0 0 1 0.
ttp229: key[4] key[5] key[6] key[7] is 0 0 0 0.
----------------------------------------------------
```

```shell
ttp229 -h

Usage:
  ttp229 (-i | --information)
  ttp229 (-h | --help)
  ttp229 (-p | --port)
  ttp229 (-t read | --test=read) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]
  ttp229 (-e read16 | --example=read16) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]
  ttp229 (-e read8 | --example=read8) [--level=<low | high>] [--interface=<iic | spi>] [--times=<num>]

Options:
      --level=<low | high>           Set the active level.([default: low])
  -e <read16 | read8>, --example=<read16 | read8>
                                     Run the driver example.
  -h, --help                         Show the help.
  -i, --information                  Show the chip information.
      --interface=<iic | spi>        Set the chip interface.([default: iic])
  -p, --port                         Display the pin connections of the current board.
  -t <read>, --test=<read>           Run the driver test.
      --times=<num>                  Set the running times.([default: 3])
```

