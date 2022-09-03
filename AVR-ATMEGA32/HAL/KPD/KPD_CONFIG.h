#ifndef KPD_CONFIG_H
#define KPD_CONFIG_H

//port that KPD is connected to :
#define KPD_PORT PORTA

// flag for not pressing on KPD :
#define KPD_NOT_PRESSED 0xff

// KPD values configuration :
#define KPD_VALUES {  {1,2,3,4} , {5,6,7,8} , {9,10,11,12} , {13,14,15,16} }

// columns configuration :
#define KPD_COLUMN0_PIN PIN0
#define KPD_COLUMN1_PIN PIN1
#define KPD_COLUMN2_PIN PIN2
#define KPD_COLUMN3_PIN PIN3

//rows configuration :
#define KPD_ROW0_PIN PIN4
#define KPD_ROW1_PIN PIN5
#define KPD_ROW2_PIN PIN6
#define KPD_ROW3_PIN PIN7


#endif
