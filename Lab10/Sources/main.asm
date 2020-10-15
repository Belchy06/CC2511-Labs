
/**
 * CC2511 Lab 10
*/
	.text 			/* The "text" section of the executable is where code is placed. */
	.align	2 		/* Make sure the starting address is a multiple of 2. */
	.global	main 	/* Declare "main" as a global symbol (callable from other files). */
  	.syntax unified /* Enable Thumb2 instruction set support */

/* Main function */
main:
	push {lr}  /* The return address is in the "link register" (lr). Preserve it by pushing it to the stack. */

	/* Write your code here */
	//SIM_SCGC5 |= 0x3e00;
	//movw r1, #0x8038
	//movt r1, #0x4004

	// load SIM_SCG5 into r1
	ldr r1, =0x40048038
	// store the value that we need to write to SIM_SCGC5 in r2
	ldr r2, =0x3e00
	// write the value in r2 to the memory address that r1 points to
	str r2, [r1]

	// set the GPIO mode for the red led on PTA1
	ldr r1, =0x40049004
	ldr r2, = 0x100
	str r2, [r1]

	// Disable the green led by writing 0 into its PCR
	ldr r1, =0x40049008
	ldr r2, =0
	str r2, [r1]

	// Disable the blue led by writing 0 into its PCR
	ldr r1, =0x4004C014
	ldr r2, =0
	str r2, [r1]

	// Select the data direction for the Red led
	.equ GPIOA_PDDR, 0x400FF014
	ldr r1, =GPIOA_PDDR
	ldr r2, =0x2
	str r2, [r1]

	// set the data output register to zero and one to turn it off
	.equ GPIOA_PDOR, 0x400FF000
	ldr r1, =GPIOA_PDOR

main_loop:
	// set all 0's to turn the led on
	ldr r2, =0
	str r2, [r1]


	// set start condition for delay
	ldr r3, =0xFFFFFF
repeatPlz:
	// decrement delay
	subs r3, #1
	// jump non-zero to
	bne repeatPlz



	// set 1<<1 to turn the led off
	ldr r2, =0x2
	str r2, [r1]


	ldr r3, =0xFFFFFF
repeat2:
	// decrement delay
	subs r3, #1
	// jump non-zero to
	bne repeat2



	b main_loop

	pop {pc}

