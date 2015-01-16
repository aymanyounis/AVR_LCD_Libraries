/* --------------------------------------------------------------------------------------------------
[Title]	:			<LCD library, HD44780U Module>
[FILE NAME]:		<lcd.c>
[AUTHOR(S)]:		<Ayman Younis>
[DATE CREATED]:		<6/1/2015>
[Software]:			<AVR-GCC 3.4.1057, Atmel Studio 6 (Version: 6.2.1153)>
[Target]:			<Any AVR device>
[DESCRIPTION]:		<This file contains the source functions for the lcd module device>
[USAGE]:			<See the C include lcd.h file for a description of each function>
-------------------------------------------------------------------------------------------------- */

/****************************************************************************
 

 DESCRIPTION
       Basic routines for interfacing a HD44780U-based text lcd display

       Originally based on Peter Fleury's lcd library,
       Changed/Added: configure each pin from data and control pins as individual (Define Any Port and Any Pin number),
       Added: improved and optimized code.

       Library can be operated in memory mapped mode (LCD_IO_MODE=0) or in 
       4-bit IO port mode (LCD_IO_MODE=1). 8-bit IO port mode not supported.
       
       Memory mapped mode compatible with Kanda STK200, but supports also
       generation of R/W signal through A8 address line.

 
       
*****************************************************************************/

/*--------------------------------------------- INCLUDES ------------------------------------------*/
#define LCD_H_MAIN
#include "lcd.h"

/* ---------------------------------------------------------------------------------------------------
Structure Name]: g_s_dataConfig
[Structure Description]: LCD Data Configurations Structure is responsible for describe Data bins,
						 Array of structure depending on the Data mode:
								1. the PORT Which the BUTTON is connect with: 'A 'B' 'C' or 'D'
								2. the number of the pin in the PORT: [0-7]
								3. the direction of pin: Button is setted as INPUT
								4. the value state of the pin
---------------------------------------------------------------------------------------------------- */
static DioConfig g_s_dataConfig[LCD_DATA_MODE];

/* ---------------------------------------------------------------------------------------------------
Structure Name]: g_s_ctrlConfig
[Structure Description]: LCD Control Configurations Structure is responsible for describe RS, RW, EN bins:
								1. the PORT Which the BUTTON is connect with: 'A 'B' 'C' or 'D'
								2. the number of the pin in the PORT: [0-7]
								3. the direction of pin: Button is setted as INPUT
								4. the value state of the pin
---------------------------------------------------------------------------------------------------- */
static DioConfig g_s_ctrlConfig[3];


static void LCD_dataConfig(uint8 a_lcdPort, uint8 a_lcdPin)
{
	/* local variable for loop iterations */
	static uint8 loop = 0;
	
	/* fill direction and initial value for each data pin, then set pin direction for them */
	g_s_dataConfig[loop].s_port	=	a_lcdPort;
	g_s_dataConfig[loop].s_pinNum	=	a_lcdPin;
	g_s_dataConfig[loop].s_direction	= OUTPUT;
	g_s_dataConfig[loop].s_value		= LOGIC_LOW;
	
	DIO_setPinDirection(& g_s_dataConfig[loop]);
	loop++;
}

static void LCD_ctrlConfig(uint8 a_lcdPort, uint8 a_lcdPin)
{
	/* local variable for loop iterations */
	static uint8 loop = 0;
	
	/* fill direction and initial value for each data pin, then set pin direction for them */
	/* fill direction and initial value for RS, RW, EN pins, then set pin direction for them */
	g_s_ctrlConfig[loop].s_port			=	a_lcdPort;
	g_s_ctrlConfig[loop].s_pinNum		=	a_lcdPin;
	g_s_ctrlConfig[loop].s_direction	=	OUTPUT;
	g_s_ctrlConfig[loop].s_value		=	LOGIC_LOW;
	
	DIO_setPinDirection(& g_s_ctrlConfig[loop]);
	loop++;
}

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : LCD_configurations
[Description] : This function is responsible for filling the LCD structure, Called only by LCD_init function.
				
