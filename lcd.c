/* --------------------------------------------------------------------------------------------------
[Title]	:			<LCD library, HD44780U Module>
[FILE NAME]:		<lcd.h>
[AUTHOR(S)]:		<Ayman Younis>
*					https://github.com/aymanyounis
*					http://aymanyounis.github.io/AVR_LCD_Libraries/
[DATE CREATED]:		<6/1/2015>
[Software]:			<AVR-GCC 3.4.1057, Atmel Studio 6 (Version: 6.2.1153)>
[Target]:			<Any AVR device>
[DESCRIPTION]:		This file contains the lcd module source file, Basic routines for interfacing a text lcd display.
*
*					Originally based on Peter Fleury's lcd library,
*					Changed/Added: configure each pin from data and control pins as individual (Define Any Port and Any Pin number),
*					Added: improved and optimized code.
*
[Options]:			Library can be operated in 4-bit IO port mode (LCD_IO_MODE=4) or 8-bit IO port mode (LCD_IO_MODE=8),
*					You can connect the data/control bins at any port and any pin number, each from its individual define
*
[USAGE]:			<See the C include lcd.h file for a description of each function>
-------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES ------------------------------------------*/
#define LCD_H_MAIN
#include "lcd.h"

/* ---------------------------------------------------------------------------------------------------
[Structure Name]: g_s_dataConfig
[Structure Description]: LCD Data Configurations Structure is responsible for describe Data bins,
						 Array of structure can be 8 or 4 structures depending on LCD_IO_MODE :
[structure members]:								
							1. PORT Which the line is connect with: 'A 'B' 'C' or 'D'
							2. Pin number in the PORT: [0-7]
							3. Direction of pin: Button is setted as INPUT
							4. Value state of the pin
---------------------------------------------------------------------------------------------------- */
static DioConfig g_s_dataConfig[LCD_IO_MODE];

/* ---------------------------------------------------------------------------------------------------
[Structure Name]: g_s_ctrlConfig
[Structure Description]: LCD Control Configurations Structure is responsible for describe RS, RW, EN bins,
						 Array of 3 structure :
[structure members]:								
							1. PORT Which the line is connect with: 'A 'B' 'C' or 'D'
							2. Pin number in the PORT: [0-7]
							3. Direction of pin: Button is setted as INPUT
							4. Value state of the pin
---------------------------------------------------------------------------------------------------- */
static DioConfig g_s_ctrlConfig[3];

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_dataConfig
[Description] :	This function is responsible for filling the data structures with the initial defined values in h 
				file for each data pin, then set pin direction for them
				
