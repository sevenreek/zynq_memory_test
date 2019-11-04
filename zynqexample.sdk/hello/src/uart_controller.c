/*
 * uart_controller.c
 *
 *  Created on: Nov 3, 2019
 *      Author: Dickbutt
 */
#include "uart_controller.h"
extern XUartLite uart_xMainDriver;


int uart_begin()
{
	return XUartLite_Initialize(&uart_xMainDriver, XPAR_UARTLITE_0_DEVICE_ID);
}



#if UART_USE_XPRINTF == TRUE
int uart_write(unsigned char * buffer, unsigned int size)
{
	xil_printf(buffer);
}
#else
int uart_write(unsigned char * buffer, unsigned int size)
{
	return XUartLite_Send(&uart_xMainDriver, buffer, size);
}
#endif
#if UART_USE_INBYTE == TRUE
unsigned char uart_getchar()
{
	return inbyte();
}
#else
unsigned char uart_getchar()
{
	return XUartLite_RecvByte(UART_BASEADDRESS);
}
#endif


