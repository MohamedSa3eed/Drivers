/************************************************************************/
/* Author       :  Mohamed Saeed                                        */
/* E-Mail       :  mohamed.sa3ed.faried@gmail.com                       */
/* Date         :  4  MAR 2023                                          */
/* Version      :  V01                                                  */
/************************************************************************/

#ifndef SPI_CONFIG_H
#define SPI_CONFIG_H

#define SPI1_SLAVE_PIN   GPIOA,PIN0

/*
*  Options :
*            1- SPI_MASTER
*            2- SPI_SLAVE
*/
#define SPI1_MASTER_OR_SLAVE SPI_MASTER

/*
*  Options :
*            1- SPI_BYTE 
*            2- SPI_WORD 
*/
#define SPI1_DATA_FRAME_FORMAT  SPI_BYTE 

/*
*  Options :
*            1- SPI_HARDWARE
*            2- SPI_SOFTWARE 
*/
#define SPI1_SLAVE_MANAGEMENT    SPI_SOFTWARE 

/*
*  Options :
*            1- SPI_LSB_FIRST
*            2- SPI_MSB_FIRST 
*/
#define SPI1_DATA_ORDER         SPI_MSB_FIRST 

/*
*  Options :
*            1- SPI_ENABLED
*            2- SPI_DISABLED
*/
#define SPI1_ENABLE         SPI_ENABLED

/*
*  Options :
*            1- SPI_FPCLK_2
*            2- SPI_FPCLK_4
*            3- SPI_FPCLK_8
*            4- SPI_FPCLK_16
*            5- SPI_FPCLK_32
*            6- SPI_FPCLK_64
*            7- SPI_FPCLK_128
*            8- SPI_FPCLK_256
*/
#define SPI1_FPCLK          SPI_FPCLK_8

/*
*  Options :
*            1- SPI_LOW
*            2- SPI_HIGH
*/
#define SPI1_CLK_POL        SPI_HIGH

/*
*  Options :
*            1- SPI_RECEIVE_FIRST
*            2- SPI_SEND_FIRST
*/
#define SPI1_CLK_PHA        SPI_SEND_FIRST

#endif // !SPI_CONFIG_H
