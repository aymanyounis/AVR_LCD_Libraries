/* --------------------------------------------------------------------------------------------------
[FILE NAME]: <dio.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file contains the device input/output which are used to set the pin/port direction
				input/output, write logic high/low and read pin data>
--------------------------------------------------------------------------------------------------- */

/* DIO_H_MAIN will be defined at the dio source file only, so the EXTERN will be removed, also EXTERN
   becomes extern in other files that include dio which is better for linker to allocate memory for 
   them than being defined as extern in all files that include dio header file */
#ifdef DIO_H_MAIN
#define EXTERN
#else
#define EXTERN extern
#endif

#ifndef DIO_H_
#define DIO_H_

/*--------------------------------------------- INCLUDES -------------------------------------------*/
#include "peripheral_reg.h"
#include "std_type.h"
#include "osc.h"
#include "common_macro.h"

/*---------------------------------- Definitions and configurations --------------------------------*/
#define INPUT 0
#define OUTPUT 1

#define LOGIC_HIGH 1
#define LOGIC_LOW 0

/*-------------------------------------- Structures and Unions ---------------------------------------*/
/* ---------------------------------------------------------------------------------------------------
Structure Name]: DioConfig
[Structure Description]: This structure is responsible for describe each individual PIN contains to be
						 used for pin functions direction, write and read:
								1. the PORT Which the pin belongs to: 'A 'B' 'C' or 'D'
								2. the number of the pin in the PORT: [0-7]
								3. the direction of pin: INPUT or OUTPUT
								4. the value of the pin
---------------------------------------------------------------------------------------------------- */
typedef struct 
{
	/* s_port is the PORT Which the pin belongs to: can be on of these characters 'A 'B' 'C' or 'D' */
	uint8 s_port;
	/* s_pinNum refers to which PIN in the PORT: can be integer number from [0-7] */
	uint8 s_pinNum;
	/* s_direction determine the PIN direction: can be INPUT or OUTPUT */
	uint8 s_direction;
	/* s_value is the value of the PIN: can be LOGIC HIGH or LOGIC LOW */
	uint8 s_value;
}DioConfig;

/*----------------------------------- FUNCTION DECLARATIONS --------------------------------*/

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_setPinDirection
[Description] : This function is responsible for setting the direction of the corresponding bit in the PORT to be
				used as INPUT or OUTPUT
[Args] :
[in] const DioConfig* a_configMsg_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void DIO_setPinDirection(const DioConfig* a_CONFIG_MSG_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_writePin
[Description] : This function is responsible for output LOGIC HIGH or LOGIC LOW on the PIN based on the DIO 
				configuration value 
[Args] :
[in] const DioConfig* a_state_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void DIO_writePin(const DioConfig* a_STATE_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_readPin
[Description] : This function is responsible for reading the PIN value to check if the corresponding bit is set
				or clear and return LOGIC HIGH if it's setted or LOGIC LOW if it's cleared
[Args] :
[in] const DioConfig* a_state_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : The function return uint8 which indicated whether the PIN is setted or cleared
--------------------------------------------------------------------------------------------------------------- */
EXTERN uint8 DIO_readPin(const DioConfig* a_STATE_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_setPortDirection
[Description] : This function is responsible for setting the direction of the whole PORT to be used as INPUT or 
				OUTPUT
[Args] :
[in] const DioConfig* a_configMsg_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void DIO_setPortDirection(const DioConfig* a_CONFIG_MSG_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_writePort
[Description] : This function is responsible for output LOGIC HIGH or LOGIC LOW on the PORT based on the DIO 
				configuration value
[Args] :
[in] const DioConfig* a_state_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : This function return void
--------------------------------------------------------------------------------------------------------------- */
EXTERN void DIO_writePort(const DioConfig* a_STATE_Ptr);

/* ---------------------------------------------------------------------------------------------------------------
[Function Name] : DIO_readPort
[Description] : This function is responsible for reading the whole PORT value and return it as uint value
[Args] :
[in] const DioConfig* a_state_Ptr:
A pointer to the DIO configuration structure, defined as constant to be used as read only
[Returns] : The function return uint8 which indicated whether the PIN is setted or cleared
--------------------------------------------------------------------------------------------------------------- */
EXTERN uint8 DIO_readPort(const DioConfig* a_STATE_Ptr);

#endif /*dio.h*/