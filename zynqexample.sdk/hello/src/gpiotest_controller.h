/*
 * gpiotest_controller.h
 *
 *  Created on: Dec 8, 2019
 */

#ifndef SRC_GPIOTEST_CONTROLLER_H_
#define SRC_GPIOTEST_CONTROLLER_H_

#include "xparameters.h"
#include "xgpio.h"
#include "uart_controller.h"
#include <stdio.h>
#define XGPIO_CHANNEL_COUNT 1
#define XGPIOTEST_CROSSCHANNEL_IO FALSE
#define XGPIO_PAIR_COUNT 8
#define XGPIO_DEVICE  XPAR_GPIO_0_DEVICE_ID
#define GPIOTEST_STRLEN 32
#define GPIOTEST_HIGH 1
#define GPIOTEST_LOW 0
#if XGPIOTEST_CROSSCHANNEL_IO == TRUE 
#define XGPIOTEST_INPUT_CHANNEL 1
#define XGPIOTEST_OUTPUT_CHANNEL 2
extern const unsigned char XGPIO_INPUT_PAIRS [XGPIO_PAIR_COUNT];
extern const unsigned char XGPIO_OUTPUT_PAIRS [XGPIO_PAIR_COUNT];
#else
extern const unsigned char XGPIO_INPUT_PAIRS [XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT];
extern const unsigned char XGPIO_OUTPUT_PAIRS [XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT];
#endif
enum GpioTestPatterns {
	GPIOTESTPATTERN_A,
	GPIOTESTPATTERN_5,
	GPIOTESTPATTERN_0,
	GPIOTESTPATTERN_1
};
int xgpiotest_init();
u32 xgpiotest_getInputMask(unsigned char channel);
u32 xgpiotest_getOutputMask(unsigned char channel);
void xgpiotest_quickTest(enum GpioTestPatterns pattern);
unsigned char gpiotest_getNextPinValue(unsigned char pairIndex, enum GpioTestPatterns pattern);
#endif /* SRC_GPIOTEST_CONTROLLER_H_ */
