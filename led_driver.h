#ifndef __LED_DRIVER_H__
#define __LED_DRIVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>

#define SUCCESS 1
#define FAIL    0
//#define DEBUG

#define LED_WRITE_REG(led_base_address, reg_offset, data) \
	*(volatile uint64_t*)((led_base_address) + (reg_offset)) = (uint32_t)(data)

	typedef struct {
		uint64_t led_base_address;
	} led_config;

	typedef struct {
		int uio_fd;
		int uio_num;
		uint64_t addr;
		uint32_t size;
	} uio_led_config;
	
	int LedInit(led_config* instance_ptr);

#ifdef __cplusplus
}
#endif

#endif
