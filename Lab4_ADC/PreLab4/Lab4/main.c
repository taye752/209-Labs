/*
 * Lab4.c
 *
 * Created: 15/09/2026 1:39:45 pm
 * Author : tomoa
 */ 

#define F_CPU 2000000

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    /* Replace with your application code */
	
	DDRB |= (1 << PB5);
	DDRB &= ~(1 << PB7);
	DDRC = 0x00;
	DDRD = 0x00;
	
    while (1) 
    {
		if (!(PINB & (1 << PB7))) {
			PORTB |= (1 << PB5);
		} else {
			PORTB &= ~(1 << PB5);
		}
    }
}

