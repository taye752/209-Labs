/*
 * timer0.c
 *
 * Created: 22/09/2026 2:34:47 pm
 *  Author: tomoa
 */ 

#include "timer0.h"
#include "led.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void timer0_init(){
	//TODO: initialise and configure timer0 to count to 10ms
	
	TCCR0A = 0;
	TCCR0B = (1 << CS02);
	
}

uint8_t timer0_check_clear_compare(){
	if( TIFR0 & (1 << OCF0A )){ //TODO: check compare flag
		//TODO: clear compare flag.
		//Note: in datasheet this is done by writing 1 to the compare flag
		TIFR0 = (1 << OCF0A);

		return 1;
	}
	return 0;




}
