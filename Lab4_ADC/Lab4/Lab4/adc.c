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