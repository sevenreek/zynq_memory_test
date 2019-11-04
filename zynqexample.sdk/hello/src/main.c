#include <stdio.h>
#include "platform.h"

#include "xparameters.h"


#include "xstatus.h"

#include "menu_controller.h"


int main()
{
    init_platform();
    uart_begin();
    menu_writeMain();
    cleanup_platform();
    return 0;
}
