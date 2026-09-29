/*
 * display.c
 *
 * Created: 29/09/2026 2:42:21 pm
 *  Author: tsha374
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"

// Array containing which segments to turn on to display a number between 0 to 9
// bit order: dp g f e d c b a
const uint8_t seg_pattern[10] = {
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

// 4 characters to be displayed on Ds1 to Ds4
static volatile uint8_t disp_characters[4] = {0,0,0,0};

// The current digit (e.g. the 1's, the 10's) of the 4-digit number we're displaying
static volatile uint8_t disp_position = 0;

// ---- Pin definitions ----
#define SH_DS_pin 4
#define SH_CP_pin 3
#define SH_ST_pin 5
#define DS1_pin   4
#define DS2_pin   5
#define DS3_pin   6
#define DS4_pin   7

void init_display(void)
{
	// SH_DS, SH_CP, SH_ST on PORTC as outputs
	DDRC |= (1 << SH_CP_pin) | (1 << SH_DS_pin) | (1 << SH_ST_pin);

	// Ds1-Ds4 on PORTD as outputs
	DDRD |= (1 << DS1_pin) | (1 << DS2_pin) | (1 << DS3_pin) | (1 << DS4_pin);

	// Shift register control lines start low
	PORTC &= ~((1 << SH_CP_pin) | (1 << SH_ST_pin));

	// All digits disabled initially (logic 1 = off)
	PORTD |= (1 << DS1_pin) | (1 << DS2_pin) | (1 << DS3_pin) | (1 << DS4_pin);
}

// Populate the array 'disp_characters[]' by separating the four digits of 'number'
// and then looking up the segment pattern from 'seg_pattern[]'
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos)
{
	uint8_t ones, tens, hundreds, thousands;

	// 1. Separate each digit from 'number'
	ones      = number % 10;
	tens      = (number / 10) % 10;
	hundreds  = (number / 100) % 10;
	thousands = (number / 1000) % 10;

	// 2. Lookup pattern required to display each digit from 'seg_pattern[]'
	//    and store this pattern in appropriate position of 'disp_characters[]'
	disp_characters[0] = seg_pattern[thousands];
	disp_characters[1] = seg_pattern[hundreds];
	disp_characters[2] = seg_pattern[tens];
	disp_characters[3] = seg_pattern[ones];

	// 3. Add decimal point at position 'decimal_pos' (bit 7 = dp)
	if (decimal_pos < 4)
	{
		disp_characters[decimal_pos] |= 0x80;
	}
}

void send_next_character_to_display(void)
{
	// 1. Load the digit to send
	uint8_t pattern = disp_characters[disp_position];

	// 2. Send this bit pattern to the shift register
	PORTC &= ~(1 << SH_CP_pin);

	for (int8_t i = 7; i >= 0; i--)
	{
		if (pattern & (1 << i)) {
			PORTC |= (1 << SH_DS_pin);
		} else {
			PORTC &= ~(1 << SH_DS_pin);
		}
		
		
		PORTC |= (1 << SH_CP_pin);
		PORTC &= ~(1 << SH_CP_pin);
	}

	// 3. Disable all digits BEFORE latching the new pattern
	PORTD |= (1 << DS1_pin) | (1 << DS2_pin) | (1 << DS3_pin) | (1 << DS4_pin);

	// 4. Latch the output by toggling SH_ST
	PORTC |= (1 << SH_ST_pin);
	PORTC &= ~(1 << SH_ST_pin);

	// 5. Enable the correct digit
	switch (disp_position)
	{
		case 0: PORTD &= ~(1 << DS1_pin); break;
		case 1: PORTD &= ~(1 << DS2_pin); break;
		case 2: PORTD &= ~(1 << DS3_pin); break;
		case 3: PORTD &= ~(1 << DS4_pin); break;
	}

	// 6. Increment disp_position, wrap after 3
	disp_position++;
	if (disp_position > 3)
	{
		disp_position = 0;
	}
}