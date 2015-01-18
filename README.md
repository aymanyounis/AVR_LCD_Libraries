#### _**These files contain the LCD module drive, Basic routines for interfacing a text lcd display with any AVR device**_

##
**DATE CREATED**: 
> * _18/1/2015_

**Software**: 
> * _AVR-GCC 3.4.1057, Atmel Studio 6 (Version: 6.2.1153)_

**Target**: 
> * _Any AVR device_

**DESCRIPTION**:
> * Originally based on **_Peter Fleury's lcd library_**,
> * **Changed/Added**: configure each pin from data and control pins as individual (Define Any Port and Any Pin number),
> * **Added**: improved and optimized code.

**Options**: 
> * Library can be operated in 4-bit IO port mode or 8-bit IO port mode, depending on the value of LCD_IO_MODE in lcd.h
> * You can connect the data/control bins at any port and any pin number, each from its individual define

**Files**: 
**NOTE**: _You have to download all these files and just include the lcd.h to your project _

> `**LCD files**`
> * 1. _[lcd.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/lcd.h)_
> * 2. _[lcd.c](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/lcd.c)_

> `**DIO files**`
> * 1. _[dio.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/dio.h)_
> * 2. _[dio.c](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/dio.c)_

> `**Test APP files**`
> * 1. _[lcd_test_app.c](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/lcd_test_app.c)_

> `**Other files**`
> * 1. _[common_macro.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/common_macro.h)_
> * 2. _[std_type.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/std_type.h)_
> * 3. _[peripheral_reg.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/peripheral_reg.h)_
> * 4. _[osc.h](https://github.com/aymanyounis/AVR_LCD_Libraries/blob/master/osc.h)_

> `**Proteus 7.9 simulation folder**`
> * Feel free to check the 4-bit and 8-bit mode running on Proteus 7.9 [Simulation files](https://github.com/aymanyounis/AVR_LCD_Libraries/tree/master/Simulation)

![Proteus Img](http://i.imgur.com/o6xrEL8.jpg)

**Functions**:
> * 1. _void **LCD_init** (uint8 a_cursorState);_
> * 2. _void **LCD_sendCommand** (uint8 a_command);_
> * 3. _void **LCD_displayCharacter** (uint8 a_dataCharacter);_
> * 4. _void **LCD_displayString** (const uint8* a_dataString_Ptr);_
> * 5. _void **LCD_displayStringRowColumn** (uint8 a_row, uint8 a_col, const uint8 *a_str_Ptr);_
> * 6. _void **LCD_displayNumber** (sint32 a_data, uint8 a_base);_
> * 7. _void **LCD_goToRowColumn** (uint8 a_row, uint8 a_col);_
> * 8. _void **LCD_clearScreen** (void);_
> * + other **inline **and **static **functions in lcd.c file

***
Contacts:
> * [Linkedin](https://www.linkedin.com/in/aymanyounis90)
> * [gmail](https://mail.google.com/mail/u/0/?view=cm&fs=1&tf=1&source=mailto&to=aymanyounis90@gmail.com)
