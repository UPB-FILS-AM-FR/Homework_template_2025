#include "labs_en.h"

#if defined(LAB0)
#include "lab0.h"

#include <avr/io.h>
#include <util/delay.h>


void setup_lab0(){
    DDRD |= (1 << PD5);
}

void loop_lab0(){
    PORTD ^= (1 << PD5);
    _delay_ms(500);
}


#endif // LAB0