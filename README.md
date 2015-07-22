# esp8266 software uart (Software Serial) & RS485 support
Software UART / Software Serial / SoftUart for ESP8266 to connect more than one UART

This library is very similar to the Arduino SoftSerial. It can be used to connect multiple GPIO's of the ESP8266 to UARTs. 

If there are any problems, please add issues and pull requests!

## How to use this example

1. Download this code
2. Edit Makefile and change the Paths to your location of the sdk and compiler

  ```
  XTENSA_TOOLS_ROOT ?= /home/main/esp8266/esp-open-sdk/xtensa-lx106-elf/bin
  SDK_BASE	?= /home/main/esp8266/esp-open-sdk/sdk
  ESPTOOL		?= /home/main/esp8266/esp-open-sdk/esptool/esptool.py
  ESPPORT		?= /dev/ttyUSB0
  ```
3. run `make clean && make`
4. connect your esp8266 in flash mode to your computer
5. run `make flash`
6. connect UART (e.g. of computer) to rx and tx of the esp at 9600 baud, you shoud see some dots '...'
7. connect UART (e.g. of computer) like this: rx -> PIN 12, tx -> PIN 14 and you should see some output like 'oneoneone'
8. connect UART (e.g. of computer) like this: rx -> PIN 5, tx -> PIN 4 and you shoudl see some output like '2222'
9. start changing the example code

## (Self-) Loopback is not supported!

When you connect a software tx with a software rx (wire from pin tx to pin rx), the rx will not receive the data because of timing issues.

If you use an external tx source, e.g. your computer, then rx will work (at least up to 38400 reliable).


## How to use this code in your project

Downlaod code and include folder 'softuart' in your project

Minimal example of how to setup one Softuart and send and receive some data:
```
#include "softuart.h"

//create global softuart instance
Softuart softuart;

//somewhere in a setup funciton e.g.
void ICACHE_FLASH_ATTR  user_init()
{
   //init software uart
   Softuart_SetPinRx(&softuart,14);
   Softuart_SetPinTx(&softuart,12);
    
   //startup
   Softuart_Init(&softuart,9600);
}

//to send a string use
Softuart_Puts(&softuart,"one");
//to send one character use
Softuart_Putchar(&softuart,0x84); //will send a T

//to receive characters use
uint8_t buf;
if(Softuart_Available(&softuart)) {
  buf = Softuart_Read(&softuart);
  os_printf("Softuart received: %c\r\n", buf);
} 
```

## How to use multiple softuart

```
//create global softuart instance
Softuart softuart;
Softuart softuart2;

//in some setup function: 
  //init first softuart
  Softuart_SetPinRx(&softuart,14);
  Softuart_SetPinTx(&softuart,12);
    
  //startup
  Softuart_Init(&softuart,9600);

  //init second uart
  Softuart_SetPinRx(&softuart2,4);
  Softuart_SetPinTx(&softuart2,5);

  //startup
  Softuart_Init(&softuart2,9600);

...

//to send a string to softuart one use
Softuart_Puts(&softuart,"one");

//to send a string to the second softuart use
Softuart_Puts(&softuart2,"two");


```

## How to use RS485 support

This library can be used to send data over a RS485 interface. To convert the signla, e.g. a MAX485 can be used. The rx and tx of the MAX485 are connected to the rx and tx of the esp8266 softuart pins. The additional pin to enable tx on the MAX485 chip will be connected to another GPIO of the esp82666, e.g. 13. 

Just add this code after the normal initialization:  `Softuart_EnableRs485(&softuart, 13);`

Then every time when the softuart wants to send some characters, it first enables the rs485 send (control pin HIGH) and after the character it will disable it again (control pin LOW).

Example code:

```
//create global softuart instance
Softuart softuart;

//in some setup function: 
  //init first softuart
  Softuart_SetPinRx(&softuart,14);
  Softuart_SetPinTx(&softuart,12);
    
  //startup
  Softuart_Init(&softuart,9600);

  //addtional (for RS485)
  //enable rs485 support
  //set pin 13 as output to control tx enable/disable of rs485 driver
  Softuart_EnableRs485(&softuart, 13);

...

//to send a string to softuart one use
Softuart_Puts(&softuart,"one");

//to send a string to the second softuart use
Softuart_Puts(&softuart2,"two");
```

## Problems / Pull request

Please contribute to this project and add issues / pull requests when you find any problems :)
