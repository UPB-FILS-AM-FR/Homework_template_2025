#include "labs_en.h"

#include <stdio.h>
#include <string.h>

#include "usart.h"
#define PM_BAUD 9600

#ifdef LAB0
#include "lab0.h"
#endif

#ifdef LAB1
#include "lab1.h"
#endif

#ifdef LAB2
#include "lab2.h"
#endif

#ifdef LAB3
#include "lab3.h"
#endif

#ifdef LAB4
#include "lab4.h"
#endif

#ifdef LAB5#include "labs_en.h"
#include "lab5.h"
#endif

#ifdef LAB6
#include "lab6.h"
#endif


int main(void){

#ifndef LAB0
USART0_init(CALC_USART_UBRR(PM_BAUD));
USART0_use_stdio();


USART0_print("dbg");
#endif

//CALL LABn SETUPS 
#ifdef LAB0
    setup_lab0(); 
#elif defined LAB1
    setup_lab1();
#elif defined LAB2
    setup_lab2();
#elif defined LAB3
    setup_lab3();
#elif defined LAB4
    setup_lab4();
#elif defined LAB5
    setup_lab5();
#elif defined LAB6
    setup_lab6();
#endif 

USART0_print("dbg2");


//CALL LABn LOOPS   
   for(;;){
        #ifdef LAB0
                loop_lab0();
        #elif defined LAB1
                loop_lab1();
        #elif defined LAB2
                loop_lab2();
        #elif defined LAB3
                loop_lab3();
        #elif defined LAB4
                loop_lab4();
        #elif defined LAB5
                loop_lab5();
        #elif defined LAB6
                loop_lab6();
        #endif

    }
}