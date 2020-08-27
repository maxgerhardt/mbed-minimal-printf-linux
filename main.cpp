#include <cstdio>
#include <climits>

extern "C" {
#include "mbed_printf_implementation.h"
}

/* duplicate printf wrapper but with correct code.. .*/
/* -Wl flags in CmakeLists.txt currently broken */
int mbed_minimal_printf(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    int result = mbed_minimal_formatted_string(NULL, INT_MAX-1, format,
                                               arguments, stdout);
    //    int result = mbed_minimal_formatted_string(NULL, LONG_MAX, format,
//                                               arguments, stdout);
    va_end(arguments);
    return result;
}


int main() {
    mbed_minimal_printf("mbed formatting test\n");
    return 0;
}