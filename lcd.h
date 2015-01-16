/* ---------------------------------------------------------------------------------------------------
[FILE NAME]: <lcd.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <6/1/2015>
[DESCRIPTION]: <This file contains the lcd module header file, functions to deal with the lcd, 
				initialize, send Command, display character, display string, clear screen, go to
				specific row and column, display string to specific row and column and convert integer
				to string
				Options:
					-> You can configure it as 4-bit or 8-bit, 
					-> Connect the data/control bits any where but connect the Data sequentially and 
					the Control at the same port any pins,
					-> You can connect the CTRL and Data at the same port or different port.
					-> If you configures it as 4-bit mode, and connect the Data and the Control pins
					all on the same port, You can use the remaining pins  
				>
--------------------------------------------------------------------------------------------------- */

/* LCD_H_MAIN will be defined at the led source file only, so the EXTERN will be removed, also EXTERN
   becomes extern in other files that include dio which is better for linker to allocate memory for 
   them than being defined as extern in all files that include lcd header file
*/
#ifdef LCD_H_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#ifndef LCD_H_
#define LCD_H_

/*--------------------------------------------- INCLUDES -------------------------------------------*/
#include "dio.h"

/*---------------------------------- Definitions and configurations --------------------------------*/

/* LCD_DATA_MODE represent the DATA PIN NUMBER, 8 pins for 8-bit mode, 4 pins for 4-bit mode */
#define LCD_DATA_MODE		 8 

/* Control Pins Configuration */
/* port and pin number for RS line */
#define LCD_RS_PORT			'C'
#define LCD_RS_PIN			 2
/* port and pin number for RW line */
#define LCD_RW_PORT			'C'
#define LCD_RW_PIN			 1
/* port and pin number for Enable line */
#define LCD_EN_PORT			'C'
#define LCD_EN_PIN			 0

/* Data Pins Configuration */
/* configure from LCD_DATA0 to LCD_DATA7 if 8-bit mode 
   configure from LCD_DATA4 to LCD_DATA7 if 4-bit mode and Ignore the first 4 pins
*/
/* port and pin number for D0 line */
#define LCD_DATA0_PORT		'B'
#define LCD_DATA0_PIN		 0
/* port and pin number for D1 line */
#define LCD_DATA1_PORT		'B'
#define LCD_DATA1_PIN		 1
/* port and pin number for D2 line */
#define LCD_DATA2_PORT		'B'
#define LCD_DATA2_PIN		 2
/* port and pin number for D3 line */
#define LCD_DATA3_PORT		'B'
#define LCD_DATA3_PIN		 3

/* Continue Data bits Configuration if 8-bit mode used */
/* port and pin number for D4 line */
#define LCD_DATA4_PORT		'B'
#define LCD_DATA4_PIN		 4
/* port and pin number for D5 line */
#define LCD_DATA5_PORT		'B'
#define LCD_DATA5_PIN		 5
/* port and pin number for D6 line */
#define LCD_DATA6_PORT		'B'
#define LCD_DATA6_PIN		 6
/* port and pin number for D7 line */
#define LCD_DATA7_PORT		'B'
#define LCD_DATA7_PIN		 7

/* LCD Options and Characteristics */
/* number of lines of the display lcd */
#define LCD_LINES			4
/* visible characters per line */
#define LCD_DISP_LENGTH		16
/* DDRAM address of first char of line 1 */
#define LCD_START_LINE1  0x00
/* DDRAM address of first char of line 2 */
#define LCD_START_LINE2  0x40
/* DDRAM address of first char of line 3 */
#define LCD_START_LINE3  0x10
/* DDRAM address of first char of line 4 */
#define LCD_START_LINE4  0x50

#if (LCD_DATA_MODE==4)
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

/* Frequently used commands and instructions for LCD */

/* function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE		0x20		/* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES	0x28		/* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_2_LINES		0x02
#define LCD_FUNCTION_8BIT_1LINE		0x30		/* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES	0x38		/* 8-bit interface, dual line,   5x7 dots */

#define LCD_CLR						0x01		/* clear display, (also clear DDRAM content) */
#define LCD_CURSOR_OFF				0x0C		/* Display on Cursor off */
#define LCD_CURSOR_ON				0x0E		/* Display on Cursor on */
#define SET_CURSOR_LOCATION			0x80		/* Set DDRAM address or cursor position on display */

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC				0x04		/* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT			0x05		/* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC				0x06		/* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT			0x07		/* display shift on,  inc cursor move dir */

/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF				0x08		/* display off                            */
#define LCD_DISP_ON					0x0C		/* display on, cursor off                 */
#define LCD_DISP_ON_BLINK			0x0D		/* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR			0x0E		/* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK	0x0F		/* display on, cursor on, blink char      */

/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT		0x10		/* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT		0x14		/* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT			0x18		/* shift display left                     */
#define LCD_MOVE_DISP_RIGHT			0x1C		/* shift display right                    */

/*	Relative jump to 1 which do nothing, it takes 2 cycles 
			PC ? PC + k + 1
			2cycles
*/
#define lcd_e_delay()   __asm__ __volatile__( "rjmp 1f\n 1:" );

/*----------------------------------- FUNCTION DECLARATIONS ----------------------------------------------------*/
/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_init
[Description] : This function is responsible for initialize the lcd data pins and control pins
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_init(uint8 a_cursorState);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_sendCommand
[Description] : This function is responsible for sending command to the lcd
				
[Args] :
[in] uint8 a_command:
The command to be executed in the LCD
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_sendCommand(uint8 a_command);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayCharacter
[Description] : This function is responsible for displaying a character on the lcd
				
[Args] :
[in] uint8 a_dataCharacter:
The character to be displayed on the LCD
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void LCD_displayCharacter(uint8 a_dataCharacter);

static void LCD_write(uint8 a_data, uint8 a_dataType);

static void LCD_ctrlConfig(uint8 a_lcdPort, uint8 a_lcdPin);
static void LCD_dataConfig(uint8 a_lcdPort, uint8 a_lcdPin);

static inline void LCD_enHigh(void);
static inline void LCD_enLow(void);
static inline void LCD_enToggle(void);
static inline void LCD_rsHigh(void);
static inline void LCD_rsLow(void);
static inline void LCD_rwHigh(void);
static inline void LCD_rwLow(void);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayString
[Description] : This function is responsible for displaying a string on the lcd
				
[Args] :
[in] const char *a_dataString_Ptr:
Pointer to the string to be displayed on the LCD
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
static void itoaAnsiC(sint32 value, uint8* str, uint8 base);
static void strreverse(uint8* begin, uint8* end);

#endif /* LCD_H_ */