[Args] :
[in] void:
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
static void LCD_configurations()
{	
	/* fill port and pin number for LCD data pins depending on Data-bit Mode */
	/* Configure data pins from 0 to 3 only if 8-bit mode defined */
	#if (LCD_DATA_MODE == 8)								
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

/*------------------------------------- FUNCTION Definitions --------------------------------------*/

void LCD_init(uint8 a_cursorState)
{
	/* Fill the LCD Configuration structure for both data and control pins and initialize them with initial data */
	LCD_configurations();
	
	#if (LCD_DATA_MODE==4)
		/* Prepare LCD to understand the 4-bit mode */
		/* When the power supply is given to LCD, it remains by default in 8-bit mode. 
		If 0x20 is sent, lower nibble will not be received by LCD because four data lines (D4-D7) are connected, 
		so 0x02 is sent instead of 0x20 to initiate it for 4-bit mode */
		LCD_sendCommand(LCD_FUNCTION_2_LINES);	
	#endif
	
	/*  (1 or 2)-line lcd + (4 or 8)-bit Data Mode + 5*7 dot display Mode 
		LCD_FUNCTION_DEFAULT is defined in the header file based on number of lines and LCD_DATA_MODE type
	*/
	LCD_sendCommand(LCD_FUNCTION_DEFAULT);
	
	/* cursor ON/OFF depending on lcd.h configuration */
	LCD_sendCommand(a_cursorState);
	/* clear LCD at the beginning */
	LCD_sendCommand(LCD_CLR); 
}

/* This function just get the command data ready depending on the configuration at header file 
	4-bit mode or 8-bit mode then send the data to a static function which display the command */
void LCD_sendCommand(uint8 a_command)
{
	LCD_write(a_command, 0);
}

/* This function just get the character data ready depending on the configuration at header file then
	send the data to the static function which display the character */
void LCD_displayCharacter(uint8 a_dataCharacter)
{
	LCD_write(a_dataCharacter, 1);
}

void LCD_displayString(const uint8 *a_dataString_Ptr)
{
	while(*a_dataString_Ptr != '\0')
	{
		/* Send character to LCD_displayCharacter function then post increment the pointer */
		LCD_displayCharacter(*a_dataString_Ptr++);
	}
}

void LCD_displayNumber(sint32 a_data, uint8 a_base)
{
	/* String to hold the ascii result */
	uint8 buff[LCD_DISP_LENGTH];
	/* Base 10 for decimal */
	itoaAnsiC(a_data,buff,a_base);
	LCD_displayString(buff);
}

void LCD_goToRowColumn(uint8 a_row,uint8 a_col)
{
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
	 * we need to apply the corresponding command 0b10000000+address */
	LCD_sendCommand(address|SET_CURSOR_LOCATION); 
}

void LCD_displayStringRowColumn(uint8 a_row,uint8 a_col,const uint8 *a_str_Ptr)
{
	/* go to to the required LCD position */
	LCD_goToRowColumn(a_row, a_col);
	/* display the string */
	LCD_displayString(a_str_Ptr);
}

static void LCD_write(uint8 a_data, uint8 a_dataType)
{	
	uint8 loop;
	if (a_dataType == 0)				/* Data Type is Command */
	{
		LCD_rsLow();
	} 
	else								/* Data Type is Data */
	{
		LCD_rsHigh();
	}
	LCD_rwLow();
	
	#if (LCD_DATA_MODE == 8)
		for (loop=0;loop<LCD_DATA_MODE;loop++)
		{
			g_s_dataConfig[loop].s_value = ((a_data >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
	#elif (LCD_DATA_MODE == 4)
		/* mask lower nibble because PD4-PD7 pins are used */
		for (loop=0;loop<LCD_DATA_MODE;loop++)
		{
			/* shift Right 4-bit and mask And OR it with the current port value to prevent change its value*/
			g_s_dataConfig[loop].s_value = (((a_data>>4) >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
		LCD_enToggle();
		for (loop=0;loop<LCD_DATA_MODE;loop++)
		{
			g_s_dataConfig[loop].s_value = ((a_data >> loop) & 1);
			DIO_writePin(& g_s_dataConfig[loop]);
		}
	#endif
	LCD_enToggle();
}

/**
 * Ansi C "itoa" based on Kernighan & Ritchie's "Ansi C":
 */
static void itoaAnsiC(sint32 value, uint8* str, uint8 base) {
	
	static uint8 num[] = "0123456789abcdefghijklmnopqrstuvwxyz";
	uint8* wstr = str;
	sint32 sign;
	
	// Validate base
	if (base<2 || base>35)
	{ 
		*wstr='\0'; 
		return; 
	}
	
	// Take care of sign
	if ((sign=value) < 0)
	{
		value = -value;	
	}
	
	// Conversion. Number is reversed.
	do
	{ 
		*wstr++ = num[value%base]; 
	}while(value/=base);
	
	if(sign<0)
	{ 
		*wstr++='-';
	}
	*wstr='\0';
	
	// Reverse string
	strreverse(str,wstr-1);
}

static void strreverse(uint8* begin, uint8* end) {
	
	uint8 aux;
	while(end>begin)
	{
		aux			=	*end;
		*end--		=	*begin;
		*begin++	=	aux;
	}
}

void LCD_clearScreen(void)
{
	/* clear display */
	LCD_sendCommand(LCD_CLR);
}

static inline void LCD_enToggle(void)
{
	LCD_enHigh();
	_delay_ms(1);
	LCD_enLow();
}

static inline void LCD_enHigh(void)
{
	g_s_ctrlConfig[2].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[2]);
}

static inline void LCD_enLow(void)
{
	g_s_ctrlConfig[2].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[2]);
}

static inline void LCD_rsHigh(void)
{
	g_s_ctrlConfig[0].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[0]);
}

static inline void LCD_rsLow(void)
{
	g_s_ctrlConfig[0].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[0]);
}

static inline void LCD_rwHigh(void)
{
	g_s_ctrlConfig[1].s_value = LOGIC_HIGH;
	DIO_writePin(& g_s_ctrlConfig[1]);
}

static inline void LCD_rwLow(void)
{
	g_s_ctrlConfig[1].s_value = LOGIC_LOW;
	DIO_writePin(& g_s_ctrlConfig[1]);
}