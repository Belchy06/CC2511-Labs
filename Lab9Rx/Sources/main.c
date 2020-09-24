/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab9Rx
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-09-22, 17:10, # CodeGen: 0
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
#include "FC321.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "ADC.h"
#include "AdcLdd1.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
	uint16 adc_prev;
	uint16 adc_curr;
	int adc_diff;
	word time;
	uint16 threshold = 1250;
	/* For example: for(;;) { } */
	Term1_SendStr("Program starting...\r\n");
	ADC_Calibrate(TRUE);
	Term1_SendStr("ADC calibration completed \r\n \r\n \r\n");
	ADC_Measure(TRUE);
	ADC_GetValue16(&adc_prev);

	for (;;) {
		ADC_Measure(TRUE);
		ADC_GetValue16(&adc_curr);
		//delay(100);
		//Term1_SendNum(adc_diff);
		//Term1_SendStr("\r\n");
		adc_diff = adc_curr - adc_prev;
		adc_prev = adc_curr;

		if (adc_diff > threshold) {
			// rising edge
			FC321_Reset();
			//Term1_SendStr("Rising	\r\n");
			do {
				ADC_Measure(TRUE);
				ADC_GetValue16(&adc_curr);
				//delay(200);
				adc_diff = adc_curr - adc_prev;
				//Term1_SendNum(adc_diff);
				//Term1_SendStr("\r\n");
				adc_prev = adc_curr;

			} while (adc_diff > (0-threshold));

			FC321_GetTimeMS(&time);
			Term1_SendStr("Pulse Width: ");
			Term1_SendNum(time);
			Term1_SendStr(" uS\r\n");
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
