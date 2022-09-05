#ifndef EXTI_PRIVATE_h
#define EXTI_PRIVATE_h

#define GICR            *((volatile u8 *)0x5B)
#define GICR_INT0       6
#define GICR_INT1       7
#define GICR_INT2       5

#define GIFR            *((volatile u8 *)0x5A)
#define GIFR_INTF0      6
#define GIFR_INTF1      7
#define GIFR_INTF2      5

#define MCUCR           *((volatile u8 *)0x55)
#define ISC00           0
#define ISC01           1
#define ISC10           2
#define ISC11           3

#define MCUCSR          *((volatile u8 *)0x54)
#define ISC2            6

// INT_SENSE values
#define   LOW_LEVEL    1 
#define   ON_CHANGE    2 
#define   FALLING_EDGE 3 
#define   RISING_EDGE  4

// INT_STATE
#define	ENABLED        1 
#define	DISABLED       2 


#endif
