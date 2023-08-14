#ifndef ADC_PRIVATE_H
#define ADC_PRIVATE_H

//ADC Multiplexer Selection Register
#define ADMUX  *((volatile u8 *)0x27)  

//ADC Control and Status Register
#define ADCSRA *((volatile u8 *)0x26) 

//The ADC Data Register
#define ADCH   *((volatile u8*)0x25)
#define ADCL   *((volatile u8*)0x24)
#define ADCR   *((volatile u16 *)0x24)

//Special FunctionIO Register
#define SFIOR  *((volatile u8 *)0x50)

//Reference Selection Bits
#define ADMUX_REFS0         6
#define ADMUX_REFS1         7

//ADC Left Adjust Result
#define ADMUX_ADLAR         5

//Analog Channel and Gain Selection Bits
#define ADMUX_MUX0          0
#define ADMUX_MUX1          1
#define ADMUX_MUX2          2
#define ADMUX_MUX3          3
#define ADMUX_MUX4          4

//ADC Enable
#define ADCSRA_ADEN         7

//ADC Start Conversion
#define ADCSRA_ADSC         6

//ADC Auto Trigger Enable
#define ADCSRA_ADATE        5 

//ADC Interrupt Flag
#define ADCSRA_ADIF         4 

//ADC Interrupt Enable
#define ADCSRA_ADIE         3 

//ADC Prescaler Select Bits
#define ADCSRA_ADPS0        0
#define ADCSRA_ADPS1        1
#define ADCSRA_ADPS2        2

//ADC Auto Trigger Source
#define SFIOR_ADT0          5
#define SFIOR_ADT1          6
#define SFIOR_ADT2          7

#endif // !ADC_PRIVATE_H
