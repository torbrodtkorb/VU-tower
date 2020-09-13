#include "basic_functions.h"
/*

//==================== BASIC FUNCTIONS ===========================
void lamp_on(uint8_t r, uint8_t g, uint8_t b) {
	uint8_t start_number = 0;
	for (uint8_t i = start_number; i < start_number + 63; i++) {
		pixels[i] = (rgb_color){r, g, b};
	}
}

void layer_on(uint8_t layer, uint8_t r, uint8_t g, uint8_t b) {
	uint8_t start_number = (layer - 1) * 9;
	for (uint8_t i = start_number; i < start_number + 9; i++) {
		pixels[i] = (rgb_color){r, g, b};
	}
}

void layer_off(uint8_t layer) {
	uint8_t start_number = (layer - 1) * 9;
	for (uint8_t i = start_number; i < start_number + 9; i++) {
		pixels[i] = (rgb_color){0, 0, 0};
	}
}

void initialize_led(void) {
	led_strip_write(pixels, NUMBER_OF_LEDS);
}

void show(void) {
	led_strip_write(pixels, NUMBER_OF_LEDS);
	
}
//================================================================*/