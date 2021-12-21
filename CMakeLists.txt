cmake_minimum_required (VERSION 2.8.12)

project (test_LED)

set (DIR ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
set (CMAKE_MODULE_PATH ${DIR}/cmake)

set (CMAKE_SYSROOT $ENV{SDKTARGETSYSROOT} CACHE PATH "Path to sysroot")
#set (CMAKE_SKIP_RPATH true CACHE INTERNAL "")

# Cmake options
option (DEBUG_MODE "Enable debug output" OFF)

# Source files
add_executable (test_led
	./main.cpp
	./led_driver.c
	#./gst.c
)

include_directories(test_led
	.)
