#include "labs_en.h"

#ifdef LAB3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "timers.h"
#include "sound.h"
#include "usart.h"

#include <util/delay.h>
#include "gp.h"



/* Constants */
// #define PM_BAUD 28800

#define LED_ANIMATION_TIME 3000
enum LED_ANIMATION {
    GLOW_UP = 0,
    GLOW_DOWN,
};

#define LED_LEVELS 5

static void GPIO_init(void)
{

    //Just uncomment
    
    /* TODO Task 1 & 2: initialize LEDs */
    // DDR_LCD_LED |= (1 << LED_R_SW1) | (1 << LED_G_SW2)  | (1 << LED_B_SW3);

    /* TODO Task 1 & 2: initialize buttons */
    // DDR_BTN_A &= ~(1 << BTN_A);
    // PORT_BTN_A |= (1 << BTN_A);

    // DDR_BTN_B &= ~(1 << BTN_B);
    // PORT_BTN_B |= (1 << BTN_B);

    /* TODO Task 3: initialize buzzer */
    // DDR_BUZZER |= (1 << BUZZER);

}

/* Brightness level variables. */
volatile uint8_t red_level = 0;
volatile uint8_t blue_level = 0;

static void interrupts_init(void)
{
    /* TODO Task 2: activate PD2 button (BTN_A) interrupt on falling edge */
  

    /* TODO Task 2: activate PC3 (BTN_B) button intterupt */
    //////////////////////////////////////////////
 
}

/* TODO Task 2: implement BTN_A interrupt */

//////////////////////////////////////////
ISR(INT0_vect)
{
  
}

/* TODO Task 2: implement BTN_B interrupt */


//////////////////////////////////////////////////
ISR(PCINT1_vect)
{
   
}



#define TASK 3

uint32_t last_ping;
uint32_t last_note;
uint16_t note_idx;

uint8_t animation;


void setup_lab3(){

    GPIO_init();

  
    last_ping = 0;
    
    last_note = 0;
    
    note_idx = 0;

    animation = 0;



    /* Initialize timers */
    if (TASK == 2) {
        Timer0_init_ctc();

    } else {
        Timer0_init_pwm();

    }
    Timer1_init_systicks();

    Timer2_init_pwm();


    /* Initialize interrupts */
    interrupts_init();


    /* Activate global interrupts */
    sei();

    USART0_print("It's timer hammer!\n");

}
void loop_lab3(){

     /* Print alive message */
     if (SYSTICKS_PASSED(last_ping, 3000)) {
        last_ping = systicks;
        printf("Stayin' alive! [ticks=%ld]\n", systicks);
    }

    if (TASK == 1) {
        /* TODO Task 1: set animation mode */
        if (PIN_LCD_LED & (1 << LED_G_SW2)) {
            animation = GLOW_UP;
        } else {
            animation = GLOW_DOWN;
        }


        /* TODO Task 1: set duty cycle for green LED
         * - calculate the current position in the animation cycle from systicks
         * - map the value from [0, LED_ANIMATION_TIME] to [0, 255]
         */
        if (animation == GLOW_UP) {
            OCR2A = (systicks % LED_ANIMATION_TIME) * 255 / LED_ANIMATION_TIME;
        } else {
            OCR2A = (LED_ANIMATION_TIME - systicks % LED_ANIMATION_TIME) * 255 / LED_ANIMATION_TIME;
        }
    } else if (TASK == 2) {
        /* TODO Task 2: set duty cycle for blue and red LEDs */
        OCR0A = blue_level * 255 / (LED_LEVELS - 1);
        OCR1B = red_level * OCR1A / (LED_LEVELS - 1);
    } else {
        /* TODO Task 3: play the music */
        if (SYSTICKS_PASSED(last_note, durations[note_idx])) {
            last_note = systicks;

            note_idx = (note_idx + 1) % num_notes;

            OCR0A = (F_CPU / 256) / surprise_notes[note_idx];
        }
    }


}


#endif // LAB3