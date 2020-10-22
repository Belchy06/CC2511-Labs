/* ###################################################################
 **     Filename    : main.c
 **     Project     : Assignment_2_Test
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-09-04, 16:22, # CodeGen: 0
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
#include "xStep.h"
#include "BitIoLdd2.h"
#include "xDir.h"
#include "BitIoLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "RealTimeLdd1.h"
#include "TU2.h"
#include "TU1.h"
#include "timer.h"
#include "mode0.h"
#include "BitIoLdd3.h"
#include "mode1.h"
#include "BitIoLdd4.h"
#include "mode2.h"
#include "BitIoLdd5.h"
#include "nSleep.h"
#include "BitIoLdd6.h"
#include "nEnable.h"
#include "BitIoLdd7.h"
#include "nReset.h"
#include "BitIoLdd8.h"
#include "yDir.h"
#include "BitIoLdd9.h"
#include "zStep.h"
#include "BitIoLdd11.h"
#include "zDir.h"
#include "BitIoLdd12.h"
#include "spindle.h"
#include "PwmLdd1.h"
#include "yStep.h"
#include "BitIoLdd10.h"
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

struct position {
	int16 x;
	int16 y;
	int16 z;
};

void timeDelay(word delayms) {
	word time;
	timer_Reset();

	do {
		__asm("wfi");
		timer_GetTimeMS(&time);
	} while (time < delayms);
}

void stepPWM(int16 steps) {
	int16 index = 0;
	while (index < steps) {
		// pwm time baby
		yStep_SetVal();
		// wait
		timeDelay(5);
		yStep_ClrVal();
		timeDelay(5);
		index++;
	}
	yStep_ClrVal();
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	// make these pos values a float
	int16 xPos;
	int16 yPos;
	int16 zPos;
	int8 sPWM;

	struct position currentPos;
	currentPos.x = 0;
	currentPos.y = 0;
	currentPos.z = 0;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	nSleep_SetVal();
	nEnable_ClrVal();
	nReset_SetVal();

	mode0_ClrVal();
	mode1_ClrVal();
	mode2_ClrVal();

	/* Write your code here */
	/* For example: for(;;) { } */
	Term1_SendStr("Starting...");
	Term1_SendStr("Done \r\n");
	Term1_MoveTo(0, 1);

	for (;;) {
		while (!complete_command) {
			__asm("wfi");
		}

		if (complete_command) {
			if (0 == strcmp((char *) buffer, "dir")) {
				xDir_SetVal();
			}
			if (sscanf((char *) buffer, "X %hu", &xPos) > 0) {
				// change position. this will take a lot to work on
				// if new xPos is less than x limit do the function
				// if xPos is negative, move backwards
				int16 xDif = currentPos.x - xPos;
				if (xDif < 0) {
					xDir_ClrVal();
					stepPWM(abs(xDif));
				} else {
					// else move forward
					xDir_PutVal(1);
					stepPWM(xDif);
				}
				currentPos.x = xPos;
			}

			if (sscanf((char *) buffer, "Y %hu", &yPos) > 0) {
				// change position. this will take a lot to work on
				// if new xPos is less than x limit do the function
				// if xPos is negative, move backwards
				int16 yDif = currentPos.y - yPos;
				if (yDif < 0) {
					yDir_ClrVal();
					stepPWM(abs(yDif));
				} else {
					// else move forward
					yDir_PutVal(1);
					stepPWM(yDif);
				}
				currentPos.y = yPos;
			}

			if (sscanf((char *) buffer, "Z %hu", &zPos) > 0) {
				// change position. this will take a lot to work on
				// if new xPos is less than x limit do the function
				// if xPos is negative, move backwards
				int16 zDif = currentPos.z - zPos;
				if (zDif < 0) {
					zDir_ClrVal();
					stepPWM(abs(zDif));
				} else {
					// else move forward
					zDir_PutVal(1);
					stepPWM(zDif);
				}
				currentPos.z = zPos;
			}

			if (sscanf((char *) buffer, "S %hu", &sPWM) > 0) {
				// do spindle
				spindle_SetRatio8(sPWM);
			}

			complete_command = false;
			index = 0;

			Term1_MoveTo(1, 1);
			Term1_SendStr(">                 ");
			Term1_MoveTo(3, 1);

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
