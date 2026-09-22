/*
 * main.c
 *
 * Created: 22/09/2026 2:34:32 pm
 *  Author: tomoa
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "led.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	//TODO: set direction of LED port to OUTPUT
	DDRB |= (1 << PB5);
	
	timer0_init();
	sei();

	while(1){
	}
}
