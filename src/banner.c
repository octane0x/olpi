#include <stdio.h>
#include "banner.h"
#include "colors.h"

void print_banner(void)
{
    printf(C_RED
"   ____  _     ____ ___ \n"
"  / __ \\| |   |  _ \\_ _|\n"
" | |  | | |   | |_) | | \n"
" | |__| | |___|  __/| | \n"
"  \\____/|_____|_|  |___|\n"
    C_RESET);

    printf(C_CYAN "        Octane's Linux Process Injector v1.1\n" C_RESET);
    printf(C_GRAY "        ------------------------------\n" C_RESET);
    printf(C_WHITE "        made by " C_GREEN "octane0x\n\n" C_RESET);
} //TODO: Make this banner less ass