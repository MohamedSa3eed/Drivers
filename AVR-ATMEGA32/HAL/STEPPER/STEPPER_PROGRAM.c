#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_INTERFACE.h"
#include "STEPPER_INTERFACE.h"
#include "STEPPER_CONFIG.h"
#include </usr/avr/include/avr/delay.h>

void STEPPER_Init()
{
	DIO_SetPinDiriction(STEPPER_BLUE_PIN,OUTPUT);
	DIO_SetPinDiriction(STEPPER_PINK_PIN,OUTPUT);
	DIO_SetPinDiriction(STEPPER_YELLOW_PIN,OUTPUT);
	DIO_SetPinDiriction(STEPPER_ORANGE_PIN,OUTPUT);
}

void STEPPER_FullStep()
{
	u8 Locale_value = DIO_GetPortValue(STEPPER_PORT);
	switch (Locale_value) {
		case 0b00000000 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
                case 0b00000001:
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
                        break;
		case 0b00000010:
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
                case 0b00000100 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
		case 0b00001000 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;

	}
}
void STEPPER_HalfStep()
{
	u8 Locale_value = DIO_GetPortValue(STEPPER_PORT);
        switch (Locale_value) {
		case 0b00000000 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
                case 0b00001001:
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
                        break;
		case 0b00000001:
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
                case 0b00000011 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
		case 0b00000010 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, HIGH);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
                case 0b00000110 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, LOW);
			_delay_ms(5);
			break;
                case 0b00000100 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, HIGH);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
                case 0b00001100 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, LOW);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
                case 0b00001000 :
			DIO_SetPinValue(STEPPER_BLUE_PIN, HIGH);
			DIO_SetPinValue(STEPPER_PINK_PIN, LOW);
			DIO_SetPinValue(STEPPER_YELLOW_PIN, LOW);
			DIO_SetPinValue(STEPPER_ORANGE_PIN, HIGH);
			_delay_ms(5);
			break;
	}
}
