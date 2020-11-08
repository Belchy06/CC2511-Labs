/* ###################################################################
 **     Filename    : main.c
 **     Project     : 2018_Exam
 **     Processor   : MK22FN512VDC12
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2020-11-08, 15:08, # CodeGen: 0
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
#include "Terminal.h"
#include "Inhr1.h"
#include "ASerialLdd1.h"
#include "ADC.h"
#include "AdcLdd1.h"
#include "RedLED.h"
#include "BitIoLdd1.h"
#include "GreenLED.h"
#include "BitIoLdd2.h"
#include "BlueLED.h"
#include "BitIoLdd3.h"
#include "FC32.h"
#include "RealTimeLdd1.h"
#include "TU1.h"
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
#include <stdlib.h>
#include <time.h>

volatile char buffer[100];
volatile uint8 index;
volatile bool complete_command = false;

// Calculate voltage function from 2c
float calculateVoltage(uint16 adcValue) {
	adcValue = (float) adcValue;
	return adcValue / (65535 / 3.3);
}

// Calculate t function from 2d
float calculateT(uint16 adcValue) {
	adcValue = (float) adcValue;
	return (30702 - adcValue) / 162.8;
}

// function used to generate an array of random number from 0-2 inclusive with a length of levelLength
void generateLedSequence(int *ledStatus, int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		int r = rand() % 3;
		ledStatus[i] = r;
	}
}

// Function for displaying the ledStatus array. R = 0, G = 1, B = 2. Illuminates for 1 second with a 0.5 second pause between colours
void displayLed(int ledStatus[], int arraySize) {
	for (int i = 0; i < arraySize; i++) {
		delay(500);
		RedLED_PutVal((ledStatus[i] % 3 == 0 ? 0 : 1));
		GreenLED_PutVal((ledStatus[i] % 3 == 1 ? 0 : 1));
		BlueLED_PutVal((ledStatus[i] % 3 == 2 ? 0 : 2));
		delay(1000);
		RedLED_SetVal();
		GreenLED_SetVal();
		BlueLED_SetVal();
	}
}

// Delay function
void delay(word delay_ms) {
	word time;
	FC32_Reset();
	do {
		__asm("wfi");
		FC32_GetTimeMS(&time);
	} while (time < delay_ms);
}

/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */
	uint16 result;
	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/
	// Q1 a.
	Terminal_SendStr("CC2511 Exam 2019 \r\nWilliam Belcher\r\n");

	ADC_Calibrate(TRUE);
	FC32_Reset();
	bool inGame = false;
	word timeElapsed;

	int gameScore = 0;
	int levelLength = 3;
	// Initialize the array to be the maximum size possible. Not efficient as the last value won't be utilized during level one but will be needed for level 2
	int ledStatus[4];
	// Turn LEDs off
	RedLED_SetVal();
	GreenLED_SetVal();
	BlueLED_SetVal();
	/* Write your code here */
	/* For example: for(;;) { } */
	for (;;) {
		while (!complete_command) {
			__asm("wfi");
		}
		if (complete_command) {
			// If the user is in the colour game, check their input differently
			if (inGame) {
				bool correctEntry;
				for (int i = 0; i < levelLength; i++) {
					// switch-case with the ledStatus array. R = 0, G = 1, B = 2. Check the user input against the value in the array.
					// If the user entered the same value as the one stored in the array, then the user has a correct entry.
					switch (ledStatus[i]) {
					case 0:
						correctEntry = (buffer[i] == 'r' ? true : false);
						break;
					case 1:
						correctEntry = (buffer[i] == 'g' ? true : false);
						break;
					case 2:
						correctEntry = (buffer[i] == 'b' ? true : false);
						break;
					default:
						break;
					}
					// if the user has at least one incorrect entry then no need to check the remaining entries as the whole answer is wrong
					if (!correctEntry)
						break;
				}
				// If the user didn't break out of the loop due to incorrect entry then add one to game score, else remove one
				gameScore += (correctEntry ? 1 : -1);
				Terminal_SendStr((correctEntry ? "\r\nCorrect" : "\r\nIncorrect"));
				Terminal_SendStr("\r\nScore: ");
				Terminal_SendNum(gameScore);
				Terminal_SendStr("\r\n");
				// Update level length. Advanced part of Q3
				if (gameScore >= 5) {
					levelLength = 4;
				} else {
					levelLength = 3;
				}

				// Check win/lose conditions
				if (gameScore >= 10) {
					Terminal_SendStr("\r\nYou WIN!");
					inGame = false;
					gameScore = 0;
					levelLength = 3;
				} else if (gameScore <= -5) {
					Terminal_SendStr("\r\nYou LOSE!");
					inGame = false;
					gameScore = 0;
					levelLength = 3;
				} else {
					// If not a win or lose, generate the next level and display the corresponding colours
					generateLedSequence(ledStatus, levelLength);
					displayLed(ledStatus, levelLength);
				}
			} else if (0 == strcmp((char *) buffer, "t")) {
				// Q2
				ADC_Measure(TRUE);
				ADC_GetValue16(&result);
				Terminal_SendStr("\r\nAnalog Measurement: \r\nx: ");
				Terminal_SendNum(result);
				Terminal_SendStr("\r\nv = ");
				Terminal_SendFloatNum(calculateVoltage(result));
				Terminal_SendStr("V ");
				Terminal_SendStr("\r\nt = ");
				Terminal_SendFloatNum(calculateT(result));
			} else if (0 == strcmp((char *) buffer, "s")) {
				Terminal_SendStr("\r\nColour Game Mode \r\n");
				// Gets the amount of time since the program started running and uses it as a seed for the rand function
				FC32_GetTimeMS(&timeElapsed);
				srand(timeElapsed);
				// Clear the buffer by setting all the values of buffer to 0
				memset(buffer, "\0", 100);
				// generate the sequence, display the sequence and set the inGame bool to true so that we then check the next user input differently
				generateLedSequence(ledStatus, levelLength);
				displayLed(ledStatus, levelLength);
				inGame = true;
			}

			complete_command = false;
			index = 0;
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
