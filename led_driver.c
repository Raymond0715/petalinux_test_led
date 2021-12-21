#include "led_driver.h"

int UioInfoReadMapSize(uio_led_config* uio_led_info) {
	int ret;
	char file[] = "/sys/class/uio/uio8/maps/map0/size";
	FILE* fp = fopen(file, "r");
	if (!fp) {
		printf("[ERROR][led_driver.c] Fail to open UIO size file.\n");
		return FAIL;
	}

	ret = fscanf(fp, "0x%x", &uio_led_info->size);
	if (ret < 0) {
		printf("[ERROR][led_driver.c] Fail to read UIO size.\n");
	}

	fclose(fp);

	return SUCCESS;
}

int LedInit(led_config* instance_ptr) {
	int func_status;
	char file[256];
	uio_led_config uio_led_info;

	func_status = UioInfoReadMapSize(&uio_led_info);
	if (!func_status) {
		printf("[ERROR][led_driver.c] UioInfoReadMapSize Failed.\n");
		return FAIL;
	}

	sprintf(file, "/dev/uio8");
	if ((uio_led_info.uio_fd = open(file, O_RDWR)) < 0) {
		printf("[ERROR][led_driver.c] Fail to get uio_fd.\n");
		return FAIL;
	}
#ifdef DEBUG
	printf("[DEBUG][led_driver.cpp] uio_led_info.size: %zu.\n", uio_led_info.size);
	printf("[DEBUG][led_driver.cpp] uio_led_info.uio_fd: %d.\n", uio_led_info.uio_fd);
#endif
	instance_ptr->led_base_address = (uint64_t)mmap(
			NULL, uio_led_info.size, PROT_READ | PROT_WRITE,
			MAP_SHARED, uio_led_info.uio_fd, 0);

	return SUCCESS;
}
