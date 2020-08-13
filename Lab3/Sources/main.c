#include "MK22F51212.h"
#include <stdbool.h>

int main(void)
{
	SIM_SCGC5 |= 0x3e00;

	// Initialise Red LED
	PORTA->PCR[1] = 0x100; // Set GPIO mode
	GPIOA_PDDR = GPIOA_PDDR | (1 << 1); // Set PTA1 to output
	// Initialise Green LED
	PORTA->PCR[2] = 0x100; // Set GPIO mode
	GPIOA_PDDR = GPIOA_PDDR | (1 << 2); // Set PTA2 to output
	// Initialise Blue LED
	PORTD->PCR[5] = 0x100; // Set GPIO mode
	GPIOD_PDDR = GPIOD_PDDR | (1 << 5); // Set PTD5 to output


    /* This for loop should be replaced. By default this loop allows a single stepping. */
    int counter;

	for (;;) {
		for(int i = 1; i < 8; i++)
		{
			set_leds(i);
			wait(1000000);
		}

    }
    /* Never leave main */
    return 0;
}


void set_leds(i) {
	// Red LED
	if((i >> 2) % 2 == 1) { GPIOA_PCOR = (1 << 1); } else { GPIOA_PSOR = (1 << 1); }
	// Green LED
	if((i >> 1) % 2 == 1) { GPIOA_PCOR = (1 << 2); } else { GPIOA_PSOR = (1 << 2); }
	// Blue LED
	if((i >> 0) % 2 == 1) { GPIOD_PCOR = (1 << 5); } else { GPIOD_PSOR = (1 << 5); }
}

void wait(i) {
	for(int counter = 0; counter < i; counter++)
	{
		__asm volatile ("nop");
	}
}
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
