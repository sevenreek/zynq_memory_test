/*
 * memtest_controller.h
 *
 *  Created on: Nov 3, 2019
 *      Author: Dickbutt
 */

#include "uart_controller.h"
#include <stdio.h>

#ifndef SRC_MEMTEST_CONTROLLER_H_
#define SRC_MEMTEST_CONTROLLER_H_


#define MEMORY_HIGH_ADDRESS XPAR_PS7_DDR_0_S_AXI_HIGHADDR
#define MEMTEST_STRLEN_VERBOSE 32
#define MEMTEST_STRLEN_RESULT  64
#define MEMORY_BASE_ADDRESS XPAR_PS7_DDR_0_S_AXI_BASEADDR


enum MemTestModes {
	MTESTMODE_ZEROES,
	MTESTMODE_DEADBEEF,
	MTESTMODE_WALKINGONE
};




void metest_setWordCount(unsigned int wordCount);
void memtest_writeRegister(unsigned int address, unsigned int value);
unsigned int memtest_readRegister(unsigned int address);
unsigned int getNextPattern(unsigned int counter, enum MemTestModes mode);
void memtest_performTest(unsigned int wordCount, enum MemTestModes mode);
void memtest_writeVerboseMessage(unsigned int address, unsigned int value, char correct);
void memtest_writeTestResult(unsigned int wordsWritten, unsigned int errors, enum MemTestModes mode);


#endif /* SRC_MEMTEST_CONTROLLER_H_ */
