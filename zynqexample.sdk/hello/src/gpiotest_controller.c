/*
 * gpiotest_controller.c
 *
 *  Created on: Dec 8, 2019
 */
#include "gpiotest_controller.h"
#if XGPIOTEST_CROSSCHANNEL_IO == TRUE
const unsigned char XGPIO_INPUT_PAIRS [XGPIO_PAIR_COUNT];
const unsigned char XGPIO_OUTPUT_PAIRS [XGPIO_PAIR_COUNT];
#else 
const unsigned char XGPIO_INPUT_PAIRS [XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT] = {{0,2,4,6,8,10,12,14}};
const unsigned char XGPIO_OUTPUT_PAIRS[XGPIO_CHANNEL_COUNT][XGPIO_PAIR_COUNT] = {{1,3,5,7,9,11,13,15}};
#endif
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
#if XGPIOTEST_CROSSCHANNEL_IO == TRUE
void xgpiotest_quickTest(enum GpioTestPatterns pattern)
{
	u32 writeClearMask = 0x0;
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		writeClearMask |= ( (1UL) << XGPIO_OUTPUT_PAIRS[pairIndex] );
	}
	XGpio_DiscreteClear(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeClearMask);
	u32 writeValue = 0x0;
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		writeValue |= ( (1UL & gpiotest_getNextPinValue(pairIndex,pattern)) << XGPIO_OUTPUT_PAIRS[pairIndex] );
	}
	XGpio_DiscreteWrite(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeMask);
	u32 readMask = XGpio_DiscreteRead(&GPIO,XGPIOTEST_INPUT_CHANNEL);
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		int pinIndex = XGPIO_INPUT_PAIRS[pairIndex];
		char readPin = ((readMask >> pinIndex) & 0b1);
		if( readPin != gpiotest_getNextPinValue(pairIndex, pattern))
		{
			unsigned char string[GPIOTEST_STRLEN];
			unsigned int stringlength = sprintf((char*)string, "GPIO: Xchannel error on pair %d\n\r",XGPIO_OUTPUT_PAIRS[pairIndex]);
			uart_write(string,stringlength);
		}
	}
}
void xgpiotest_longTest(char holdValue)
{
	u32 writeResetMask = 0x0;
	for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
	{
		writeResetMask |= ( (1UL) << XGPIO_OUTPUT_PAIRS[pairIndex] );
	}
	if(holdValue = 0x1)
	{
		XGpio_DiscreteSet(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeResetMask);
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			newWriteMask = 	( (1UL) << XGPIO_OUTPUT_PAIRS[pairIndex] );
			newReadMask = 	( (1UL) << XGPIO_INPUT_PAIRS[pairIndex] );
			XGpio_DiscreteClear(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, newWriteMask);
			u32 readMask = XGpio_DiscreteRead(&GPIO,XGPIOTEST_INPUT_CHANNEL);
			if((readMask & newReadMask) != 0x0)
			{
				unsigned char string[GPIOTEST_STRLEN];
				unsigned int stringlength = sprintf((char*)string, "GPIO: Error on Xpair %d\n\r",XGPIO_OUTPUT_PAIRS[pairIndex]);
				uart_write(string,stringlength);
			}
			XGpio_DiscreteSet(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeResetMask);
		}
	}
	else
	{
		XGpio_DiscreteClear(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeResetMask);
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			newWriteMask = 	( (1UL) << XGPIO_OUTPUT_PAIRS[pairIndex] );
			newReadMask = 	( (1UL) << XGPIO_INPUT_PAIRS[pairIndex] );
			XGpio_DiscreteSet(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, newWriteMask);
			u32 readMask = XGpio_DiscreteRead(&GPIO,XGPIOTEST_INPUT_CHANNEL);
			if((readMask & newReadMask) != newReadMask)
			{
				unsigned char string[GPIOTEST_STRLEN];
				unsigned int stringlength = sprintf((char*)string, "GPIO: Error on Xpair %d\n\r",XGPIO_OUTPUT_PAIRS[pairIndex]);
				uart_write(string,stringlength);
			}
			XGpio_DiscreteClear(&GPIO, XGPIOTEST_OUTPUT_CHANNEL, writeResetMask);
		}
	}
}
#else
void xgpiotest_quickTest(enum GpioTestPatterns pattern)
{
	
	for(int channel = 0; channel < XGPIO_CHANNEL_COUNT; channel++)
	{
		u32 writeClearMask = 0x0;
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			writeClearMask |= ( (1UL) << XGPIO_OUTPUT_PAIRS[channel][pairIndex] );
		}
		XGpio_DiscreteClear(&GPIO, channel+1, writeClearMask);
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

void xgpiotest_longTest(char holdValue)
{
	for(int channel = 0; channel < XGPIO_CHANNEL_COUNT; channel++)
	{
		u32 writeResetMask = 0x0;
		for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
		{
			writeResetMask |= ( (1UL) << XGPIO_OUTPUT_PAIRS[channel][pairIndex] );
		}
		if(holdValue == GPIOTEST_HIGH)
		{
			XGpio_DiscreteSet(&GPIO, channel+1, writeResetMask);
			for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
			{
				u32 newWriteMask = 	( (1UL) << XGPIO_OUTPUT_PAIRS[channel][pairIndex] );
				u32 newReadMask = 	( (1UL) << XGPIO_INPUT_PAIRS[channel][pairIndex] );
				XGpio_DiscreteClear(&GPIO, channel+1, newWriteMask);
				u32 readMask = XGpio_DiscreteRead(&GPIO,channel+1);
				if((readMask & newReadMask) != 0x0)
				{
					unsigned char string[GPIOTEST_STRLEN];
					unsigned int stringlength = sprintf((char*)string, "GPIO: Error on pair %d-%d\n\r",XGPIO_OUTPUT_PAIRS[channel][pairIndex],XGPIO_INPUT_PAIRS[channel][pairIndex]);
					uart_write(string,stringlength);
				}
				XGpio_DiscreteSet(&GPIO, channel+1, writeResetMask);
			}
		}
		else
		{
			XGpio_DiscreteClear(&GPIO, channel+1, writeResetMask);
			for(int pairIndex = 0; pairIndex < XGPIO_PAIR_COUNT; pairIndex++)
			{
				u32 newWriteMask = 	( (1UL) << XGPIO_OUTPUT_PAIRS[channel][pairIndex] );
				u32 newReadMask = 	( (1UL) << XGPIO_INPUT_PAIRS[channel][pairIndex] );
				XGpio_DiscreteSet(&GPIO, channel+1, newWriteMask);
				u32 readMask = XGpio_DiscreteRead(&GPIO,channel+1);
				if((readMask & newReadMask) != newReadMask)
				{
					unsigned char string[GPIOTEST_STRLEN];
					unsigned int stringlength = sprintf((char*)string, "GPIO: Error on pair %d-%d\n\r",XGPIO_OUTPUT_PAIRS[channel][pairIndex],XGPIO_INPUT_PAIRS[channel][pairIndex]);
					uart_write(string,stringlength);
				}
				XGpio_DiscreteClear(&GPIO, channel+1, writeResetMask);
			}
		}
	}
}
#endif
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
