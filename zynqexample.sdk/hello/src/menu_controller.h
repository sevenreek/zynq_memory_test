/*
 * menu_controller.h
 *
 *  Created on: Nov 3, 2019
 *      Author: Dickbutt
 */

#ifndef SRC_MENU_CONTROLLER_H_
#define SRC_MENU_CONTROLLER_H_
#include <stdio.h>
#include "uart_controller.h"
#include "memtest_controller.h"
#define MENU_STRLEN_MAIN 128
#define MENU_STRLEN_RESPONSE 32
#define MENU_MEMTEST_SIZE_POSSIBLITIES 8
#define MENU_MEMTEST_MODE_POSSIBLITIES 3
#define MENU_MEMTEST_VERB_POSSIBLITIES 3
enum MemTestVerbosity {
	MTESTVERBOSITY_NONE,
	MTESTVERBOSITY_BAD,
	MTESTVERBOSITY_ALL
};
extern const unsigned int MEMORY_TEST_SIZES[MENU_MEMTEST_SIZE_POSSIBLITIES];


void menu_writeMain();
char menu_getChar();
void menu_awaitInput();
char* menu_getVerbosityString(enum MemTestVerbosity verbosity);
char* menu_getTestModeString(enum MemTestModes mode);


#endif /* SRC_MENU_CONTROLLER_H_ */
