#include "labs_en.h"

#if defined(LAB1)
#include "lab1.h"
#include <util/delay.h>
#include "usart.h"
#include "gp.h"

#define CLOCK_SPEED 12000000
#define BAUD 9600
#define MYUBRR CLOCK_SPEED/16/BAUD-1

#define MORSE_LUNG  3
#define MORSE_SCURT 1

/* Literele alfabetului in cod Morse */
char* morse_alphabet[] = {
    (char*)"13",    // a
    (char*)"3111",  // b
    (char*)"3131",  // c
    (char*)"311",   // d
    (char*)"1",     // e
    (char*)"1131",  // f
    (char*)"331",	// g
    (char*)"1111",	// h
    (char*)"11",	// i
    (char*)"1333",	// j
    (char*)"313",	// k
    (char*)"1311",	// l
    (char*)"33",	// m
    (char*)"31",	// n
    (char*)"333",	// o
    (char*)"1331",	// p
    (char*)"3313",	// q
    (char*)"131",	// r
    (char*)"111",	// s
    (char*)"3",	    // t
    (char*)"113",	// u
    (char*)"1113",	// v
    (char*)"133",	// w
    (char*)"3113",	// x
    (char*)"3133",	// y
    (char*)"3311"	// z
};

/* apelati functia pentru a obtine un ton lung/scurt,
 * folosind macro-urile MORSE_LUNG si MORSE_SCURT
 */
void speaker_morse(int tip)
{
    int delay = 1;
    int i;
    DDRD |= (1 << PD4);     // PD4 trebuie sa fie output

    for (i = 0; i < tip * 50 / delay; i++)
    {
        PIND = (1 << PD4);  // alternam starea iesirii
        _delay_ms(1);
    }
}

void setup_lab1(){
    USART0_init(MYUBRR);
    USART0_use_stdio();

    DDR_BTN_A &= ~(1 << BTN_A);  // setam pinul butonului ca input
    PORT_BTN_A |= (1 << BTN_A); // activam rez pull-up pentru buton
}


void loop_lab1(){
    if (!(PIN_BTN_A & (1 << BTN_A))) {  // verificam daca butonul este apasat
        USART0_print("Butonul 1 a fost apasat!\n");
    }

}

#endif // LAB1