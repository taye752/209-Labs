/*
 * Lab4.c
 *
 * Created: 15/09/2026 1:39:45 pm
 * Author : tomoa
 */ 

#include "common.h"
#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include "UART.h"

int main(void) {
	adc_init();
	usart_init(UBRR);
	
	uint16_t adc0_samples[40];
	uint16_t adc1_samples[40];

	while (1) {
		
		for (int i = 0; i < 40; i++) {
			adc0_samples[i] = adc_read(0);   
			adc1_samples[i] = adc_read(1);   
			
		}
		
		uint16_t count = 0;
		uint16_t mv    = 0;
		uint8_t thousands = 0;
		uint8_t hundreds = 0;
		uint8_t tens     = 0;
		uint8_t ones     = 0;
		
		for (int i = 0; i < 40; i++) {
			uint16_t mv0 = adc_convert_mv(adc0_samples[i]);
			uint16_t mv1 = adc_convert_mv(adc1_samples[i]);

			usart_send_number(mv0);      
			usart_transmit(',');
			usart_transmit(' ');
			usart_send_number(mv1);      
			usart_transmit('\r');        
			usart_transmit('\n');
		}
		
		for (int i = 0; i < 40; i++) {
			adc0_samples[i] = adc_read(0);
			adc1_samples[i] = adc_read(1);
			_delay_ms(1000);   
		}
	}
}



