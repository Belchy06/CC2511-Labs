/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab8
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-09-16, 18:59, # CodeGen: 0
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
#include "ADC.h"
#include "AdcLdd1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "RedPWM.h"
#include "PwmLdd1.h"
#include "TU1.h"
#include "GreenPWM.h"
#include "PwmLdd2.h"
#include "BluePWM.h"
#include "PwmLdd3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
#include "PDD_Includes.h"
#include "Init_Config.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#define max(a, b)\
({	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	_a > _b ? _a : _b; })

#define min(a, b)\
({	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	_a < _b ? _a : _b; })

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	/* r = min(result, 21845) * 3;

		if (max(21845, result) > 21845) {
			g = max(21845, result);
			g = min(g, 43690);
			g = (g - 21845) * 3;
		} else {
			g = 0;
		}

		if (max(43690, result) > 43690) {
			b = max(43690, result);
			b = (b - 43690) * 3;
		} else {
			b = 0;
		}

		Term1_SendNum(r);
		Term1_SendStr("\r\n");
		Term1_SendNum(g);
		Term1_SendStr("\r\n");
		Term1_SendNum(b);
		Term1_SendStr("\r\n");
		RedPWM_SetRatio8(r);
		GreenPWM_SetRatio8(g);
		BluePWM_SetRatio8(b);
		for (int i = 0; i < 100000; i++) {
			__asm volatile ("nop");
		}
		*/
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	uint16 result;
	uint8 r;
	uint8 g;
	uint8 b;
	int max = 65535;
	/* Write your code here */
	/* For example: for(;;) { } */
	Term1_SendStr("Program starting...\r\n");
	ADC_Calibrate(TRUE);
	Term1_SendStr("ADC calibration completed \r\n \r\n \r\n");

	for (;;) {
		ADC_Measure(TRUE);
		ADC_GetValue16(&result);
		Term1_SendNum(result);
		Term1_SendStr("\r\n");

		RedPWM_SetRatio16(max - result);
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
