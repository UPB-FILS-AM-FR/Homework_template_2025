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

#ifdef LAB5
#include "lab5.h"
#endif

#ifdef LAB6
#include "lab6.h"
#endif


int main(void){

USART0_init(CALC_USART_UBRR(PM_BAUD));
USART0_use_stdio();


USART0_print("dbg");

//CALL LABn SETUPS    
#ifdef LAB3
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

        #ifdef LAB3
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