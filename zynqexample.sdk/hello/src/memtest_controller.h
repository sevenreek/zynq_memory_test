/*
 * memtest_controller.h
 *
 *  Created on: Nov 3, 2019
 */



#ifndef SRC_MEMTEST_CONTROLLER_H_
#define SRC_MEMTEST_CONTROLLER_H_
#include "uart_controller.h"
#include <stdio.h>

#define MEMTEST_SIZE_FULL 0
#define MEMORY_HIGH_ADDRESS XPAR_PS7_DDR_0_S_AXI_HIGHADDR
#define MEMTEST_STRLEN_VERBOSE 32
#define MEMTEST_STRLEN_RESULT  64
#define MEMORY_BASE_ADDRESS XPAR_PS7_DDR_0_S_AXI_BASEADDR
enum MemTestVerbosity {
	MTESTVERBOSITY_NONE,
	MTESTVERBOSITY_BAD,
	MTESTVERBOSITY_ALL
};

enum QuickTestPatterns {
	QUICKPATTERN_ZEROES,
	QUICKPATTERN_ONES,
	QUICKPATTERN_DEADBEEF,
	QUICKPATTERN_WALKINGONE,
	QUICKPATTERN_A
};
enum DetailTestPatterns {
	DETAILPATTERN_A5ALTERNATING,
	DETAILPATTERN_WALKINGONE,
	DETAILPATTERN_WALKINGZERO
};




void metest_setWordCount(unsigned int wordCount);
void memtest_writeRegister(unsigned int address, unsigned int value);
unsigned int memtest_readRegister(unsigned int address);
unsigned int memtest_getNextQuickPattern(unsigned int counter, enum QuickTestPatterns mode);
unsigned int memtest_getNextDetailPattern(unsigned int memoryPoint, unsigned char concurrentTest, enum DetailTestPatterns mode);
void memtest_performQuickTest(unsigned int wordCount, enum QuickTestPatterns mode, int readCount, unsigned int increment, enum MemTestVerbosity verbosity);
void memtest_performDetailTest(unsigned int wordCount, enum DetailTestPatterns mode, int readCount, unsigned int increment, enum MemTestVerbosity verbosity);
void memtest_writeVerboseMessage(unsigned int address, unsigned int value, char correct);
void memtest_writeTestResult(unsigned int wordsWritten, unsigned int errors, enum QuickTestPatterns mode);
unsigned int memtest_getDetailPatternTestCount(enum DetailTestPatterns mode);
void memtest_setVerbosity(enum MemTestVerbosity verbosity);
#endif /* SRC_MEMTEST_CONTROLLER_H_ */
