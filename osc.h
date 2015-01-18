/* ---------------------------------------------------------------------------------------------------
[FILE NAME]: <osc.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file defines the oscillator clock by 1MHz>
--------------------------------------------------------------------------------------------------- */

#ifndef OSC_H_
#define OSC_H_

/*---------------------------------- Definitions and configurations ---------------------------------*/
#ifndef F_CPU
/* define 1MHz Clock frequency */
#define F_CPU 1000000UL
#endif

#include <util/delay.h>

#endif /*osc.h*/
