	.syntax unified /* enable thumb-2 support */

	.text
	.align 2
	.global asm_dotproduct
asm_dotproduct:
	push {r4-r11, lr}
	
	// r0 = Q
	// r1 = length
	// r2 = vecA pointer
	// r3 = vecB pointer
	
	/* write you code here */
	// you need a final result container that should be 64 bits long
	mov r8, #0
	mov r9, #0

	// implement a loop operation that performs the umlal r8, r9, rx, ry
	// set the length of r4 to the len * 4. This is done in 2 steps, move the length into r4 and the multiply by 4 which is the same as shifting left twice
	mov r4, r1 // the array index
	lsl r4, #2

loop:
	subs r4, #4
	// get the next element in the arrarys offset by r4, which jumps by 4 after each iteraton
	ldr r6, [r2,r4] // this fills up r6 with the current element in vecA as indexed by r4
	ldr r7, [r3,r4] // this fills up r7 with the current element in vecB as indexed by r4
	// do the umlal, r8, r9, rx, ry
	umlal r8, r9, r6, r7
	// loop back if we have not done r1 umlal

	bne loop
	// due to not being in fixed-point mode, we need to divide the result that is in [r9,r8] by r0 bits
	// however the result is in 64 bits in two registers [r9 and r8]
	// the final result to be returned can only be a 32bit value to be put into r0

	// 20bits of the final result are the 20 LSB from r9 and the other 12 are the 12MSB from r8
	// how do we get the final 32 bits by combining these 20 and 12 bits
	// shift r9 left
	// shift r8 right
	// finally OR these together is a 32 bit number
	lsl r9, #12
	lsr r8, #20
	orr r0, r8, r9
		
	pop {r4-r11, pc} // return


