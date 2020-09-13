#define F_CPU 8000000UL
#define NUMBER_OF_LEDS 63
#define FADE_SPEED 1

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "Driver.h"
#include "basic_functions.h"


rgb_color pixels[NUMBER_OF_LEDS] = {0};
uint8_t i = 0;


//==================== BASIC FUNCTIONS ===========================
void lamp_on(uint8_t r, uint8_t g, uint8_t b) {
	uint8_t start_number = 0;
	for (uint8_t i = start_number; i < start_number + NUMBER_OF_LEDS; i++) {
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

float hue2rgb(float p, float q, float t) {
	if(t < 0) t += 1;
	if(t > 1) t -= 1;
	if(t < 1/6.0) return p + (q - p) * 6 * t;
	if(t < 1/2.0) return q;
	if(t < 2/3.0) return p + (q - p) * (2/3.0 - t) * 6;
	return p;
}

void hslToRgb(float h, float s, float l, char rgb[]) {
	float r, g, b;

	if (s == 0) {
		r = g = b = l; // achromatic
		} else {
		float q = l < 0.5 ? l * (1 + s) : l + s - l * s;
		float p = 2 * l - q;
		r = hue2rgb(p, q, h + 1/3.0);
		g = hue2rgb(p, q, h);
		b = hue2rgb(p, q, h - 1/3.0);
	}

	rgb[0] = r * 255;
	rgb[1] = g * 255;
	rgb[2] = b * 255;
}
//================================================================


//==================== PROGRAMS ==================================

void blue_lagoon(void) {
	i = 0;
	while(i < 7) {
		i++;
		layer_on(i,150,80,0);
		show();
		_delay_ms(50);
	}
	
	
	while(i > 0) {
		layer_on(i,0,0,0);
		show();
		_delay_ms(50);
		i--;
	}
}

void mit_and_out(uint8_t r, uint8_t g, uint8_t b) {
	i = 4;
	layer_on(i,r,g,b);
	show();
	_delay_ms(50);
	
	while (i < 7) {
		i++;
		layer_on(i,r,g,b);
		layer_on(8 - i,r,g,b);
		show();
		_delay_ms(50);
	}

	while (i > 4) {
		layer_on(i,0,0,0);
		layer_on(8 - i,0,0,0);
		show();
		_delay_ms(50);
		i--;
	}
}

void mit_and_out_with_a_twist() {
	i = 4;
	layer_on(i,1,0,1);
	show();
	_delay_ms(50);
	int j = 0;
	uint8_t r = 10;
	uint8_t b = 10;
	while (i < 7) {
		i++;
		j++;
		layer_on(i,r,0,b);
		layer_on(8 - i,r,0,b);
		show();
		_delay_ms(50);
		r += j*20;
		b += j*20;
	}

	r = 10;
	b = 10;

	while (i > 4) {
		layer_on(i,0,0,0);
		layer_on(8 - i,0,0,0);
		show();
		_delay_ms(50);
		i--;
	}
}

void crazy() {
	layer_on(1,0,150,10);
	layer_on(7,0,150,10);
	show ();
	
	while (1) {
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,150,150);
		}
		show();
		_delay_ms(15);
		
		
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,0,0);
		}
		show();
		_delay_ms(15);
	}
}

void crazy_twist() {
	layer_on(1,0,255,10);
	layer_on(7,0,255,10);
	show ();
	
	while (1) {
		
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,255,0);
		}
		show();
		
		
		_delay_ms(15);
		
		
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,0,0);
		}
		show();
		_delay_ms(15);
		
		
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,0,255);
		}
		show();
		
		
		_delay_ms(15);
		
		
		i = 1;
		while (i < 6) {
			i++;
			layer_on(i,0,0,0);
		}
		show();
		_delay_ms(15);
		
		
	}
}

void fade () {
	
	while (i < 100) {
		i++;
		lamp_on(i,i,0);
		show();
	}

	while (i > 0) {
		i--;
		lamp_on(i,i,0);
		show();
		_delay_ms(30);
	}
}

void rainbow(){
	char color1 [3];
	char color2 [3];
	char color3 [3];
	char color4 [3];
	char color5 [3];
	char color6 [3];
	char color7 [3];
	
	float hue = 0;
	while (1) {
		hue = hue+0.01f;
		hue -= (int)hue;
		
		hslToRgb(hue, 1, 0.2f, color1);
		hslToRgb(hue + 0.1429, 1, 0.2f, color2);
		hslToRgb(hue + +.2857, 1, 0.2f, color3);
		hslToRgb(hue + 0.4286, 1, 0.2f, color4);
		hslToRgb(hue + 0.5714, 1, 0.2f, color5);
		hslToRgb(hue + 0.4173, 1, 0.2f, color6);
		hslToRgb(hue + 0.8571, 1, 0.2f, color7);
		
		layer_on(1,color1[0], color1[1], color1[2]);
		layer_on(2,color2[0], color2[1], color2[2]);
		layer_on(3,color3[0], color3[1], color3[2]);
		layer_on(4,color4[0], color4[1], color4[2]);
		layer_on(5,color5[0], color5[1], color5[2]);
		layer_on(6,color6[0], color6[1], color6[2]);
		layer_on(7,color7[0], color7[1], color7[2]);
		show();
		
		
	}
}

void chill(){
	char color [3];
	
	float hue = 0;
	while (1) {
		hue = hue+0.01f;
		hue -= (int)hue;
		
		hslToRgb(hue, 1, 0.2f, color);
		lamp_on(color[0], color[1], color[2]);
		show();
		_delay_ms(300);
		
	}
}

void halloween_edition_configuration(void) {
	//----------------------------------------------------------

	uint8_t intensity[7];;
	int random_one = 0;
	int random_two = 0;
	int random_three = 0;

	random_two = 1;
	for (uint8_t i = 0; i < 7; i++) {
		intensity[i] = 0;
	}
	
	for (int j = 1; j <= 7; j++) {
		layer_on(j, 0, 0, intensity[j-1]);
		
	}
	show();
	int count = 1;
	//--------------------------------------------------------
	while (1) {
		random_one = rand() % 7;
		random_two = rand() % 50;
		random_three = rand() % 100;

		if (random_two == 1) {
			intensity[random_one] = 200;
			//intensity[random_three] = 255;
		}
		
		for (int j = 1; j <= 7; j++) {
			layer_on(j, 0, 0, intensity[j-1]);
		}
		show();
		for (uint8_t i = 0; i < 7; i++) {
			if (intensity[i] >= FADE_SPEED) intensity[i] -= FADE_SPEED; else intensity[i] = 0;
		}
		
	}
}
//================================================================


int main(void) {
	initialize_led();
	while (1) {
	chill();
	}
}
