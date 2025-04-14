#include "labs_en.h"

#ifdef LAB5

#include <avr/io.h>
#include <avr/interrupt.h>

#include <util/delay.h>

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "usart.h"
#include "lcd.h"
#include "pff.h"

#include "lab5.h"

#define PM_BAUD 9600



FATFS fs;					// sistemul de fisiere

/*---------------------------------------------------------------------------*/
/* Player audio                                                              */
/*---------------------------------------------------------------------------*/

/*
 * Four-Character Code - folosit pentru a indentifica formate de date
 */
#define FCC(c1, c2, c3, c4) \
	(((DWORD)(c4) << 24) + \
	 ((DWORD)(c3) << 16) + \
	 (( WORD)(c2) <<  8) + \
	 (( BYTE)(c1) <<  0))


uint8_t	buf[2][256];	// wave output buffers (double buffering)
const	 uint16_t	buf_size = 256;	// front and back buffer sizes
volatile uint8_t	buf_front = 0;	// front buffer index (current buffer used)
volatile uint8_t	buf_pos = 0;	// current buffer position
volatile uint8_t	buf_sync = 0;

#define BUF_FRONT	(buf[buf_front])
#define BUF_BACK	(buf[1 - buf_front])


ISR(TIMER0_COMPA_vect)
{
	OCR1B = BUF_FRONT[buf_pos++];

	// swap buffers when end is reached (end is 256 <=> overflow to 0)
	if(buf_pos == 0)
		buf_front = 1 - buf_front;
}

void timer0_start(void)
{
	// interrupt on compare A
	TIMSK0 |= (1 << OCIE0A);
	// CTC, top OCRA
	TCCR0B |= (0 << WGM02);
	TCCR0A |= (1 << WGM01) | (0 << WGM00);
	// prescaler 8
	TCCR0B |= (2 << CS00);
}

void timer0_stop(void)
{
	TCCR0B = 0;
	TCCR0A = 0;
	TIMSK0 = 0;
	OCR0A = 0;
	TCNT0 = 0;
}

void timer1_start(void)
{
	// 8-bit FastPWM
	TCCR1B |= (1 << WGM12);
	TCCR1A |= (1 << WGM10);
	// channel B inverted
	TCCR1A |= (1 << COM1B0) | (1 << COM1B1);
	// prescaler 1
	TCCR1B |= (1 << CS10);
}

void timer1_stop(void)
{
	TCCR1B = 0;
	TCCR1A = 0;
	OCR1B = 0;
	TCNT1 = 0;
}


void SD_log_data(int temp_c) {
    char buf[32];
    WORD bw;
    // Deschide fișierul în mod append
    // if (pf_open("log.csv") != FR_OK) {
    //     USART0_print("log.csv could not be opened");
    //     return;
    // }

    // // Du-te la finalul fișierului
    if (pf_lseek(0) != FR_OK) {
        USART0_print("lseek did not work");
        return;
    }
    pf_read(buf+1, 4, &bw);
    // Scrie linia în format CSV: "temp\n"
    buf[0] = (char) temp_c;
    char usart_string[30];
    if (pf_lseek(0) != FR_OK) {
        USART0_print("lseek did not work");
        return;
    }

    FRESULT res = pf_write(buf, 5, &bw);
    snprintf(usart_string, sizeof(usart_string), "Write: %s\r\n", res == FR_OK ? "Success" : "Failed");
    USART0_print(usart_string);
    res = pf_write(0, 0, &bw); // Finalizează scrierea
    snprintf(usart_string, sizeof(usart_string), "Finalize: %s\r\n", res == FR_OK ? "Success" : "Failed");
    USART0_print(usart_string);
    if (pf_lseek(0) != FR_OK) {
        USART0_print("lseek did not work");
        return;
    }
}



/*---------------------------------------------------------------------------*/
/* Ceas                                                                      */
/*---------------------------------------------------------------------------*/

volatile uint8_t hours = 0;
volatile uint8_t minutes = 0;
volatile uint8_t seconds = 0;


ISR(TIMER2_COMPA_vect)
{
	static uint16_t miliseconds = 0;

	if(++miliseconds != 1000)
		return;
	miliseconds = 0;

	if(++seconds == 60)
	{
		seconds = 0;

		if(++minutes == 60)
		{
			minutes = 0;

			if(++hours == 24)
				hours = 0;
		}
	}

	char buf[9];
	snprintf(buf, sizeof(buf), "%02d:%02d:%02d", hours, minutes, seconds);


	LCD_clear_bottom_line();
	LCD_printAt(0x40, buf);
}

void timer2_init(void)
{
	// set compare at each milisecond
	OCR2A = 124;
	// interrupt on compare A
	TIMSK2 |= (1 << OCIE2A);
	// CTC, top OCRA
	TCCR2A |= (1 << WGM21);
	// prescaler 128
	TCCR2B |= (1 << CS20) | (1 << CS22);
}


DIR directory;
FILINFO file;

void init_directory() {
	/* TODO3: open `/music`, using the `directory` structure declared above */

	/* TODO3: find the first file whose name doesn't start with a `_`; use the `directory` and `file` structures declared above */

	/* TODO3: display the name of the first file on the LCD */
}

void next_file() {
	/* TODO4: go to the next file whose name doesn't start with a `_`; after the last file, go back to the first file*/

	/* TODO4: display the file name on the LCD */
}

void buttons_init() {
	/* TODO4: configure button PB2 */

	/* TODO5: configure button PD6 */
}


void mounting(){

	for(;;){

		// mount filesystem
		LCD_printAt(0x00, "mounting...");

		int mount = pf_mount(&fs);
		
		char dbg[17];
		snprintf(dbg, sizeof(dbg), "res: %d", mount);
		LCD_clear_bottom_line();
		LCD_printAt(0x40, dbg);
		_delay_ms(200);

		
		snprintf(dbg, sizeof(dbg), "res: %d \n", mount);
		USART0_print(dbg);



		if(mount == FR_OK)
		{
			return;
		}
		// wait a while and retry
		_delay_ms(1000);
	}

}



void setup_lab5(){

	char path[200];

	buttons_init();
	LCD_init();
	

	USART0_init(CALC_USART_UBRR(PM_BAUD));
  	USART0_use_stdio();
	timer2_init();

	sei();

	mounting();

	LCD_clear_top_line();
	LCD_printAt(0x00, "mounted!");

}



void loop_lab5(){

	

	LCD_clear_top_line();
	LCD_printAt(0x00, "mounted!");
	_delay_ms(2000);
	
   /* TODO4: go to next file when button PB2 is pressed */

   /* TODO5: play current file on the speaker when button PD6 is pressed */

}

#endif // LAB5
