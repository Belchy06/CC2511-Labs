/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab5
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-08-27, 14:22, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */

/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "Pins1.h"
#include "Blue.h"
#include "BitIoLdd1.h"
#include "In.h"
#include "BitIoLdd2.h"
#include "AS1.h"
#include "ASerialLdd1.h"
#include "PWMRed.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "PWMGreen.h"
#include "PwmLdd2.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdbool.h>
#include <stddef.h>

void send_string(const char *str) {
	size_t len, i; // a size_t is an unsigned integer
	len = strlen(str); // returns the number of chars in str
	byte err;
	for (i = 0; i < len; i++) {
		// send this character
		do {
			err = AS1_SendChar(str[i]);
		} while (err != ERR_OK);
	}
}
/*
 void part1() {
 do {
 Blue_PutVal(In_GetVal());
 err = AS1_RecvChar(&c); // component name = AS1
 } while (err != ERR_OK);

 if (c == ' ') {
 PORTB_PCR19 ^= 0b11;
 send_string("Toggled\r\n");
 }
 }
 */
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	char c;
	byte err;
	byte redRatio;
	byte greenRatio;
	char str[80];
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	AS1_Enable();
	//Green_NegVal();
	/* Write your code here */
	/* For example: for(;;) { } */
	for (;;) {
		do {
			err = AS1_RecvChar(&c); // component name = AS1
		} while (err != ERR_OK);

		switch (c) {
		case 'r':
			if (redRatio < 11) {
				redRatio = 0;
			} else {
				redRatio -= 10;
			}
			sprintf(str, "Set red to: %d \r\n", redRatio);
			send_string(str);
			break;

		case 'R':
			if (redRatio > 244) {
				redRatio = 255;
			} else {
				redRatio += 10;
			}
			sprintf(str, "Set red to: %d \r\n", redRatio);
			send_string(str);
			break;

		case 'g':
			if (greenRatio < 11) {
				greenRatio = 0;
			} else {
				greenRatio -= 10;
			}
			sprintf(str, "Set green to: %d \r\n", greenRatio);
			send_string(str);
			break;

		case 'G':
			if (greenRatio > 244) {
				greenRatio = 255;
			} else {
				greenRatio += 10;
			}
			sprintf(str, "Set green to: %d \r\n", greenRatio);
			send_string(str);
			break;
		}

		PWMGreen_SetRatio8(greenRatio);
		PWMRed_SetRatio8(redRatio);
	}
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
