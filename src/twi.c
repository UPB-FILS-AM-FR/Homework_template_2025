/*
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * PLEASE MODIFY THIS FILE * * * * * * * * * * * * * *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 */

#include "twi.h"
#include "gp.h"

void twi_init(void) {
	/* Enable I2C power pin (PC4, PC5 ) */
	// TODO 0: set PC4 as output with high level
        

	/* Reset I2C control register */

	
    /* Set I2C clock frequency */
    
    // TODO 0: set bitrate in TWSR register (check twi.h to find prescaler value)
        
}

void twi_start(void) {
    /* Enable I2C communication and clear interrupt flag */
    // TODO 0: send START condition (corresponding bit in TWCR)
	

	/* Mandatory: wait for START condition to be sent */
	
}

void twi_write(uint8_t data) {
    // Send a byte of data (TWCR + TWDR)
    TWDR = data;
    /* Enable I2C communication and clear interrupt flag */
    // TODO 1: set acknowledge bit (corresponding bit in TWCR)
	
	
    // TODO 1: wait for transfer to complete (TWINT flag)
       
}

void twi_read_ack(uint8_t *data) {
    /* Enable I2C communication and clear interrupt flag */
    // TODO 1: set acknowledge bit (corresponding bit in TWCR)
   

    // TODO 1: wait for transfer to complete (TWINT flag)
       
}

void twi_read_nack(uint8_t *data) {
    // TODO 1: read a byte of data with ACK disabled 
	// (same as above, but don't send acknowledge)
       
}

void twi_stop(void) {
    /* Enable I2C communication and clear interrupt flag */
    // TODO 0: send STOP condition (corresponding bit in TWCR)
    
}

void twi_discover(void) {
    /* Search for I2C slaves */
    // HINT: An acknowledged SLA_R should enable a flag in TWSR. Check the datasheet (pg 275)!
    
		// TODO 2: write address (as seen in OCW hints)
            
        
        // TODO 2: check TWSR (see util/twi.h documentation for constants!)
        
}
