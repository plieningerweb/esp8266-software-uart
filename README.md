# esp8266-software-uart
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

## Problems / Pull request

Please contribute to this project and add issues / pull requests when you find any problems :)
