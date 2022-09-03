#ifndef STEPPER_INTERFACE_H
#define STEPPER_INTERFACE_H

/* this fuction initialize the pins connected to stepper motor */
void STEPPER_Init();

/*  this functoin makes the stepper do the primary steps */
void STEPPER_FullStep(void);


/*  this functoin makes the stepper do the primary & secondary steps */
void STEPPER_HalfStep(void);

#endif
