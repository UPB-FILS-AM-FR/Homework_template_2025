#ifndef GP_H_
#define GP_H_

#include <avr/io.h>

//LCD
#define LCD_RS       PD7
#define LCD_RW       PD1

#define LCD_D4_SW1   PD3
#define LCD_D5       PD4
#define LCD_D6_SW2   PD5
#define LCD_D7_SW3   PD6

#define LCD_EN       PB0

//LED
#define LED_R_SW1    PD3
#define LED_G_SW2    PD5
#define LED_B_SW3    PD6

//BUZZER
#define BUZZER       PB1

//SPI SD 
#define SD_CS        PB2
#define SD_MOSI      PB3
#define SD_MISO      PB4
#define SD_SCK       PB5

//MISC
#define TEMP_SENSOR    PC0
#define BTN_A          PD2 //INT0
#define BTN_B          PC3
#define POTENTIOMETER  PC1

//I2C
#define I2C_SDA      PC4
#define I2C_SCL      PC5


// DDRn PORTn PINn
#define DDR_LCD_LED   DDRD
#define DDR_SD_SPI    DDRB
#define DDR_I2C_MISC  DDRC

#define PORT_LCD_LED   PORTD
#define PORT_SD_SPI    PORTB
#define PORT_I2C_MISC  PORTC


#define PIN_LCD_LED   PIND
#define PIN_SD_SPI    PINB
#define PIN_I2C_MISC  PINC

//BUZZER DDR & PORT
#define DDR_BUZZER     DDRB
#define PORT_BUZZER    PORTB

//LCD_EN DDR & PORT
#define DDR_LCD_EN     DDRB
#define PORT_LCD_EN    PORTB

//BTN_A DDR & PORT & PIN & INT & PCINT
#define DDR_BTN_A    DDRD
#define PORT_BTN_A   PORTD
#define PIN_BTN_A    PIND
#define INT_BTN_A    INT0
#define PCINT_BTN_A  PCINT18


//BTN_B DDR & PORT & PIN & PCINT
#define DDR_BTN_B    DDRC
#define PORT_BTN_B   PORTC
#define PIN_BTN_B    PINC
#define PCINT_BTN_B  PCINT11

#endif // GP_H_