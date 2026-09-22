/*
 * led.c
 *
 * Created: 22/09/2026 2:34:57 pm
 *  Author: tomoa
 */ 

#include "led.h"

#include <avr/io.h>

void led_toggle(){
	//TODO: LED toggle code
	PORTB ^= (1 << PB5);
}
