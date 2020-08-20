/* ###################################################################
**     Filename    : main.c
**     Project     : Lab4
**     Processor   : MK22FN512VDC12
**     Version     : Driver 01.01
**     Compiler    : GNU C Compiler
**     Date/Time   : 2020-08-17, 12:11, # CodeGen: 0
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
#include "AS1.h"
#include "ASerialLdd1.h"
#include "Red.h"
#include "BitIoLdd1.h"
#include "Green.h"
#include "BitIoLdd2.h"
#include "Blue.h"
#include "BitIoLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stddef.h>
#include <string.h>


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

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void) {
	/* Write your local variable definition here */
	byte err;
	char c;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	/* Write your code here */
	AS1_Enable();
	for(;;) {
		do {
			err = AS1_RecvChar(&c); // component name = AS1
		} while (err != ERR_OK);

		if (c == 'r' || c == 'R') {
			Red_NegVal();
			send_string("Toggled Red \r\n");
		} else if (c == 'g' || c == 'G') {
			Green_NegVal();
			send_string("Toggled Green \r\n");
		} else if (c == 'b' || c == 'B') {
			Blue_NegVal();
			send_string("Toggled Blue \r\n");
		}
	}

  #ifdef PEX_RTOS_START
  	PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/




