/*
 * dotproduct.h
 */

#ifndef DOTPRODUCT_H_
#define DOTPRODUCT_H_

unsigned int c_dotproduct(int Q, int len, const unsigned int *vecA, const unsigned int *vecB);
unsigned int asm_dotproduct(int Q, int len, const unsigned int *vecA, const unsigned int *vecB);

#endif /* DOTPRODUCT_H_ */
