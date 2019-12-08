/*
 * gpiotest_controller.c
 *
 *  Created on: Dec 8, 2019
 */
#include "gpiotest_controller.h"
const unsigned char XGPIO_INPUT_PAIRS [XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT] = {{0,2,4,6,8,10,12,14}};
const unsigned char XGPIO_OUTPUT_PAIRS[XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT] = {{1,3,5,7,9,11,13,15}};
XGpio GPIO;
int xgpiotest_init()
{
	int initresult = XGpio_Initialize(&GPIO, XGPIO_DEVICE);
	XGpio_SetDataDirection(&GPIO,1,xgpiotest_getInputMask(0));
#if XGPIO_CHANNEL_COUNT>1
	XGpio_SetDataDirection(&GPIO,2,xgpiotest_getInputMask(1));
#endif
	u32 readMask = XGpio_DiscreteRead(&GPIO,1);
	return initresult | (readMask&0);
}
u32 xgpiotest_getInputMask(unsigned char channel)
{
	u32 mask = 0x0;
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		mask |= ((1UL) << XGPIO_INPUT_PAIRS[channel][pairIndex]);
	}
	return mask;
}
u32 xgpiotest_getOutputMask(unsigned char channel)
{
	u32 mask = 0x0;
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		mask |= ((1UL) << XGPIO_OUTPUT_PAIRS[channel][pairIndex]);
	}
	return mask;
}
void xgpiotest_quickTest(enum GpioTestPatterns pattern)
{
	for(int channel = 0; channel < XGPIO_CHANNEL_COUNT; channel++)
	{
		u32 writeMask = 0x0;
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			writeMask |= ( (1UL & gpiotest_getNextPinValue(pairIndex,pattern)) << XGPIO_OUTPUT_PAIRS[channel][pairIndex] );
		}
		XGpio_DiscreteWrite(&GPIO, channel+1, writeMask);
	}
	for(int channel = 0; channel < XGPIO_CHANNEL_COUNT; channel++)
	{
		u32 readMask = XGpio_DiscreteRead(&GPIO,channel+1);
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			int pinIndex = XGPIO_INPUT_PAIRS[channel][pairIndex];
			char readPin = ((readMask >> pinIndex) & 0b1);
			if( readPin != gpiotest_getNextPinValue(pairIndex, pattern))
			{
				unsigned char string[GPIOTEST_STRLEN];
				unsigned int stringlength = sprintf((char*)string, "GPIO: Error on pair %d-%d\n\r",XGPIO_OUTPUT_PAIRS[channel][pairIndex],XGPIO_INPUT_PAIRS[channel][pairIndex]);
				uart_write(string,stringlength);
			}
		}
	}
}
unsigned char gpiotest_getNextPinValue(unsigned char pairIndex, enum GpioTestPatterns pattern)
{
	switch (pattern)
	{
		case GPIOTESTPATTERN_A:
			return (pairIndex+1)%2;
		break;
		case GPIOTESTPATTERN_5:
			return pairIndex%2;
		break;
		case GPIOTESTPATTERN_0:
			return 0b0;
		break;
		case GPIOTESTPATTERN_1:
			return 0b1;
		break;
		default:
			return 0b0;
		break;

	}
}
