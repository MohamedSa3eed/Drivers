#ifndef EXTI_CONFIG_H
#define EXTI_CONFIG_H





/* options to INT0_SENSE
 * 1- LOW_LEVEL
 * 2- ON_CHANGE
 * 3- FALLING_EDGE
 * 4- RISING_EDGE  
 */ 
#define INT0_SENSE FALLING_EDGE 

 //options for INT0_STATE 
 //1- ENABLED
 //2- DISABLED
#define INT0_STATE DISABLED


/* options to INT1_SENSE
 * 1- LOW_LEVEL
 * 2- ON_CHANGE
 * 3- FALLING_EDGE
 * 4- RISING_EDGE  
 */ 
#define INT1_SENSE FALLING_EDGE 

 //options for INT1_STATE 
 //1- ENABLED
 //2- DISABLED
#define INT1_STATE DISABLED


/* options to INT1_SENSE
 * 1- FALLING_EDGE
 * 2- RISING_EDGE  
 */ 
#define INT2_SENSE FALLING_EDGE 

 //options for INT2_STATE 
 //1- ENABLED
 //2- DISABLED
#define INT2_STATE DISABLED

#endif
