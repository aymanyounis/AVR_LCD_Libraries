/* ---------------------------------------------------------------------------------------------------
[FILE NAME]: <std_type.h>
[AUTHOR(S)]: <Ayman Younis>
[DATE CREATED]: <1/1/2015>
[DESCRIPTION]: <This file contains the standard variable types>
--------------------------------------------------------------------------------------------------- */

#ifndef STD_TYPE_H_
#define STD_TYPE_H_

/*---------------------------------- Definitions and configurations --------------------------------*/
/* define 8 bits unsigned [0-255] (2^8)-1 */
typedef unsigned char uint8;
/* define 16 bits unsigned [0-65565] (2^16)-1 */
typedef unsigned short uint16;
/* define 32 bits unsigned [0-4294967295] (2^32)-1 */
typedef unsigned long uint32;
/* define 8 bits signed [-128 - 127] (2^8)-1 */
typedef signed char sint8;
/* define 16 bits signed [-32,768 - 32,767] (2^16)-1 */
typedef signed short sint16;
/* define 32 bits signed [-2,147,483,648 - 2,147,483,647] (2^32)-1 */
typedef signed long sint32;

#endif /*std_type.h*/