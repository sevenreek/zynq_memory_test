/*
 * menu_controller.c
 *
 *  Created on: Nov 3, 2019
 */
#include "menu_controller.h"


const unsigned int MEMORY_TEST_SIZES[MENU_MEMTEST_SIZE_POSSIBLITIES]
									 = {MEMTEST_SIZE_FULL, 4, 16, 64, 1024, 4096, 16384, 65536, 262144}; // 0 is full memory
const unsigned int MEMORY_TEST_INCREMENTS[MENU_INCREMENT_BYTES_POSSIBILITES]
									 = {1,4,8,1024,1024*1024};
unsigned char config_memoryTestPattern = QUICKPATTERN_ZEROES;
unsigned char config_memoryTestModeIsDetail = MENU_TEST_MODE_QUICK;
unsigned int config_memoryTestSize = 0;
unsigned int config_memoryTestReadCount = 1;
unsigned int config_memoryTestIncrementBytesChoice = 0;
enum MemTestVerbosity config_memoryTestVerbosity = MTESTVERBOSITY_BAD;
void menu_writeMain()
{
	unsigned char string[MENU_STRLEN_MAIN];
	unsigned int stringlength = sprintf(
			(char*)string,
			"Memory test:\n\r"
			"\tm - toggle mode\n\r"
			"\tp - switch pattern\n\r"
			"\ts - switch size\n\r"
			"\tv - switch verbosity\n\r"
			"\td - switch read count(RDF)\n\r"
			"\ti - switch increment size\n\r"
			"\tr - run test\n\r"
			);
	uart_write(string,stringlength);
	menu_awaitInput();
}

char menu_getChar()
{
	return uart_getchar();
}
void menu_awaitInput()
{
	while(1)
	{
		char c = menu_getChar();
		unsigned char string[MENU_STRLEN_RESPONSE];
		unsigned int stringlength;
		switch(c)
		{
			case 'm':
				config_memoryTestModeIsDetail = (config_memoryTestModeIsDetail+1)%2;
				config_memoryTestPattern = 0;
				stringlength = sprintf(
							(char*)string,
							"mode is now %s\n\r",
							config_memoryTestModeIsDetail?"detailed":"quick"
							);
				uart_write(string,stringlength);
			break;
			case 'p':
				if(config_memoryTestModeIsDetail)
					config_memoryTestPattern = (config_memoryTestPattern+1)%MENU_DETAILTEST_PATTERN_POSSIBLITIES;
				else
					config_memoryTestPattern = (config_memoryTestPattern+1)%MENU_QUICKTEST_PATTERN_POSSIBLITIES;
				stringlength = sprintf(
						(char*)string,
						"pattern is now %s\n\r",
						menu_getTestModeString(config_memoryTestModeIsDetail, config_memoryTestPattern)
						);
				uart_write(string,stringlength);
			break;
			case 's':
				config_memoryTestSize = (config_memoryTestSize+1)%MENU_MEMTEST_SIZE_POSSIBLITIES;
				stringlength = sprintf(
						(char*)string,
						"test size is now %dB\n\r",
						MEMORY_TEST_SIZES[config_memoryTestSize]
					  	);
				uart_write(string,stringlength);
			break;
			case 'v':
				config_memoryTestVerbosity = (config_memoryTestVerbosity+1)%MENU_MEMTEST_VERB_POSSIBLITIES;
				memtest_setVerbosity(config_memoryTestVerbosity);
				stringlength = sprintf(
						(char*)string,
						"verbosity is now %s\n\r",
						menu_getVerbosityString(config_memoryTestVerbosity)
						);
				uart_write(string,stringlength);
			break;
			case 'd':
				config_memoryTestReadCount = config_memoryTestReadCount==1?2:1;
				stringlength = sprintf(
						(char*)string,
						"%d read(s) will be made\n\r",
						config_memoryTestReadCount
						);
				uart_write(string,stringlength);
			break;
			case 'r':
				stringlength = sprintf(
						(char*)string,
						"%s",
						"Running...\n\r"
						);
				uart_write(string,stringlength);
				if(config_memoryTestModeIsDetail)
					memtest_performDetailTest(
							MEMORY_TEST_SIZES[config_memoryTestSize],
							config_memoryTestPattern,
							config_memoryTestReadCount,
							MEMORY_TEST_INCREMENTS[config_memoryTestIncrementBytesChoice],
							config_memoryTestVerbosity
						   );
				else
					memtest_performQuickTest(
							MEMORY_TEST_SIZES[config_memoryTestSize],
							config_memoryTestPattern,
							config_memoryTestReadCount,
							MEMORY_TEST_INCREMENTS[config_memoryTestIncrementBytesChoice],
							config_memoryTestVerbosity
						   );
			break;
			case 'i':
				config_memoryTestIncrementBytesChoice = (config_memoryTestIncrementBytesChoice+1) % MENU_INCREMENT_BYTES_POSSIBILITES;
				stringlength = sprintf(
						(char*)string,
						"increment set to %d words\n\r",
						MEMORY_TEST_INCREMENTS[config_memoryTestIncrementBytesChoice]
						);
				uart_write(string,stringlength);
			break;
			default:
			break;
		}
	}
}
char* menu_getVerbosityString(enum MemTestVerbosity verbosity)
{
	switch(verbosity)
	{
		case MTESTVERBOSITY_NONE:
			return "NONE";
			break;
		case MTESTVERBOSITY_BAD:
			return "ON ERROR";
			break;
		case MTESTVERBOSITY_ALL:
			return "ON ALL";
			break;
		default: return "???";
			break;
	}
}
char* menu_getTestModeString(char mode, char pattern)
{
	if(mode)
	{
		switch(pattern)
		{
			case DETAILPATTERN_A5ALTERNATING:
				return "A/5";
			break;
			case DETAILPATTERN_WALKINGONE:
				return "WALKINGONE";
			break;
			case DETAILPATTERN_WALKINGZERO:
				return "WALKINGZERO";
			break;
			default:
				return "???";
			break;
		}
	}
	else
	{
		switch(pattern)
		{
			case QUICKPATTERN_ZEROES:
				return "ZEROS";
			break;
			case QUICKPATTERN_ONES:
				return "ONES";
			break;
			case QUICKPATTERN_DEADBEEF:
				return "DEADBEEF";
			break;
			case QUICKPATTERN_WALKINGONE:
				return "WALKING ONE";
			break;
			default: return "???";
			break;
		}
	}
}

