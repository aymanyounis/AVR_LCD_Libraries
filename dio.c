/* --------------------------------------------------------------------------------------------------
[FILE NAME]: <dio.c>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file contains the source functions for device input/output which are used to 
				set the direction input/output, write logic high/low and read data to/from a certain 
				bit in any defined register>
-------------------------------------------------------------------------------------------------- */

/*--------------------------------------------- INCLUDES ------------------------------------------*/
#define DIO_H_MAIN
#include "dio.h"

/*------------------------------------- FUNCTION Definitions --------------------------------------*/
/*--------------------------------------- DIO_setPinDirection ----------------------------------------*/
void DIO_setPinDirection(const DioConfig* a_CONFIG_MSG_Ptr)
{
	/* local pointer to hold the address for the required DDR Register */
	uint8* ddr_Ptr;
	/* point to the required DDR Register depending on structure port value */
	switch(a_CONFIG_MSG_Ptr->s_port)
	{
		case 'A':
		case 'a': 
			ddr_Ptr = &DDRA;
			break;
		case 'B':
		case 'b': 
			ddr_Ptr = &DDRB;
			break;
		case 'C':
		case 'c': 
			ddr_Ptr = &DDRC;
			break;
		case 'D':
		case 'd': 
			ddr_Ptr = &DDRD;
			break;
		default:
			break;		  		  		  
	}
	
	/* check if user need to make PIN direction OUTPUT*/
	if(a_CONFIG_MSG_Ptr->s_direction == OUTPUT)
	{
		/* set the corresponding bit in the DDR register to configure it as OUTPUT pin */
		SETBIT(*ddr_Ptr,a_CONFIG_MSG_Ptr->s_pinNum); 
	}
	/* check if user need to make PIN direction INPUT*/
	else if(a_CONFIG_MSG_Ptr->s_direction == INPUT)	
	{
		/* clear the corresponding bit in the DDR register to configure it as INPUT pin */
		CLEARBIT(*ddr_Ptr,a_CONFIG_MSG_Ptr->s_pinNum);
	}				
}

/*---------------------------------------- DIO_Write_Pin ----------------------------------------*/
void DIO_writePin(const DioConfig* a_STATE_Ptr)
{
	/* local pointer to hold the address for the required PORT Register */
	uint8* port_Ptr;
	/* point to the required DDR Register depending on structure port value */
	switch(a_STATE_Ptr->s_port)
	{
		case 'A':
		case 'a': 
			port_Ptr = &PORTA;
			break;
		case 'B':
		case 'b': 
			port_Ptr = &PORTB;
			break;
		case 'C':
		case 'c': 
			port_Ptr = &PORTC;
			break;
		case 'D':
		case 'd': 
			port_Ptr = &PORTD;
			break;
		default:
			break;		  		  		  
	}
	/* check if user need to write LOGIC HIGH on OUTPUT PIN */
	if(a_STATE_Ptr->s_value == LOGIC_HIGH)
	{
		/* set the corresponding pin in the PORT register */
		SETBIT(*port_Ptr,a_STATE_Ptr->s_pinNum); 
	}
	/* check if user need to write LOGIC LOW on OUTPUT PIN */				
    else if(a_STATE_Ptr->s_value == LOGIC_LOW)
	{
		/* clear the corresponding pin in the PORT register */
        CLEARBIT(*port_Ptr,a_STATE_Ptr->s_pinNum); 
	}		
}

/*----------------------------------------- DIO_Read_Pin ----------------------------------------*/
uint8 DIO_readPin(const DioConfig* a_STATE_Ptr)
{
	/* local pointer to hold the address for the required PIN Register */
	uint8* pin_Ptr;
	/* local uint8 which indicated whether the PIN is setted or cleared */
	uint8 pinStatus;
	/* point to the required PIN Register */
	switch(a_STATE_Ptr->s_port)
	{
		case 'A': 
		case 'a':
			pin_Ptr = &PINA;
			break;
		case 'B':
		case 'b':
			pin_Ptr = &PINB;
			break;
		case 'C':
		case 'c':
			pin_Ptr = &PINC;
			break;
		case 'D':
		case 'd':
			pin_Ptr = &PIND;
			break;
		default:
			break;
	}
	/* check if the corresponding bit is set in the PIN register */
	if(BITISSET(*pin_Ptr,a_STATE_Ptr->s_pinNum))
	{
		pinStatus = LOGIC_HIGH;
	}
	/* check if the corresponding bit is clear in the PIN register */
	else if(BITISCLEAR(*pin_Ptr,a_STATE_Ptr->s_pinNum))
	{
		pinStatus = LOGIC_LOW;
	}
	return pinStatus;
}

