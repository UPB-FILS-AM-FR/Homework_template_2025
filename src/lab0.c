#include "labs_en.h"

#if defined(LAB0)
#include "lab0.h"

#include <avr/io.h>
#include <util/delay.h>

// #define TASK0
// #define TASK1
// #define TASK2
 #define TASK3

int color_state = 0;
int blink_state = 0;
int timer = 0;

void setup_lab0(){
#ifdef TASK0
    DDRD |= (1 << PD5);
    
#endif

#ifdef TASK1
    DDRD |= (1 << PD3);
#endif

#ifdef TASK2
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD3);
    DDRD |= (1 << PD6);

    PORTD &= ~(1 << PD5);
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD6);


    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2); // activam rez pull-up pentru PD2
#endif

#ifdef TASK3
    DDRD |= (1 << PD5);
    DDRD |= (1 << PD3);
    DDRD |= (1 << PD6);

    PORTD |= (1 << PD5);
    PORTD |= (1 << PD3);
    PORTD |= (1 << PD6);


    DDRD &= ~(1 << PD2);
    PORTD |= (1 << PD2); // activam rez pull-up pentru PD2

    DDRC &= ~(1 << PC3);
    PORTC |= (1 << PC3); // activam rez pull-up pentru PC3
#endif

}

void loop_lab0(){
#ifdef TASK0
    PORTD ^= (1 << PD5);
    _delay_ms(500);
#endif
#ifdef TASK1
    PORTD ^= (1 << PD3);
    _delay_ms(500);
#endif
#ifdef TASK2
    if (!(PIND & (1 << PD2))){ // verificam starea butonului
         
        PORTD &= ~(1 << PD6); // aprindem LED-ul daca butonul nu e apasat
        PORTD &= ~(1 << PD3); // stingem LED-ul daca butonul nu e apasat
        _delay_ms(50);
    }
    else{
        PORTD |= (1 << PD6); // stingem LED-ul daca butonul e apasat
        PORTD |= (1 << PD3); // stingem LED-ul daca butonul e apasat

    }
#endif
#ifdef TASK3

    if (!(PIND & (1<< PD2)))
    {
        color_state = (color_state + 1) % 3;
        _delay_ms(100);
        
    }
    if (!(PINC & (1 << PC3)))
    {
        blink_state = !blink_state;

    }
    switch (color_state)
    {    case 0:
        if (blink_state && timer == 0)
        {
            PORTD ^= (1 << PD5); // alternam starea LED-ului rosu
            
        }else{
            PORTD &= ~(1 << PD5); // stingem LED rosu
        }
        PORTD |= (1 << PD3);  // stingem LED verde
        PORTD |= (1 << PD6);  // stingem LED albastru
        break;
    case 1:
        if (blink_state && timer == 0)
        {
            PORTD ^= (1 << PD3); // alternam starea LED-ului verde
            _delay_ms(500);
        }else{
            PORTD &= ~(1 << PD3); // aprindem LED verde
        }
        PORTD |= (1 << PD5);  // stingem LED rosu
        PORTD |= (1 << PD6);  // stingem LED albastru
        break;
    case 2:
        if (blink_state && timer == 0)
        {
            PORTD ^= (1 << PD6); // alternam starea LED-ului albastru
            _delay_ms(500);
        }else{
            PORTD &= ~(1 << PD6); // stingem LED albastru
        }
        PORTD |= (1 << PD5);  // stingem LED rosu
        PORTD |= (1 << PD3);  // stingem LED verde
        break;
    default:
        break;
    }


timer+=10;
if (timer >= 500)
{
    timer = 0;

}
_delay_ms(10);
        
    
#endif

}

#endif // LAB0