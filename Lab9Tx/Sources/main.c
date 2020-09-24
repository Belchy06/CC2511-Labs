/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab9Tx
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-09-22, 15:39, # CodeGen: 0
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
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "TU1.h"
#include "Red.h"
#include "BitIoLdd1.h"
#include "Green.h"
#include "BitIoLdd2.h"
#include "Blue.h"
#include "BitIoLdd3.h"
#include "FC32.h"
#include "RealTimeLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Variables for receiving strings
volatile char buffer[100];
volatile uint8 index = 0;
volatile bool complete_command = false;
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */

int convertASCIItoPWM(int ASCII) {
	return (((ASCII - 32) * 255) / 94);
}

void setLEDS(int val) {
	Red_PutVal(val);
	Blue_PutVal(val);
	Green_PutVal(val);
}

void delay(word delay_ms) {
	word time;
	FC32_Reset();

	do {
		__asm("wfi");
		FC32_GetTimeMS(&time);
	} while (time < delay_ms);
}

int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	int16 rec_val;
	int ascii_val;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	setLEDS(1);
	Term1_SendStr("Send a message to yoink! \r\n");
	Term1_SendStr("> ");
	/* Write your code here */
	/* For example: for(;;) { } */
	for (;;) {
		while (!complete_command) {
			__asm("wfi");
		}
		if (complete_command) {
			for (int i = 0; i < sizeof(buffer); i++) {
				ascii_val = (int) buffer[i];

				if (ascii_val == 0x0) {
					break;
				} else {
					setLEDS(0);
					delay(10 * ascii_val);
					//Term1_SendNum(ascii_val);
					//Term1_SendStr("\r\n");
					setLEDS(1);

					delay(500);
				}

			}

			complete_command = false;
			index = 0;

			Term1_MoveTo(1, 2);
			Term1_SendStr(">                                              ");
			Term1_MoveTo(3, 2);

			// 500ms pulse signals end of sentence
			setLEDS(0);
			delay(2000);
			setLEDS(1);
			delay(500);

		}

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
