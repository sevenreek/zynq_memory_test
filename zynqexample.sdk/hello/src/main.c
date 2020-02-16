#include <stdio.h>
#include "platform.h"

#include "xparameters.h"


#include "xstatus.h"

#include "menu_controller.h"

#define TEST_UART_LOOP FALSE
#define AUTO_TEST_MEMORY TRUE
int main()
{
    init_platform();
    uart_begin();
    uart_write("Device booted.\n\r",15);
#if TEST_UART_LOOP == TRUE
    unsigned char buf[1];
    while(TRUE)
    {
    	unsigned char c = uart_getchar();
    	if(c <= 'Z' && c>='A')
    	{
    		buf[0] = c ^ 32;
    	}
    	else if(c<='z' && c>='a')
    	{
    		buf[0] = c ^ 32;
    	}
    	else
    	{
    		buf[0] = c;
    	}
    	uart_write(buf,1);
    }
#endif
#if MEMTEST_SIMULATED_ERROR_PROBABILITY_PROMILE > 0
    uart_write("Error simulation is enabled.\n\r",30);
#endif
#if AUTO_TEST_MEMORY == TRUE
    uart_write("Running quick memory test.\n\r",27);
    memtest_performQuickTest(
		4096, // test a few words
		QUICKPATTERN_ADDRESS,
		1, // single read
		1, // increment by single word
		MTESTVERBOSITY_BAD
   );
#endif
    menu_writeMain();
    cleanup_platform();
    return 0;
}
