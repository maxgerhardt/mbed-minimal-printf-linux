#include <cstdio>
#include <climits>
#include <ctime>

extern "C" {
#include "mbed_printf_implementation.h"
}

/* duplicate printf wrapper but with correct code.. .*/
/* -Wl flags in CmakeLists.txt currently broken */
int mbed_minimal_printf(const char* format, ...) {
    va_list arguments;
    va_start(arguments, format);
    int result = mbed_minimal_formatted_string(NULL, INT_MAX, format,
                                               arguments, stdout);
    //    int result = mbed_minimal_formatted_string(NULL, LONG_MAX, format,
//                                               arguments, stdout);
    va_end(arguments);
    return result;
}

void test_regression() {
    int sf=7;
    int spi_enabled = 0;
    int radio_enabled = 1;
    // width-specifier + width
    //expecting 0012 03
    mbed_minimal_printf("Test width + width: %04d %02d [expecting 0012 03]\n", 12, 3);
    // width-specified + no width
    //expecting 07:01
    mbed_minimal_printf("Test width + no width: [%02d:%d%d] [expecting 07:01]\n", sf, spi_enabled, radio_enabled);

    mbed_minimal_printf("Test No width + width + no Width: [%d:%02d:%d%d] [expecting 1337:07:01]\n", 1337, sf, spi_enabled, radio_enabled);

    int someVal = 1;
    //expecting 64-bit pointer hex, e.g. 0x7FFC88D27B08
    mbed_minimal_printf("Test pointer: %p [expecting e.g. 0x7FFC88D27B08]\n", &someVal);
    mbed_minimal_printf("Test pointer with zeros: %p [expecting 0x07FFC88D27B0]\n", 0x07FFC88D27B0ULL);

    //expecting 0x01223344
    mbed_minimal_printf("Test 8 hex: 0x%08x [expecting 0x01223344]\n", 0x01223344);
    //expecting 0x0123
    mbed_minimal_printf("Test 4 hex: 0x%04x [expecting 0x0123]\n", 0x0123);

    mbed_minimal_printf("Test 3 hex: 0x%03x [expecting 0x123]\n", 0x123);

    mbed_minimal_printf("Testing normal %%x hex: 0x%x [expecting 0x12345]\n", 0x12345);

    //4 chars (including \0)
    char identification[4] = "ABC";
    //only print first two chars
    mbed_minimal_printf("String with max chars: %.2s [expecting AB]\n", identification);

}

void test_float_regression() {
    float diff_time = 123.123f;
    long long int now = time(nullptr) * 1000LL;
    mbed_minimal_printf(
            "Time to HS expiry is %lld (%.2f) with now = %lld expiresHSTime = %lld\n",
            (long long int) diff_time, diff_time, now, now + 1LL);

}

int main() {
    printf("Teeeest\n");
    fflush(stdout);
    //mbed_minimal_printf("sizeof long = %d sizeof int = %d\n", (int)sizeof(long), (int)sizeof(int));
    mbed_minimal_printf("mbed formatting test\n");

    test_regression();
    test_float_regression();
    return 0;
}