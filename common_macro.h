/* ---------------------------------------------------------------------------------------------------
[FILE NAME]: <common_macro.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file contains the common macros which are used directly to set/clear or check a 
				certain bit in any defined register, rotate Right/Left and Toggle a certain bit in any
				register.
				and commonly included in the DIO header file to deal with the device input and output 
				hardware registers>
--------------------------------------------------------------------------------------------------- */

#ifndef COMMON_MACRO_H_
#define COMMON_MACRO_H_

/*------------------------------------ FUNCTION-LIKE MACROS ----------------------------------------*/

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : SETBIT
[Description] : This macro is responsible for setting a certain bit in any defined register, by ORing
				this register with a byte, all its bits are zeros except the required bit to be 
				setted equal one, by logically shift left one to the BITNUM
				
				The bit shift (1<<(BITNUM)) is performed by the compiler which then inserts the result
				into the code. Thus, there is no run-time overhead.
[Args] : REG which refers to the register name, BITNUM which refers to the bit number from [0-7]

--------------------------------------------------------------------------------------------------- */
#define SETBIT(REG, BITNUM) ((REG) = (REG) | (1<<(BITNUM)))

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : CLEARBIT
[Description] : This macro is responsible for clearing a certain bit in any defined register, by 
				ANDing this register with a byte, all its bits are ones except the required bit to
				be cleared equal zero, by logically shift left one to BITNUM then complement the
				whole byte
				
				The bit shift (1<<(BITNUM)) is performed by the compiler which then inserts the result
				into the code. Thus, there is no run-time overhead.
[Args] : reg which refers to the register name, BITNUM which refers to the bit number from [0-7]

--------------------------------------------------------------------------------------------------- */
#define CLEARBIT(REG, BITNUM) ((REG) = (REG) & (~(1<<(BITNUM))))

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : BITISSET
[Description] : This macro is responsible for checking if any bit is set in any defined register, 
				and return one if it's setted and zero if it's cleared by ANDing this register with 
				a byte, all its bits are zeros except the required bit to be checked equal one, by 
				logically shift left one to BITNUM
				
				The bit shift (1<<(BITNUM)) is performed by the compiler which then inserts the result
				into the code. Thus, there is no run-time overhead.
[Args] : reg which refers to the register name, BITNUM which refers to the bit number from [0-7]

--------------------------------------------------------------------------------------------------- */
#define BITISSET(REG, BITNUM) ((REG) & (1<<BITNUM))

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : BITISCLEAR
[Description] : This macro is responsible for checking if any bit is clear in any defined register,
				and return one if it's cleared and zero if it's setted 
				
				The bit shift (1<<(BITNUM)) is performed by the compiler which then inserts the result
				into the code. Thus, there is no run-time overhead.
[Args] : reg which refers to the register name, BITNUM which refers to the bit number from [0-7]

--------------------------------------------------------------------------------------------------- */ 
#define BITISCLEAR(REG, BITNUM) (!((REG) & (1<<BITNUM)))

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : TOGGLEBIT
[Description] : This macro is responsible for Toggle a certain bit in any register by XORing it with 
				one 
				
				The bit shift (1<<(BITNUM)) is performed by the compiler which then inserts the result
				into the code. Thus, there is no run-time overhead.
[Args] : reg which refers to the register name, BITNUM which refers to the bit number from [0-7]

--------------------------------------------------------------------------------------------------- */
#define TOGGLEBIT(REG,BITNUM) ( (REG)^=(1<<BITNUM) )

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : ROR
[Description] : This macro is responsible for rotate right the register value with specific number of 
				rotates 
				
[Args] : reg which refers to the register name, NUM which refers to the number of rotates

--------------------------------------------------------------------------------------------------- */
#define ROR(REG,NUM) ( (REG) = (REG>>NUM) | (REG<<(8-NUM)) )

/* ---------------------------------------------------------------------------------------------------
[MACRO Name] : ROL
[Description] : This macro is responsible for rotate left the register value with specific number of 
				rotates 
				
[Args] : reg which refers to the register name, NUM which refers to the number of rotates

--------------------------------------------------------------------------------------------------- */
#define ROL(REG,NUM) ( (REG) = (REG<<NUM) | (REG>>(8-NUM)) )

#endif /*common_macro.h*/