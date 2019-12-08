/*
 * memtest_controller.c
 *
 *  Created on: Nov 3, 2019
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

unsigned int memtest_getNextQuickPattern(unsigned int counter, enum QuickTestPatterns mode)
{
	switch(mode)
	{
		case QUICKPATTERN_ZEROES:
			return 0x0;
			break;
		case QUICKPATTERN_ONES:
			return 0xFFFFFFFF;
			break;
		case QUICKPATTERN_DEADBEEF:
			return 0xDEADBEEF;
		break;
		case QUICKPATTERN_WALKINGONE:
			return 1UL << (counter%32);
		break;
		case QUICKPATTERN_A:
			return 0xAAAAAAAA;
		break;
		default:
			return 0x0;
		break;
	}
}
unsigned int memtest_getNextDetailPattern(unsigned int memoryPoint, unsigned char concurrentTest, enum DetailTestPatterns mode)
{
	switch(mode)
	{
		case DETAILPATTERN_A5ALTERNATING:
			return concurrentTest%2?0xAAAAAAAA:0x55555555;
			break;
		case DETAILPATTERN_WALKINGONE:
			return 1UL << ( concurrentTest % 32 );
		break;
		case DETAILPATTERN_WALKINGZERO:
			return ~(1UL << ( concurrentTest % 32 ));
		break;
		default:
			return 0x0;
		break;
	}
}
unsigned int memtest_getDetailPatternTestCount(enum DetailTestPatterns mode)
{
	switch(mode)
	{
		case DETAILPATTERN_A5ALTERNATING:
			return 2;
			break;
		case DETAILPATTERN_WALKINGONE:
			return 32;
		break;
		case DETAILPATTERN_WALKINGZERO:
			return 32;
		break;
		default:
			return 1;
		break;
	}
}
void memtest_performQuickTest(unsigned int wordCount, enum QuickTestPatterns mode, int readCount, unsigned int increment, enum MemTestVerbosity verbosity)
{
	memtest_setVerbosity(verbosity);
	wordCount = wordCount==MEMTEST_SIZE_FULL?(MEMORY_HIGH_ADDRESS - MEMORY_BASE_ADDRESS + 1)/4:wordCount; //
	for(unsigned int counter = 0; counter < wordCount; counter+=increment)
	{
		unsigned int currentAddress =  MEMORY_BASE_ADDRESS + sizeof(unsigned int)*counter;
		unsigned int pattern = memtest_getNextQuickPattern(counter, mode);
		memtest_writeRegister(currentAddress, pattern);
	}
	unsigned int errorCount = 0;
	unsigned char currentReadCount;
	for(unsigned int counter = 0; counter < wordCount; counter+=increment)
	{
		for(currentReadCount = 0; currentReadCount < readCount; currentReadCount++)
		{
			unsigned int currentAddress =  MEMORY_BASE_ADDRESS + sizeof(unsigned int)*counter;
			unsigned int expectedPattern = memtest_getNextQuickPattern(counter, mode);
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
	}
	memtest_writeTestResult(wordCount,errorCount,mode);
}
void memtest_performDetailTest(unsigned int wordCount, enum DetailTestPatterns mode, int readCount, unsigned int increment, enum MemTestVerbosity verbosity)
{
	memtest_setVerbosity(verbosity);
	wordCount = wordCount==MEMTEST_SIZE_FULL?(MEMORY_HIGH_ADDRESS - MEMORY_BASE_ADDRESS + 1)/4:wordCount; //set appropriate wordCount if parameter passed is 0
	unsigned int errorCount = 0;
	unsigned char concurrentTestCount = memtest_getDetailPatternTestCount(mode);
	unsigned char currentConcurrentTestIndex = 0;
	unsigned char currentReadCount;
	for(unsigned int counter = 0; counter < wordCount; counter+=increment)
	{
		unsigned int currentAddress =  MEMORY_BASE_ADDRESS + sizeof(unsigned int)*counter;
		unsigned int pattern;
		for(currentConcurrentTestIndex = 0; currentConcurrentTestIndex < concurrentTestCount; currentConcurrentTestIndex++)
		{
			pattern = memtest_getNextDetailPattern(counter, currentConcurrentTestIndex, mode);
			memtest_writeRegister(currentAddress, pattern);
			for(currentReadCount = 0; currentReadCount < readCount; currentReadCount++)
			{
				unsigned int writtenPattern = memtest_readRegister(currentAddress);
				if(pattern != writtenPattern)
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
void memtest_writeTestResult(unsigned int wordsWritten, unsigned int errors, enum QuickTestPatterns mode)
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
void memtest_setVerbosity(enum MemTestVerbosity verbosity)
{
	switch(verbosity)
	{
		case MTESTVERBOSITY_NONE:
			memtest_cfg_printCorrect = FALSE;
			memtest_cfg_printError = FALSE;
		break;
		case MTESTVERBOSITY_BAD:
			memtest_cfg_printCorrect = FALSE;
			memtest_cfg_printError = TRUE;
		break;
		case MTESTVERBOSITY_ALL:
			memtest_cfg_printCorrect = TRUE;
			memtest_cfg_printError = TRUE;

		break;
		default:
		break;
	}
}

