#ifndef STEPPER_INTERFACE_H
#define STEPPER_INTERFACE_H

/* this fuction initialize the pins connected to stepper motor */
ES_t STEPPER_Init(void);

/*  this functoin makes the stepper do the primary steps */
ES_t STEPPER_FullStep(void);


/*  this functoin makes the stepper do the primary & secondary steps */
ES_t STEPPER_HalfStep(void);

#endif
