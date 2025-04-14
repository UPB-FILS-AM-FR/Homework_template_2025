#include <avr/io.h>
#include <util/delay.h>
#include "spi.h"
#include "gp.h"

void SPI_init(){

	/* TODO1: set MOSI and SCK output, all others input */
	

	/* TODO1: set SS PIN as output and set it on HIGH */
	

	/* TODO1: enable SPI, set it as Master, set clock rate at fosc/16 */

	
    
}

uint8_t SPI_exchange(uint8_t data){
	
	// TODO1: send a byte of data to the slave and return the response byte received from him in this transmission

	    // Start transmission
		

		// Wait for transmission complete
		
	
		// Return received data
		return SPDR;
}

