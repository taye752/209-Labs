/*
 * adc.c
 *
 * Created: 15/09/2026 2:52:33 pm
 *  Author: tomoa
 */ 

#include "common.h"
#include "adc.h"
#include <avr/io.h>

void adc_init(void) {
	ADMUX = (1 << REFS0) | (2 << MUX0);
	ADCSRA = (1 << ADEN) | (1 << ADPS2);
}

uint16_t adc_read(uint8_t channel) {
	ADMUX = (ADMUX & 0xF0) | channel;
	ADCSRA |= (1 << ADSC);
	while (ADCSRA & (1 << ADSC));
	return ADC;
}

uint16_t adc_convert_mv(uint16_t value) {
	uint32_t Vout = ((uint32_t)value*5000)/1023;
	return Vout;
}