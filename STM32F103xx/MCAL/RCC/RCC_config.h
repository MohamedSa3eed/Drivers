/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4 FEB 2023                                           */
/* Version      :  V01                                                  */
/************************************************************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* Clock Type : 
Options : 
          1-RCC_HSE_CRYSTAL
          2-RCC_HSE_RC     
          3-RCC_HSI        
          4-RCC_PLL        
*/ 
#define RCC_CLOCK_TYPE   RCC_HSI

#if  RCC_CLOCK_TYPE == RCC_PLL 
// If PLL is selected as Clock type 
/* PLL Options :
          1-RCC_PLL_HSI_DIV_2  
          2-RCC_PLL_HSE_DIV_2
          3-RCC_PLL_HSE 
*/
#define RCC_PLL_INPUT    RCC_PLL_HSE_DIV_2

// Options : 2 to 16 
#define RCC_PLL_MUL_VAL  4

#endif // !RCC_PLL

#endif // !RCC_CONFIG_H
