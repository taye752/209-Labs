/*
 * display.c
 *
 * Created: 29/09/2026 12:09:49 pm
 *  Author: thoma
 */ 



#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"

static const uint8_t digits[10] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x6F  // 9
};

static volatile uint8_t count = 0;
static volatile uint8_t digit1_displayed = 0;


#define DS1_high PORTB |= (1<<PB0)
#define DS2_high PORTB |= (1<<PB1)
#define DS1_low PORTB &= ~(1<<PB0)
#define DS2_low PORTB &= ~(1<<PB1)


static void timer0_init(void) {
	TCCR0A = (1 << WGM01);              // CTC mode
	TCCR0B = (1 << CS02) | (1 << CS00); // prescaler 356
	OCR0A = 78;                         // ~10ms @ 2MHz
	TIMSK0 = (1 << OCIE0A);             // enable compare-match interrupt
}

void display_init(void) {
	DDRB |= (1<<DDB0 | 1<<DDB1 | 1<<DDB4);
	DDRC |= (1<<DDC0 | 1<<DDC1 | 1<<DDC2 | 1<<DDC3 | 1<<DDC4 | 1<<DDC5);
	
	DS1_low;
	DS2_low;
	timer0_init();
}

void display_increment_counter(void) {
	count++;
	if (count > 99) {
		count = 0;
	}
}

static void set_segments(uint8_t num) {
	uint8_t digit = digits[num];
	PORTC = (PORTC & 0xC0) | (digit & 0x3F);
	PORTB = (PORTB & 0xEF) | (((digit & 0x40) >> 2));
}

ISR(TIMER0_COMPA_vect) {
	uint8_t tens = count / 10;
	uint8_t ones = count % 10;

	if (digit1_displayed)
	{
		// Showed tens last -> show ones now
		PORTB |= (1 << PORTB0) | (1 << PORTB1); // 3. disable both
		set_segments(ones);                // 2/4. set segments for ones
		PORTB &= ~(1 << PORTB1);              // 5. enable Ds2
		digit1_displayed = 0;
	}
	else
	{
		// Showed ones last -> show tens now
		PORTB |= (1 << PORTB0) | (1 << PORTB1); // 3. disable both
		set_segments(tens);                // 2/4. set segments for tens
		PORTB &= ~(1 << PORTB0);              // 5. enable Ds1
		digit1_displayed = 1;
	}
}