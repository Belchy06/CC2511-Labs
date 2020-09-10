/* ###################################################################
 **     Filename    : main.c
 **     Project     : Lab7
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-09-10, 10:04, # CodeGen: 0
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
#include "Red.h"
#include "PwmLdd1.h"
#include "Green.h"
#include "PwmLdd2.h"
#include "TU1.h"
#include "Term1.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "Blue.h"
#include "PwmLdd3.h"
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

void drawGUI() {
	Term1_SetColor(clYellow, clBlack);
	Term1_MoveTo(1, 1);
	Term1_SendStr("CC2511 - Lab 7");

	// Left hand box
	Term1_SetColor(clBlack, clYellow);
	Term1_MoveTo(1, 3);
	Term1_SendStr("+-- PWM Status --+\r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");
	Term1_SendStr("                  \r\n");

	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(2, 4);
	Term1_SendStr("                ");
	Term1_MoveTo(2, 5);
	Term1_SendStr("                ");
	Term1_MoveTo(2, 6);
	Term1_SendStr("   Red:  0      ");
	Term1_MoveTo(2, 7);
	Term1_SendStr("   Green:0      ");
	Term1_MoveTo(2, 8);
	Term1_SendStr("   Blue: 0      ");
	Term1_MoveTo(2, 9);
	Term1_SendStr("                ");
	Term1_MoveTo(2, 10);
	Term1_SendStr("                ");

	// Right side instruction box
	Term1_SetColor(clBlack, clYellow);
	Term1_MoveTo(20, 3);
	Term1_SendStr("+----------------- [ How to Use ] -----------------+");
	Term1_MoveTo(20, 4);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 5);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 6);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 7);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 8);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 9);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 10);
	Term1_SendStr("                                                    ");
	Term1_MoveTo(20, 11);
	Term1_SendStr("                                                    ");

	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(21, 4);
	Term1_SendStr("                                                  ");
	Term1_MoveTo(21, 5);
	Term1_SendStr("      Type the following command:                 ");
	Term1_MoveTo(21, 6);
	Term1_SendStr("       > Red n    Set the Red PWM ratio to n/255  ");
	Term1_MoveTo(21, 7);
	Term1_SendStr("       > Green n  Set the Red PWM ratio to n/255  ");
	Term1_MoveTo(21, 8);
	Term1_SendStr("       > Blue n   Set the Red PWM ratio to n/255  ");
	Term1_MoveTo(21, 9);
	Term1_SendStr("       > Off      Turn the LEDs off               ");
	Term1_MoveTo(21, 10);
	Term1_SendStr("                                                  ");

	Term1_SetColor(clWhite, clBlack);
	Term1_MoveTo(1, 13);
	Term1_SendStr("Command prompt: \r\n");
	Term1_SendStr("> ");
}

void write_colour_val(char colour, int16 val) {
	Term1_SetColor(clWhite, clBlack);
	switch (colour) {
	case 'r':
		Term1_MoveTo(3, 6);
		Term1_SendStr("  Red:       ");
		Term1_MoveTo(11, 6);
		Term1_SendNum(val);
		break;
	case 'g':
		Term1_MoveTo(3, 7);
		Term1_SendStr("  Green:     ");
		Term1_MoveTo(11, 7);
		Term1_SendNum(val);
		break;
	case 'b':
		Term1_MoveTo(3, 8);
		Term1_SendStr("  Blue:       ");
		Term1_MoveTo(11, 8);
		Term1_SendNum(val);
		break;
	}
}
/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	drawGUI();
	int16 rval;
	int16 gval;
	int16 bval;
	Red_SetRatio8(0);
	Green_SetRatio8(0);
	Blue_SetRatio8(0);

	for (;;) {
		while (!complete_command) {
			__asm("wfi");
		}

		// A complete command has been received
		if (complete_command) {
			if (sscanf((char *) buffer, "Red %hu", &rval) > 0) {
				Red_SetRatio8(rval);
				write_colour_val('r', rval);
			} else if (sscanf((char *) buffer, "Green %hu", &gval) > 0) {
				Green_SetRatio8(gval);
				write_colour_val('g', gval);
			} else if (sscanf((char *) buffer, "Blue %hu", &bval) > 0) {
				Blue_SetRatio8(bval);
				write_colour_val('b', bval);
			} else if (0 == strcmp((char *) buffer, "Off")) {
				rval = 0;
				gval = 0;
				bval = 0;
				Red_SetRatio8(rval);
				Green_SetRatio8(bval);
				Blue_SetRatio8(gval);
				write_colour_val('r', rval);
				write_colour_val('g', gval);
				write_colour_val('b', bval);
			} else if (0 == strcmp((char *) buffer, "\f")) {
				drawGUI();
				write_colour_val('r', rval);
				write_colour_val('g', gval);
				write_colour_val('b', bval);
			}

			complete_command = false;
			index = 0;

			Term1_MoveTo(1, 14);
			Term1_SendStr(">                   ");
			Term1_MoveTo(3, 14);
		}
	}
	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
	/*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
#ifdef PEX_RTOS_START
	PEX_RTOS_START(); /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
#endif
	/*** End of RTOS startup code.  ***/
	/*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
	for (;;) {
	}
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
