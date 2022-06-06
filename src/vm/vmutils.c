
#include <stdarg.h>

void avm_warning(int line, const char * warformat, ...)
{
    #define error_msg "\033[0;35mWarrning\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

    va_list print_args;

    va_start(print_args, warformat);

    printf(error_msg, line);
    vprintf(warformat, print_args);

    va_end(print_args);
}