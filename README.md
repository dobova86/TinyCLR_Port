# TinyCLR Ports

This repository hosts ports of TinyCLR to many different devices. For information on porting TinyCLR to your device or building a firmware for an existing port, see http://docs.ghielectronics.com/tinyclr/porting/intro.html.

Some targets and devices are maintained by GHI Electronics while others are maintained by community contributions. Right now, the below devices and targets are officially supported and maintained by GHI

This porting is mainly focused to port TinyCLR to STM32F7/H7 (tested on STM32F746 and STM32F769 Discovery) adding some display support for ST Discovery boards and Mikroelektronika Multimedia Plus STM32F4 and F7. There's also a porting for STM32F429ZI-Discovery board.

Original code done by GHI: https://github.com/ghi-electronics/TinyCLR-Ports

<b>NOTE: 0.12.0 changes many code and code organization. The Disco-F746/F769 are working with included SDRAM heap for TinyCLR,
but SDRAM initialization must be implemented better. Added NUCLEO-F767 first release.</b>