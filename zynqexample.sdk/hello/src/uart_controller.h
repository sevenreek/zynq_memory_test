#ifndef SRC_UART_CONTROLLER_H_
#define SRC_UART_CONTROLLER_H_

// INCLUDES
#include "xuartlite.h"
#include "xuartlite_l.h"
#include "xparameters.h"

// CONSTANTS
#define UART_BASEADDRESS 	XPAR_UARTLITE_0_BASEADDR
#define UART_BAUDRATE	 	AXI_UARTLITE_0_BAUDRATE
#define UART_PARITY 		XPAR_AXI_UARTLITE_0_USE_PARITY
#define UART_ODDPARITY 		XPAR_AXI_UARTLITE_0_ODD_PARITY
#define UART_DATABITS 		XPAR_AXI_UARTLITE_0_DATA_BITS
#define UART_USE_XPRINTF 	TRUE
#define UART_USE_INBYTE 	TRUE

// CONDITIONAL INCLUDES
#if UART_USE_XPRINTF == TRUE
#include "xil_printf.h"
#endif
#if UART_USE_INBYTE == TRUE
extern char inbyte();
#endif
// GLOBALS
XUartLite uart_xMainDriver;

// FUNCTION PROTOTYPES
int uart_begin();
int uart_write(unsigned char * buffer, unsigned int size);
unsigned char uart_getchar();

#endif /* SRC_UART_CONTROLLER_H_ */

