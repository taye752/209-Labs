/*
 * adc.h
 *
 * Created: 15/09/2026 2:52:13 pm
 *  Author: tomoa
 */ 


#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>
void adc_init(void);
uint16_t adc_read(uint8_t channel);
uint16_t adc_convert_mv(uint16_t value);


#endif /* ADC_H_ */