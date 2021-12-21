#include <unistd.h>
#include "led_driver.h"

int main() {
	printf("[INFO][main.cpp] Application start.\n");
	unsigned int led = 1;
	int func_status;
	led_config led_instance;

	printf("[INFO][main.cpp] Initialize led.\n");
	func_status = LedInit(&led_instance);
	if (!func_status) {
		printf("[ERROR][main.cpp] LedInit Failed.\n");
		return -1;
	}
	printf("[INFO][main.cpp] Start loop.\n");
	while (1){
		led = led << 1;
		if (led == 0x100) {
			led = 1;
		}
#ifdef DEBUG
		printf("[DEBUG][main.cpp] Write register: %ju.\n", led_instance.led_base_address);
#endif
		LED_WRITE_REG(led_instance.led_base_address, 0, led);
		sleep(1);
	}
	return 0;
}
