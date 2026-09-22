#ifndef TIMER0_H_
#define TIMER0_H_

#include <stdint.h>    // ? add this; needed for uint8_t
#include <stdbool.h>

void timer0_init();
uint8_t timer0_check_clear_compare();

#endif