/*--------------------------------------- DIO_setPortDirection ----------------------------------------*/
void DIO_setPortDirection(const DioConfig* a_CONFIG_MSG_Ptr)
{
	/* local counter to loop on the whole port pins from 0 to 7 */
	uint8 pinCounter = 0;
	/* local pointer to hold the address for the required DDR Register */
	uint8* ddr_Ptr;
	/* point to the required DDR Register depending on structure port value */
	switch(a_CONFIG_MSG_Ptr->s_port)
	{
		case 'A':
		case 'a':
		ddr_Ptr = &DDRA;
		break;
		case 'B':
		case 'b':
		ddr_Ptr = &DDRB;
		break;
		case 'C':
		case 'c':
		ddr_Ptr = &DDRC;
		break;
		case 'D':
		case 'd':
		ddr_Ptr = &DDRD;
		break;
		default:
		break;
	}
	
	/* check if user need to make PIN direction OUTPUT*/
	if(a_CONFIG_MSG_Ptr->s_direction == OUTPUT)
	{
		/* loop on the whole port pins from 0 to 7 */
		for (pinCounter=0;pinCounter<8;pinCounter++)
		{
			/* set the corresponding bit in the DDR register to configure it as OUTPUT pin */
			SETBIT(*ddr_Ptr, pinCounter);
		}
	}
	/* check if user need to make PIN direction INPUT*/
	else if(a_CONFIG_MSG_Ptr->s_direction == INPUT)
	{
		/* loop on the whole port pins from 0 to 7 */
		for (pinCounter=0;pinCounter<8;pinCounter++)
		{
			/* set the corresponding bit in the DDR register to configure it as OUTPUT pin */
			CLEARBIT(*ddr_Ptr, pinCounter);
		}
	}
}

/*---------------------------------------- DIO_Write_Pin ----------------------------------------*/
void DIO_writePort(const DioConfig* a_STATE_Ptr)
{
	/* local counter to loop on the whole port pins from 0 to 7 */
	uint8 pinCounter = 0;
	/* local pointer to hold the address for the required PORT Register */
	uint8* port_Ptr;
	/* point to the required DDR Register depending on structure port value */
	switch(a_STATE_Ptr->s_port)
	{
		case 'A':
		case 'a':
		port_Ptr = &PORTA;
		break;
		case 'B':
		case 'b':
		port_Ptr = &PORTB;
		break;
		case 'C':
		case 'c':
		port_Ptr = &PORTC;
		break;
		case 'D':
		case 'd':
		port_Ptr = &PORTD;
		break;
		default:
		break;
	}
	/* OUT the port value */
	*port_Ptr = a_STATE_Ptr->s_value;
}

/*----------------------------------------- DIO_Read_Pin ----------------------------------------*/
uint8 DIO_readPort(const DioConfig* a_STATE_Ptr)
{
	/* local pointer to hold the address for the required PIN Register */
	uint8* pin_Ptr;
	/* local uint8 which indicated whether the PIN is setted or cleared */
	uint8 portValue;
	/* point to the required PIN Register */
	switch(a_STATE_Ptr->s_port)
	{
		case 'A':
		case 'a':
		pin_Ptr = &PINA;
		break;
		case 'B':
		case 'b':
		pin_Ptr = &PINB;
		break;
		case 'C':
		case 'c':
		pin_Ptr = &PINC;
		break;
		case 'D':
		case 'd':
		pin_Ptr = &PIND;
		break;
		default:
		break;
	}
	portValue = *pin_Ptr;
	return portValue;
}