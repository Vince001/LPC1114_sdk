/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* File Name          : LED_main.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 01/18/2010
* Description        : LED_main program body.
*******************************************************************************
*******************************************************************************
* History:
* 01/18/2010		 : V1.0		   initial version
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "timer16.h"
#include "clkconfig.h"
#include "gpio.h"
#include "uart.h"

extern volatile uint32_t timer16_0_counter;
extern volatile uint32_t timer16_1_counter;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TEST_TIMER_NUM		0		/* 0 or 1 for 16-bit timers only */
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int LED_main (void) {

  SystemInit();

  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);	  

  printf("\n\r-- Basic Blinky Project V1.0 --\n\r");
  printf("\n\r-- EM-LPC1100 --\n\r");
  printf("\n\r-- LED1 blinky test --\n\r"); 

  /* Config CLKOUT, mostly used for debugging. */
  CLKOUT_Setup( CLKOUTCLK_SRC_MAIN_CLK );
  LPC_IOCON->PIO0_1 &= ~0x07;	
  LPC_IOCON->PIO0_1 |= 0x01;		/* CLK OUT */

  /* Enable AHB clock to the GPIO domain. */
  LPC_SYSCON->SYSAHBCLKCTRL |= (1<<6);

  /* TEST_TIMER_NUM is either 0 or 1 for 16-bit timer 0 or 1. */
  init_timer16(TEST_TIMER_NUM, TIME_INTERVAL);
  enable_timer16(TEST_TIMER_NUM);

  /* Set port 2_0 to output */
  GPIOSetDir( 2, 0, 1 );

  while (1)                                /* Loop forever */
  {
#if TEST_TIMER_NUM
	/* I/O configuration and LED setting pending. */
	if ( (timer16_1_counter > 0) && (timer16_1_counter <= 200) )
	{
	  GPIOSetValue( 2, 0, 0 );
	}
	if ( (timer16_1_counter > 200) && (timer16_1_counter <= 400) )
	{
	  GPIOSetValue( 2, 0, 1 );
	}
	else if ( timer16_1_counter > 400 )
	{
	  timer16_1_counter = 0;
	}
#else
	/* I/O configuration and LED setting pending. */
	if ( (timer16_0_counter > 0) && (timer16_0_counter <= 200) )
	{
	  GPIOSetValue( 2, 0, 0 );
	}
	if ( (timer16_0_counter > 200) && (timer16_0_counter <= 400) )
	{
	  GPIOSetValue( 2, 0, 1 );
	}
	else if ( timer16_0_counter > 400 )
	{
	  timer16_0_counter = 0;
	}
#endif
  }
}
/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****END OF FILE****/
