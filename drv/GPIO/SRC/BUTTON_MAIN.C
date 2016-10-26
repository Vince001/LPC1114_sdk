/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* File Name          : BUTTON_main.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 01/18/2010
* Description        : BUTTON_main program body.
*******************************************************************************
*******************************************************************************
* History:
* 01/18/2010		 : V1.0		   initial version
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */
#include "gpio.h"
#include "uart.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int BUTTON_main (void)
{
  SystemInit();

  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);	  

  printf("\n\r-- Basic GPIO Project V1.0 --\n\r");
  printf("\n\r-- EM-LPC1100 --\n\r");
  printf("\n\r-- GPIO port single edge trigger interrupt test --\n\r");
  printf("\n\r-- Please press 'BOOT' button on the board! --\n\r");

  GPIOInit();

  /* use port0_1 as input event, interrupt test. */
  GPIOSetDir( PORT0, 1, 0 );
  /* port0_1, single trigger, active high. */
  GPIOSetInterrupt( PORT0, 1, 0, 0, 1 );
  GPIOIntEnable( PORT0, 1 );

  while( 1 );
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****END OF FILE****/
