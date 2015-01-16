/* ---------------------------------------------------------------------------------------------------
[FILE NAME]: <peripheral_reg.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file contains the memory mapped peripheral registers addresses which are used
				to access these registers "pointer dereference operator" for read/write operations>
--------------------------------------------------------------------------------------------------- */

#ifndef PERIPHERAL_REG_H_
#define PERIPHERAL_REG_H_

/*---------------------------------- Definitions and configurations --------------------------------*/

/*------------------------------------------ DDR Registers -----------------------------------------*/
#define DDRA (*((volatile uint8 *)0x3A))
#define DDRB (*((volatile uint8 *)0x37))
#define DDRC (*((volatile uint8 *)0x34))
#define DDRD (*((volatile uint8 *)0x31))

/*----------------------------------------- PORT Registers -----------------------------------------*/
#define PORTA (*((volatile uint8 *)0x3B))
#define PORTB (*((volatile uint8 *)0x38))
#define PORTC (*((volatile uint8 *)0x35))
#define PORTD (*((volatile uint8 *)0x32))

/*------------------------------------------ PIN Registers -----------------------------------------*/
#define PINA (*((volatile uint8 *)0x39))
#define PINB (*((volatile uint8 *)0x36))
#define PINC (*((volatile uint8 *)0x33))
#define PIND (*((volatile uint8 *)0x30))

/*------------------------------------------ Timer Registers -----------------------------------------*/
#define TCNT0 (*((volatile uint8 *)0x52))
#define OCR0 (*((volatile uint8 *)0x51))
#define TIMSK (*((volatile uint8 *)0x57))
#define TCCR0 (*((volatile uint8 *)0x53))

#endif /*peripheral_reg.h*/