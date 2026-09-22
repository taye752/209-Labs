/*
 * main.c
 *
 * Created: 22/09/2026 2:34:32 pm
 *  Author: tomoa
 */ 

#define F_CPU 2000000UL

#include "timer0.h"
#include "UART.h"

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

int main(void){
	
	timer0_init();
	usart_init(12);
	
	

	while(1){
	
	
	while (PIND & (1 << PD2));
	while (!(PIND & (1 << PD2)) );
	TCNT0 = 0;
	while (PIND & (1 << PD2));
	while (!(PIND & (1 << PD2)));
	uint8_t count = TCNT0;
	
	uint32_t period_us = (uint32_t)count * 128;
	uint32_t freq = 1000000UL / period_us;
	
	usart_send_number(freq);
	usart_transmit('\r');
	usart_transmit('\n'); 
	}
	
}
