#include "labs_en.h"
#include <avr/interrupt.h>

#include <util/delay.h>
#include "gp.h"

#ifdef LAB4

#include "adc.h"

void setup_lab4(){
    adc_init();

    // TODO [task1]: Use the previous defined function to read the ADC
    // value of the temperature sensor (PC0) and print it to the serial
    printf("ADC value: %d\n", myAnalogRead(0));
}

void loop_lab4(){

    printf("ADC value: %d\n", myAnalogRead(0));
    _delay_ms(2000);
}

#endif // LAB4
