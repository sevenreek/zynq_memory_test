/*
 * memtest_controller.c
 *
 *  Created on: Nov 3, 2019
 *      Author: Dickbutt
 */
#include "memtest_controller.h"



unsigned int memtest_cfg_wordCount;
unsigned int memtest_cfg_stopAddress;
char memtest_cfg_printCorrect = TRUE;
char memtest_cfg_printError	 = TRUE;



void metest_setWordCount(unsigned int wordCount)
{
	memtest_cfg_wordCount = wordCount;
	memtest_cfg_stopAddress = MEMORY_BASE_ADDRESS + sizeof(unsigned int)*memtest_cfg_wordCount;
}

void memtest_writeRegister(unsigned int address, unsigned int value)
{
	*((volatile unsigned int*)address) = value;
}
unsigned int memtest_readRegister(unsigned int address)
{
	return *((volatile unsigned int*)address);
}

unsigned int getNextPattern(unsigned int counter, enum MemTestModes mode)
{
	switch(mode)
	{
		case MTESTMODE_DEADBEEF:
			return 0xDEADBEEF;
		break;
		case MTESTMODE_WALKINGONE:
			return 1UL << (counter%32);
		break;
		default:
			return 0x0;
		break;
	}
}

void memtest_performTest(unsigned int wordCount, enum MemTestModes mode)
{
	for(unsigned int counter = 0; counter < wordCount; counter++)
	{
		unsigned int currentAddress =  MEMORY_BASE_ADDRESS + sizeof(unsigned int)*counter;
		unsigned int pattern = getNextPattern(counter, mode);
		memtest_writeRegister(currentAddress, pattern);
	}
	unsigned int errorCount = 0;
	for(unsigned int counter = 0; counter < wordCount; counter++)
	{
		unsigned int currentAddress =  MEMORY_BASE_ADDRESS + sizeof(unsigned int)*counter;
		unsigned int expectedPattern = getNextPattern(counter, mode);
		unsigned int writtenPattern = memtest_readRegister(currentAddress);
		if(expectedPattern != writtenPattern)
		{
			errorCount++;
			if(memtest_cfg_printError == TRUE)
			{
				memtest_writeVerboseMessage(currentAddress, writtenPattern, FALSE);
			}
		}
		else if (memtest_cfg_printCorrect == TRUE)
		{
			memtest_writeVerboseMessage(currentAddress, writtenPattern, TRUE);
		}
	}
	memtest_writeTestResult(wordCount,errorCount,mode);
}
void memtest_writeVerboseMessage(unsigned int address, unsigned int value, char correct)
{
	unsigned char string[MEMTEST_STRLEN_VERBOSE];
	unsigned int stringlength = sprintf((char*)string, "%#010x = %#010x [%s]\n\r", address, value, correct?"OK":"BAD");
	uart_write(string,stringlength);
}
void memtest_writeTestResult(unsigned int wordsWritten, unsigned int errors, enum MemTestModes mode)
{
	unsigned char string[MEMTEST_STRLEN_RESULT];
	unsigned int stringlength = sprintf(
		(char*)string, "Test result:\n\r"
				"MODE: %d\n\r"
				"WORD COUNT: %d\n\r"
				"ERROR COUNT: %d\n\r",
				mode, wordsWritten, errors
	);
	uart_write(string,stringlength);
}

