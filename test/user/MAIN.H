/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* File Name          : main.h
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 01/18/2010
* Description        : Header for main.c module.
*******************************************************************************
*******************************************************************************
* History:
* 01/18/2010		 : V1.0		   initial version
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

/* Local constants */
static const char menu[] =
"\n\r"
"\r *****************************************************************\r\n"
"\r *                                                               *\r\n"             
"\r *   Welcome to Embest                                           *\r\n"
"\r *                                                               *\r\n" 
"\r *   This is EM-LPC1100 test                                     *\r\n"
"\r *                                                               *\r\n"
"\r *   arm.embedinfo.com                                           *\r\n"
"\r *                                                               *\r\n"  
"\r *   0-LED test      1-BUTTON test      2-UART test              *\r\n"
"\r *                                                               *\r\n" 
"\r *   3-I2C EEPROM test    4-I2C Temperature Sensor test          *\r\n" 
"\r *                                                               *\r\n" 
"\r *****************************************************************\r\n"   
"\r\n Please input number from keyboard \r\n\n  ";

/* Exported functions ------------------------------------------------------- */
extern  int LED_main (void);
extern  int BUTTON_main (void);
extern  int UART_main (void);
extern  int EEPROM_main (void);
extern  int TemSensor_main (void);

#endif /* __MAIN_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****END OF FILE****/
