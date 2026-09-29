/*
 * display.h
 *
 * Created: 29/09/2026 2:42:39 pm
 *  Author: tsha374
 */ 


#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

void init_display(void);
void seperate_and_load_characters(uint16_t number, uint8_t decimal_pos);
void send_next_character_to_display(void);



#endif /* DISPLAY_H_ */