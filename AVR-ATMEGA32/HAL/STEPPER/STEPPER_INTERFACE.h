#ifndef STEPPER_INTERFACE_H
#define STEPPER_INTERFACE_H
/**
 * @brief Initializes the pins connected to the stepper motor.
 *
 * @return Error state of the stepper motor initialization.
 */
ES_t STEPPER_Init(void);

/**
 * @brief Makes the stepper motor perform full steps.
 *
 * @return Error state of the full step operation.
 */
ES_t STEPPER_FullStep(void);

/**
 * @brief Makes the stepper motor perform both primary and secondary steps.
 *
 * @return Error state of the half step operation.
 */
ES_t STEPPER_HalfStep(void);

#endif
