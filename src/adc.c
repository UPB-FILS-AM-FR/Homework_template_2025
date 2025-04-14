#include <stdio.h>
#include <avr/io.h>

#include "adc.h"

void adc_init(void)
{
    //(pg. 260) Set ADC prescaler to 128 (don't need higher precision for this project)
    
    //(pg. 258) Set ADC reference voltage to AVCC
    

    //(pg. 260) Enable ADC
    
}

uint16_t myAnalogRead(uint8_t channel)
{
    // Force input channel to be between 0 and 7 (as ADC pins are PC0-7)
    channel &= 0b00000111;

    // TODO [task0]:
    // 1. Clear the old channel value (if any, last 5 bits in ADMUX)
    ADMUX &= 0b11111000;

    // 2. Select the new channel in ADMUX
    

    // 3. Start single conversion
    

    // 4. Busy wait for conversion to complete
    

    // Return ADC value
    return (ADC);
}