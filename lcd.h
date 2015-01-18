/* --------------------------------------------------------------------------------------------------
[Title]	:			<LCD library, HD44780U Module>
[FILE NAME]:		<lcd.h>
[AUTHOR(S)]:		<Ayman Younis>
*					https://github.com/aymanyounis
*					http://aymanyounis.github.io/AVR_LCD_Libraries/
[DATE CREATED]:		<6/1/2015>
[Software]:			<AVR-GCC 3.4.1057, Atmel Studio 6 (Version: 6.2.1153)>
[Target]:			<Any AVR device>
[DESCRIPTION]:		This file contains the lcd module header file, Basic routines for interfacing a text lcd display.
*
*					Originally based on Peter Fleury's lcd library,
*					Changed/Added: configure each pin from data and control pins as individual (Define Any Port and Any Pin number),
*					Added: improved and optimized code.
*										
[Options]:			Library can be operated in 4-bit IO port mode (LCD_IO_MODE=4) or 8-bit IO port mode (LCD_IO_MODE=8),
*					You can connect the data/control bins at any port and any pin number, each from its individual define
-------------------------------------------------------------------------------------------------- */

/*	LCD_H_MAIN will be defined at the led source file only, so the EXTERN will be removed, also EXTERN
*   becomes extern in other files that include lcd.h which is better for linker to allocate memory for 
*   them than being defined as extern in all files including the lcd.c
*/
#ifdef LCD_H_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#ifndef LCD_H_
#define LCD_H_

/*--------------------------------------------- INCLUDES -------------------------------------------*/
/*	dio.h includes the functions dealing with the device IOs, which are used to set the pin direction 
*	input/output, write logic high/low and read pin data */
#include "dio.h"

/*---------------------------------- Definitions and configurations --------------------------------*/

/*	LCD can be operated in 4-bit IO port mode (LCD_IO_MODE=4) or 8-bit IO port mode (LCD_IO_MODE=8) */
#define LCD_IO_MODE		 4

/*	Definitions for Data and Control IOs bins
*	Change each pin individual, to adapt your hardware configuration
*
*	Change LCD_RS_PORT, LCD_RW_PORT, LCD_E_PORT if you want the control lines on
*	different ports.
*	Each data line also can be on different port or all on the same port
*
*	configure Data lines from LCD_DATA0 to LCD_DATA7 if 8-bit mode used
*	configure from LCD_DATA4 to LCD_DATA7 if 4-bit mode and Ignore the first 4 pins
*/

/*	Control Pins Configuration */
#define LCD_RS_PORT			'C'							/**< port for RS line						*/
#define LCD_RS_PIN			 0							/**< pin number for RS line					*/ 
#define LCD_RW_PORT			'D'							/**< port for RW line						*/
#define LCD_RW_PIN			 0							/**< pin number for RW line					*/ 
#define LCD_EN_PORT			'D'							/**< port for Enable line					*/
#define LCD_EN_PIN			 4							/**< pin number for EN line					*/ 

/*	Data Pins Configuration */
/*	configure from LCD_DATA0 to LCD_DATA7 if 8-bit mode 
*   configure from LCD_DATA4 to LCD_DATA7 if 4-bit mode and Ignore the first 4 pins
*/
#define LCD_DATA0_PORT		'D'							/**< port for Data bit 0 line				*/
#define LCD_DATA0_PIN		 6							/**< pin for Data bit 0 line				*/
#define LCD_DATA1_PORT		'D'							/**< port for Data bit 1 line				*/
#define LCD_DATA1_PIN		 7							/**< pin for Data bit 1 line				*/
#define LCD_DATA2_PORT		'C'							/**< port for Data bit 2 line				*/
#define LCD_DATA2_PIN		 5							/**< pin for Data bit 2 line				*/
#define LCD_DATA3_PORT		'C'							/**< port for Data bit 3 line				*/
#define LCD_DATA3_PIN		 7							/**< pin for Data bit 3 line				*/

#define LCD_DATA4_PORT		'A'							/**< port for Data bit 4 line				*/
#define LCD_DATA4_PIN		 2							/**< pin for Data bit 4 line				*/
#define LCD_DATA5_PORT		'A'							/**< port for Data bit 5 line				*/
#define LCD_DATA5_PIN		 7							/**< pin for Data bit 5 line				*/
#define LCD_DATA6_PORT		'B'							/**< port for Data bit 6 line				*/
#define LCD_DATA6_PIN		 1							/**< pin for Data bit 6 line				*/
#define LCD_DATA7_PORT		'B'							/**< port for Data bit 7 line				*/
#define LCD_DATA7_PIN		 6							/**< pin for Data bit 7 line				*/

/*	Definitions for Display Size
*	Change these definitions to adapt setting to your display
*/
#define LCD_LINES			4							/**< number of lines of the display lcd		*/
#define LCD_DISP_LENGTH		20							/**< visible characters per line			*/
#define LCD_START_LINE1		0x00						/**< DDRAM address of first char of line 1	*/
#define LCD_START_LINE2		0x40						/**< DDRAM address of first char of line 2	*/
#define LCD_START_LINE3		0x10						/**< DDRAM address of first char of line 3	*/	
#define LCD_START_LINE4		0x50						/**< DDRAM address of first char of line 4	*/

