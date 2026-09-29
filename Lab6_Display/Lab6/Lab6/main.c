/*
 * Lab6.c
 *
 * Created: 29/09/2026 12:57:40 am
 * Author : thoma
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "display.h"





int main(void)
{
	
	DDRB &= ~(1<<DDB7);
	display_init();
	sei();
	
    /* Replace with your application code */
    while (1) {
		_delay_ms(1000);
		display_increment_counter();
	}
}