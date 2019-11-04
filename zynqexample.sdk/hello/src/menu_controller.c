/*
 * menu_controller.c
 *
 *  Created on: Nov 3, 2019
 *      Author: Dickbutt
 */
#include "menu_controller.h"


const unsigned int MEMORY_TEST_SIZES[MENU_MEMTEST_SIZE_POSSIBLITIES] = {4, 16, 64, 1024, 4096, 16384, 65536, 262144};
enum MemTestModes config_memoryTestMode = MTESTMODE_ZEROES;
unsigned int config_memoryTestSize = 0;
enum MemTestVerbosity config_memoryTestVerbosity = MTESTVERBOSITY_BAD;
void menu_writeMain()
{
	unsigned char string[MENU_STRLEN_MAIN];
	unsigned int stringlength = sprintf(
			(char*)string,
			"Memory test:\n\r"
			"\tm - switch test mode\n\r"
			"\ts - switch test size\n\r"
			"\tv - switch test verbosity\n\r"
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
				config_memoryTestMode = (config_memoryTestMode+1)%MENU_MEMTEST_MODE_POSSIBLITIES;
				stringlength = sprintf(
						(char*)string,
						"switched to %s\n\r",
						menu_getTestModeString(config_memoryTestMode)
						);
				uart_write(string,stringlength);
			break;
			case 's':
				config_memoryTestSize = (config_memoryTestSize+1)%MENU_MEMTEST_SIZE_POSSIBLITIES;
				stringlength = sprintf(
						(char*)string,
						"switched to %dB\n\r",
						MEMORY_TEST_SIZES[config_memoryTestSize]
					  	);
				uart_write(string,stringlength);
			break;
			case 'v':
				config_memoryTestVerbosity = (config_memoryTestVerbosity+1)%MENU_MEMTEST_VERB_POSSIBLITIES;
				stringlength = sprintf(
						(char*)string,
						"switched to %s\n\r",
						menu_getVerbosityString(config_memoryTestVerbosity)
						);
				uart_write(string,stringlength);
			break;
			case 'r':
				memtest_performTest(MEMORY_TEST_SIZES[config_memoryTestSize], config_memoryTestMode);
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
char* menu_getTestModeString(enum MemTestModes mode)
{
	switch(mode)
	{
		case MTESTMODE_DEADBEEF:
			return "0xDEADBEEF";
			break;
		case MTESTMODE_WALKINGONE:
			return "WALKING ONE";
			break;
		default: return "???";
			break;
	}
}

