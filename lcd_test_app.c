/* --------------------------------------------------------------------------------------------------
[FILE NAME]: <lcd_test_app.c, EmbeddedC_Project2_Ayman_Younis>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <6/1/2015>
[DESCRIPTION]: <This file contains the source main functions that test the lcd module, writing
				commands, characters, string and integer on it through the LCD and DIO drivers>
-------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES ------------------------------------------*/
#include "lcd.h"

/*------------------------------------------ main function ----------------------------------------*/
int main(void)
{
	int i;
	
    LCD_init(LCD_CURSOR_OFF);
	
	while(1)
    {
		LCD_displayStringRowColumn(0,4,"Hello World!");
		LCD_goToRowColumn(1,1);
		LCD_displayString("TESTING LCD DRIVER");
		_delay_ms(1500);
		LCD_clearScreen();
		
		for (i=20;i>=0;i--)
		{
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,i+1,"EmbeddedC_Project2");
			LCD_displayStringRowColumn(1,i,"Ayman_ITI  18/1/2015");
			_delay_ms(150);
		}
		_delay_ms(1500);
		LCD_clearScreen();
	}
}