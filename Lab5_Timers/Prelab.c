/*
 * CFile1.c
 *
 * Created: 22/09/2026 2:18:00 pm
 *  Author: tomoa
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	DDRB |= (1 << PB5);   // LED pin as output (confirm PB5 from schematic)
	while (1) {
		PORTB |=  (1 << PB5);   // LED on
		_delay_ms(375);         // 0.375 s
		PORTB &= ~(1 << PB5);   // LED off
		_delay_ms(125);         // 0.125 s
	}
}
