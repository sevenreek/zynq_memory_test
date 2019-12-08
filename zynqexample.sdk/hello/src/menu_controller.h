/*
 * menu_controller.h
 *
 *  Created on: Nov 3, 2019
 */

#ifndef SRC_MENU_CONTROLLER_H_
#define SRC_MENU_CONTROLLER_H_
#include <stdio.h>
#include "uart_controller.h"
#include "memtest_controller.h"
#define MENU_STRLEN_MAIN 256
#define MENU_STRLEN_RESPONSE 32
#define MENU_MEMTEST_SIZE_POSSIBLITIES 9
#define MENU_QUICKTEST_PATTERN_POSSIBLITIES 5
#define MENU_DETAILTEST_PATTERN_POSSIBLITIES 3
#define MENU_INCREMENT_BYTES_POSSIBILITES 5
#define MENU_TEST_MODE_QUICK 0
#define MENU_TEST_MODE_DETAIL 1
#define MENU_MEMTEST_VERB_POSSIBLITIES 3
#define MENU_MEMTEST_READCOUNT_MAX 2


extern const unsigned int MEMORY_TEST_SIZES[MENU_MEMTEST_SIZE_POSSIBLITIES];
extern const unsigned int MEMORY_TEST_INCREMENTS[MENU_INCREMENT_BYTES_POSSIBILITES];

void menu_writeMain();
char menu_getChar();
void menu_awaitInput();
char* menu_getVerbosityString(enum MemTestVerbosity verbosity);
char* menu_getTestModeString(char mode, char pattern);


#endif /* SRC_MENU_CONTROLLER_H_ */