[Args] :
[in] uint8 a_lcdPort, uint8 a_lcdPin:
a_lcdPort: PORT Which the line is connect with: 'A 'B' 'C' or 'D'
a_lcdPin: Pin number in the PORT: [0-7]
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_dataConfig(uint8 a_lcdPort, uint8 a_lcdPin)
{
	/* local variable for loop iterations, declared as static to keep its value */
	static uint8 loop = 0;
	
	/* fill initial value for each data pin, then set pin direction for them */
	g_s_dataConfig[loop].s_port			= a_lcdPort;
	g_s_dataConfig[loop].s_pinNum		= a_lcdPin;
	g_s_dataConfig[loop].s_direction	= OUTPUT;
	g_s_dataConfig[loop].s_value		= LOGIC_LOW;
	
	DIO_setPinDirection(& g_s_dataConfig[loop]);
	loop++;
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_ctrlConfig
[Description] :	This function is responsible for filling the control structures with the initial defined values in h
				file for each data pin, then set pin direction for them
				
[Args] :
[in] uint8 a_lcdPort, uint8 a_lcdPin:
a_lcdPort: PORT Which the line is connect with: 'A 'B' 'C' or 'D'
a_lcdPin: Pin number in the PORT: [0-7]
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_ctrlConfig(uint8 a_lcdPort, uint8 a_lcdPin)
{
	/* local variable for loop iterations, declared as static to keep its value */
	static uint8 loop = 0;
	
	/* fill initial value for each control pin, then set pin direction for them */
	g_s_ctrlConfig[loop].s_port			=	a_lcdPort;
	g_s_ctrlConfig[loop].s_pinNum		=	a_lcdPin;
	g_s_ctrlConfig[loop].s_direction	=	OUTPUT;
	g_s_ctrlConfig[loop].s_value		=	LOGIC_LOW;
	
	DIO_setPinDirection(& g_s_ctrlConfig[loop]);
	loop++;
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_configurations
[Description] : This function is responsible for filling the LCD data and control structures by calling the static 
				functions LCD_dataConfig and LCD_ctrlConfig.
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_configurations()
{	
	/* fill port and pin number for LCD data pins depending on Data_IO_Mode */
	/* Configure data pins from 0 to 3 only if 8-bit mode defined */
	#if (LCD_IO_MODE == 8)								
		LCD_dataConfig(LCD_DATA0_PORT, LCD_DATA0_PIN);
		LCD_dataConfig(LCD_DATA1_PORT, LCD_DATA1_PIN);
		LCD_dataConfig(LCD_DATA2_PORT, LCD_DATA2_PIN);
		LCD_dataConfig(LCD_DATA3_PORT, LCD_DATA3_PIN);
	#endif
	/* Configure data pins from 4 to 7 whether its defined as 8-bit mode or 4-bit mode */
	LCD_dataConfig(LCD_DATA4_PORT, LCD_DATA4_PIN);
	LCD_dataConfig(LCD_DATA5_PORT, LCD_DATA5_PIN);
	LCD_dataConfig(LCD_DATA6_PORT, LCD_DATA6_PIN);
	LCD_dataConfig(LCD_DATA7_PORT, LCD_DATA7_PIN);
	
	/* fill port and pin number for RS, RW, EN LCD control pins */
	LCD_ctrlConfig(LCD_RS_PORT, LCD_RS_PIN);
	LCD_ctrlConfig(LCD_RW_PORT, LCD_RW_PIN);
	LCD_ctrlConfig(LCD_EN_PORT, LCD_EN_PIN);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : itoaAnsiC
[Description] : This function is responsible for converting from integer to string to display number on LCD,
				Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C"
				
[Args]: sint32 a_value, uint8* a_str_Ptr, uint8 a_base
a_value: the integer value to be converted
a_str_Ptr: pointer to array of character which will hold the string value represent the integer number
a_base: the value base number, binary, decimal, octal, hexadecimal, ..
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void itoaAnsiC(sint32 a_value, uint8* a_str_Ptr, uint8 a_base);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : strreverse
[Description] : This function is responsible for reversing string
				
[Args]: uint8* a_begin_Ptr, uint8* a_end_Ptr
a_begin_Ptr: pointer to the start character
a_end_Ptr: pointer to the end character
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void strreverse(uint8* a_begin_Ptr, uint8* a_end_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_write
[Description] : This function is responsible for write on LCD, it configure rs as low or high depending on Data 
				Type whether its command or data, then send data to lcd data pins based on LCD_IO_MODE, and toggle 
				the enable pin
				
[Args] :
[in] uint8 a_data, uint8 a_dataType:
a_data: The data to be sent to LCD
a_dataType: the data type whether its a command or data
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_write(uint8 a_data, uint8 a_dataType);

static inline void LCD_enHigh(void);
static inline void LCD_enLow(void);
static inline void LCD_enToggle(void);
static inline void LCD_rsHigh(void);
static inline void LCD_rsLow(void);
static inline void LCD_rwHigh(void);
static inline void LCD_rwLow(void);

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
void LCD_init(uint8 a_cursorState)
{
	/*	Fill the LCD Configuration structure for both data and control pins and initialize them with initial data */
	LCD_configurations();
	
	#if (LCD_IO_MODE==4)
		/*	Prepare LCD to understand the 4-bit mode
		*	When the power supply is given to LCD, it remains by default in 8-bit mode. 
		*	If 0x20 is sent, lower nibble will not be received by LCD because four data lines (D4-D7) are connected, 
		*	so 0x02 is sent instead of 0x20 to initiate it for 4-bit mode 
		*/
		LCD_sendCommand(LCD_FUNCTION_2_LINES);	
	#endif
	
	/*  LCD_FUNCTION_DEFAULT is defined in the header file based on number of lines and LCD_IO_MODE type
	*	(1 or 2)-line lcd + (4 or 8)-bit Data Mode + 5*7 dot display Mode 
	*/
	LCD_sendCommand(LCD_FUNCTION_DEFAULT);
	
	/* Setting cursor state ON/OFF */
	LCD_sendCommand(a_cursorState);
	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLR); 
}

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
void LCD_sendCommand(uint8 a_command)
{
	LCD_write(a_command, 0);
}

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
void LCD_displayCharacter(uint8 a_dataCharacter)
{
	LCD_write(a_dataCharacter, 1);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_displayString
[Description] : This function is responsible for displaying string on the lcd, by displaying it character by character
				till it reach the terminator character
				
[Args] :
[in] const uint8 *a_dataString_Ptr:
a_dataString_Ptr is a pointer to character
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
void LCD_displayString(const uint8 *a_dataString_Ptr)
{
	while(*a_dataString_Ptr != '\0')
	{
		/* Send character to LCD_displayCharacter function then post increment the pointer */
		LCD_displayCharacter(*a_dataString_Ptr++);
	}
}

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
void LCD_displayNumber(sint32 a_data, uint8 a_base)
{
	/* String to hold the ascii result */
	uint8 buff[LCD_DISP_LENGTH];
	/* Base can be 10 for decimal, 8 for octal, ..etc, can be from 2 to 35 */
	itoaAnsiC(a_data,buff,a_base);
	LCD_displayString(buff);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_goToRowColumn
[Description] : This function is responsible for moving the cursor to a specific row and column on the lcd screen
				
[Args] :
[in] uint8 a_row,uint8 a_col:
uint8 a_row, the row number
uint8 a_col, the column number
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
void LCD_goToRowColumn(uint8 a_row,uint8 a_col)
{
	/* local variable to hold the LCD address value for the cursor */
	uint8 address;
	
	/* first of all calculate the required address */
	switch(a_row)
	{
		case 0:
				address = a_col + LCD_START_LINE1;
				break;
		case 1:
				address = a_col + LCD_START_LINE2;
				break;
		case 2:
				address = a_col + LCD_START_LINE3;
				break;
		case 3:
				address = a_col + LCD_START_LINE4;
				break;
		default:
				address = a_col + LCD_START_LINE1;
				break;
	}					
	/* to write to a specific address in the LCD 
	 * we need to apply the corresponding command 0b10000000+address 
	*/
	LCD_sendCommand(address|SET_CURSOR_LOCATION); 
}

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
void LCD_displayStringRowColumn(uint8 a_row, uint8 a_col, const uint8 *a_str_Ptr)
{
	/* go to to the required LCD position */
	LCD_goToRowColumn(a_row, a_col);
	/* display the string */
	LCD_displayString(a_str_Ptr);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_write
[Description] : This function is responsible for write on LCD, it configure rs as low or high depending on Data 
				Type whether its command or data, then send data to lcd data pins based on LCD_IO_MODE, and toggle 
				the enable pin
				
[Args] :
[in] uint8 a_data, uint8 a_dataType:
a_data: The data to be sent to LCD
a_dataType: the data type whether its a command or data
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_write (uint8 a_data, uint8 a_dataType)
{	
	uint8 loop;
	if (a_dataType == 0)				/* Data Type is Command */
	{
		/* write 0 on rs control bin */
		LCD_rsLow();
	} 
	else								/* Data Type is Data */
	{
		/* write 1 on rs control bin */
		LCD_rsHigh();
	}
	/* write 1 on rw control bin */
	LCD_rwLow();
	
	#if (LCD_IO_MODE == 8)
		for (loop=0;loop<LCD_IO_MODE;loop++)
		{
			/*	write each bit in the data value on each corresponding pin
			*	shift the data from [0-7] and AND it with 1 to get only the bit value 
			*	then write this bit to data bin
			*/
			g_s_dataConfig[loop].s_value = ((a_data >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
	#elif (LCD_IO_MODE == 4)
		for (loop=0;loop<LCD_IO_MODE;loop++)
		{
			/*	if 4-bit mode is used we will send data twice,
			*	write each bit in the data value on each corresponding pin
			*	for we shift the data right by 4 to get 4 bits high nibble and then shift
			*	these bit [0-3] and ANDing the whole byte with 1 to get each bit value 
			*	then write this bit to data bin
			*/
			g_s_dataConfig[loop].s_value = (((a_data>>4) >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
		/* toggle enable pin for LCD to read data */
		LCD_enToggle();
		/* send the low nibbles using the same method */
		for (loop=0;loop<LCD_IO_MODE;loop++)
		{
			g_s_dataConfig[loop].s_value = ((a_data >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
	#endif
	/* toggle enable pin for LCD to read data */
	LCD_enToggle();
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_clearScreen
[Description] : This function is responsible for clearing the lcd by sending the clearing command CLEAR_COMMAND
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
void LCD_clearScreen(void)
{
	/* clear display */
	LCD_sendCommand(LCD_CLR);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_enToggle
[Description] : This inline function is responsible for toggle enable pin by setting it high then delay then low
				for LCD to read the data on data line the en control pin need to be toggles
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_enToggle(void)
{
	LCD_enHigh();
	_delay_ms(1);
	LCD_enLow();
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_enHigh
[Description] : This inline function is responsible for set enable pin to high by write LOGIC_HIGH on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_enHigh(void)
{
	g_s_ctrlConfig[2].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[2]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_enLow
[Description] : This inline function is responsible for set enable pin to high by write LOGIC_LOW on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_enLow(void)
{
	g_s_ctrlConfig[2].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[2]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_rsHigh
[Description] : This inline function is responsible for set rs pin to high by write LOGIC_HIGH on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_rsHigh(void)
{
	g_s_ctrlConfig[0].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[0]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_rsLow
[Description] : This inline function is responsible for set rs pin to low by write LOGIC_LOW on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_rsLow(void)
{
	g_s_ctrlConfig[0].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[0]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_rwHigh
[Description] : This inline function is responsible for set rw pin to high by write LOGIC_HIGH on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_rwHigh(void)
{
	g_s_ctrlConfig[1].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[1]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_rwHigh
[Description] : This inline function is responsible for set rw pin to low by write LOGIC_LOW on it
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static inline void LCD_rwLow(void)
{
	g_s_ctrlConfig[1].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[1]);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : itoaAnsiC
[Description] : This function is responsible for converting from integer to string to display number on LCD,
				Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C"
				
[Args]: sint32 a_value, uint8* a_str_Ptr, uint8 a_base
a_value: the integer value to be converted
a_str_Ptr: pointer to array of character which will hold the string value represent the integer number
a_base: the value base number, binary, decimal, octal, hexadecimal, ..
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void itoaAnsiC(sint32 a_value, uint8* a_str_Ptr, uint8 a_base) {
	
	static uint8 num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	uint8* wstr_Ptr = a_str_Ptr;
	sint32 sign;
	
	/* check if base is Validate or no */
	if (a_base<2 || a_base>35)
	{ 
		*wstr_Ptr='\0'; 
		return; 
	}
	
	/* Take care of sign */
	if ((sign = a_value) < 0)
	{
		a_value = -a_value;	
	}
	
	/* Conversion. Number is reversed. */
	do
	{ 
		*wstr_Ptr++ = num[a_value%a_base]; 
	}while(a_value /= a_base);
	
	if(sign<0)
	{ 
		*wstr_Ptr++='-';
	}
	*wstr_Ptr='\0';
	
	/* Reverse string */
	strreverse(a_str_Ptr,wstr_Ptr-1);
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : strreverse
[Description] : This function is responsible for reversing string
				
[Args]: uint8* a_begin_Ptr, uint8* a_end_Ptr
a_begin_Ptr: pointer to the start character
a_end_Ptr: pointer to the end character
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void strreverse(uint8* a_begin_Ptr, uint8* a_end_Ptr) {
	
	uint8 aux;
	while(a_end_Ptr>a_begin_Ptr)
	{
		aux				=	*a_end_Ptr;
		*a_end_Ptr--	=	*a_begin_Ptr;
		*a_begin_Ptr++	=	aux;
	}
}