/*	function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE		0x20				/**< 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES	0x28				/**< 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_2_LINES		0x02				
#define LCD_FUNCTION_8BIT_1LINE		0x30				/**< 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES	0x38				/**< 8-bit interface, dual line,   5x7 dots */

/*	instruction register bit positions */
#define LCD_CLR						0x01				/**< clear display, (also clear DDRAM content) */
#define LCD_CURSOR_OFF				0x0C				/**< Display on Cursor off					*/
#define LCD_CURSOR_ON				0x0E				/**< Display on Cursor on					*/
#define SET_CURSOR_LOCATION			0x80				/**< Set DDRAM address or cursor position on display */

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC				0x04				/**< display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT			0x05				/**< display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC				0x06				/**< display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT			0x07				/**< display shift on,  inc cursor move dir */

/*	display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF				0x08				/**< display off                            */
#define LCD_DISP_ON					0x0C				/**< display on, cursor off                 */
#define LCD_DISP_ON_BLINK			0x0D				/**< display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR			0x0E				/**< display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK	0x0F				/**< display on, cursor on, blink char      */

/*	move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT		0x10				/**< move cursor left  (decrement)			*/
#define LCD_MOVE_CURSOR_RIGHT		0x14				/**< move cursor right (increment)			*/
#define LCD_MOVE_DISP_LEFT			0x18				/**< shift display left						*/
#define LCD_MOVE_DISP_RIGHT			0x1C				/**< shift display right					*/

/*	Definitions for LCD number of line and LCD_IO_MODE
*	You don't need to change it
*/
#if (LCD_IO_MODE==4)
	#if LCD_LINES==1
		#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_1LINE
	#else
		#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_4BIT_2LINES
	#endif
#else
	#if LCD_LINES==1
		#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_8BIT_1LINE
	#else
		#define LCD_FUNCTION_DEFAULT    LCD_FUNCTION_8BIT_2LINES
	#endif
#endif

/*----------------------------------- FUNCTION DECLARATIONS ----------------------------------------------------*/
/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_init
[Description] :	This function is responsible for initialize the lcd data and control pins by call the static function
				"LCD_configurations" which Fill the LCD Configuration structure for both data and control pins and 
				initialize them with initial values, Prepare LCD to understand the 4-bit mode or 8-bit mode and set
				cursor ON/OFF state and clear the LCD.
				
[Args] :
[in] a_cursorState:
a_cursorState is uint8 for the cursor state, LCD_CURSOR_OFF or LCD_CURSOR_ON
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_init(uint8 a_cursorState);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_sendCommand
[Description] : This function is responsible for sending command to the lcd, it call the LCD_write function which
				takes two parameters, 1st the data to be sent to LCD, and the data type whether it's a data character 
				or a command byte, so we call LCD_write and send 0 to indicate that it's a command
				
[Args] :
[in] uint8 a_command:
The command to be executed in the LCD
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_sendCommand(uint8 a_command);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayCharacter
[Description] : This function is responsible for sending character to the lcd, it call the LCD_write function which
				takes two parameters, 1st the data to be sent to LCD, and the data type whether it's a data character 
				or a command byte, so we call LCD_write and send 1 to indicate that it's a data not command
				
[Args] :
[in] uint8 a_command:
The command to be executed in the LCD
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_displayCharacter(uint8 a_dataCharacter);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayString
[Description] : This function is responsible for displaying string on the lcd, by displaying it character by character
				till it reach the terminator character
				
[Args] :
[in] const uint8 *a_dataString_Ptr:
a_dataString_Ptr is a pointer to character
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_displayString(const uint8* a_dataString_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_clearScreen
[Description] : This function is responsible for clearing the lcd by sending the clearing command CLEAR_COMMAND
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_clearScreen(void);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayStringRowColumn
[Description] : This function is responsible for moving the cursor to a specific row and column on the lcd screen
				and display a string from this position
				
[Args] :
[in] uint8 a_row,uint8 a_col,const char *a_str_Ptr:
uint8 a_row, the row number
uint8 a_col, the column number
const char *a_str_Ptr, pointer to the sting to be displayed character by charater using displayCharacter function 
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_displayStringRowColumn(uint8 a_row, uint8 a_col, const uint8 *a_str_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_goToRowColumn
[Description] : This function is responsible for moving the cursor to a specific row and column on the lcd screen
				
[Args] :
[in] uint8 a_row,uint8 a_col:
uint8 a_row, the row number
uint8 a_col, the column number
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_goToRowColumn(uint8 a_row, uint8 a_col);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayNumber
[Description] : This function is responsible for displaying integer numbers on the lcd by converting this integer 
				to string using the itoa function and then display it as string, the value can be represented as
				binary, decimal, octal, hexadecimal, or any other base from 2 to 35.
				
[Args] :
[in] uint16 a_data, uint8 a_base:
a_data: The number value to be displayed on the LCD
a_base: The number base to be displayed on the LCD 
	Base can be any integer number from 2 to 35
		2 represent binary,
		8 represent octal,
		10 represent decimal, 
		16 represent hexadecimal, ..etc
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_displayNumber(sint32 a_data, uint8 a_base);

#endif /* LCD_H_ */