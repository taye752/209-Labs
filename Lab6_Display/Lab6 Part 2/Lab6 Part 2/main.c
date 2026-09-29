/*
 * Lab6part2.c
 *
 * Created: 29/09/2026 12:33:41 pm
 * Author : thoma
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>
#include "display.h"

static volatile uint16_t counter = 0;

static void timer0_init(void)
{
	TCCR0A = (1 << WGM01);              // CTC mode
	TCCR0B = (1 << CS02); // prescaler 256
	OCR0A = 78;                          // ~10ms @ 2MHz
	TIMSK0 = (1 << OCIE0A);             // enable compare-match interrupt
}

ISR(TIMER0_COMPA_vect)
{
	send_next_character_to_display();
}

int main(void)
{
	init_display();
	timer0_init();
	sei();   // enable global interrupts

	seperate_and_load_characters(counter, 4); // 4 = no decimal point shown

	while (1)
	{
		_delay_ms(400);

		counter++;
		if (counter > 9999)
		{
			counter = 0;
		}

		seperate_and_load_characters(counter, 4);
	}
}