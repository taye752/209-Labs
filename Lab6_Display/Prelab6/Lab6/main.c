/*
 * lab6prelab.c
 *
 * Created: 28/09/2026 10:25:53 pm
 * Author : thoma
 */ 
#define F_CPU 2000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define DS1_high PORTB |= (1<<PB0)
#define DS2_high PORTB |= (1<<PB1)
#define DS1_low PORTB &= ~(1<<PB0)
#define DS2_low PORTB &= ~(1<<PB1)

const uint8_t digits[10] = {
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

void set_output(uint8_t num) {
	uint8_t digit = digits[num];
	PORTC = (PORTC & 0xC0) | (digit & 0x3F);
	PORTB = (PORTB & 0xEF) | (((digit & 0x40) >> 2));
}


int main(void)
{
	
	DDRB &= ~(1<<DDB7);
	
	DDRB |= (1<<DDB0 | 1<<DDB1 | 1<<DDB4);
	DDRC |= (1<<DDC0 | 1<<DDC1 | 1<<DDC2 | 1<<DDC3 | 1<<DDC4 | 1<<DDC5);
	
	DS1_high;
	DS2_low;
	
	uint8_t count = 0;
	set_output(count);
	
    /* Replace with your application code */
    while (1) 
    {
		for (uint8_t i = 0; i <10; i++) {
			if (!(PINB & (1<<PINB7))) {
				count = 0;
				set_output(count);
			}
			_delay_ms(100);
		}
		
		
		count++;
		
		if (count > 9) {
			count = 0;
		}
		set_output(count);
    }
}