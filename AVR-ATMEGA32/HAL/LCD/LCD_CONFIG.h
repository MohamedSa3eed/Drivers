#ifndef LCD_CONFIG_H
#define LCD_CONFIG_H

/* options to use LCD 
 * 1- 8-PINS
 * 2- 4-PINS
 */
#define CONNECTION  _8_PINS

#define GPORT PORTB
#define RS PIN1 //GPORT
#define EN PIN2 //GPORT
#define RW PIN3 //GPORT
#define LCD_PORT PORTA



 //commands to write in LCD 

#define dispaly_on              0x0f
#define dispaly_off             0x08
#define return_to_0x00_in_DDRAM 0x02
#define clear                   0x01
#define entry_mode              0x06
#define entry_mode_shifting     0x07
#define entry_mode_reverse      0x04
#define entry_mode_rev_shifting 0x05



#endif
