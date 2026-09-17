#include <stdio.h>
#include "banner.h"

#define C_RED     "\033[1;31m"
#define C_GREEN   "\033[1;32m"
#define C_CYAN    "\033[1;36m"
#define C_WHITE   "\033[1;37m"
#define C_GRAY    "\033[0;90m"
#define C_RESET   "\033[0m"

void print_banner(void)
{
    printf(C_RED
"   ____  _     ____ ___ \n"
"  / __ \\| |   |  _ \\_ _|\n"
" | |  | | |   | |_) | | \n"
" | |__| | |___|  __/| | \n"
"  \\____/|_____|_|  |___|\n"
    C_RESET);

    printf(C_CYAN "        Octane's Linux Process Injector\n" C_RESET);
    printf(C_GRAY "        ------------------------------\n" C_RESET);
    printf(C_WHITE "        made by " C_RED "octane0x\n\n" C_RESET);
} 
//TODO: Add style to olpi.c
//TODO: Make this banner less ass
