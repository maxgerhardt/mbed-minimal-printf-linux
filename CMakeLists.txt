cmake_minimum_required(VERSION 3.17)
project(minimal_printf_debugging)

set(CMAKE_CXX_STANDARD 14)
add_compile_definitions(MBED_MINIMAL_PRINTF)
set (CMAKE_CXX_FLAGS "-Wl,--wrap,printf")
add_executable(minimal_printf_debugging main.cpp mbed_printf_implementation.c mbed_printf_wrapper.c)