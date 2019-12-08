#include <stdio.h>
#include "platform.h"

#include "xparameters.h"


#include "xstatus.h"

#include "menu_controller.h"
#include "gpiotest_controller.h"

int main()
{

    init_platform();
    uart_begin();
    xgpiotest_init();
    xgpiotest_quickTest(GPIOTESTPATTERN_A);
    xgpiotest_quickTest(GPIOTESTPATTERN_5);
    menu_writeMain();
    cleanup_platform();
    return 0;
}
