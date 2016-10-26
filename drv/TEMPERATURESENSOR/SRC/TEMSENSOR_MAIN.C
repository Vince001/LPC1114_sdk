/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* File Name          : TemSensor_main.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 01/18/2010
* Description        : TemSensor_main program body.
*******************************************************************************
*******************************************************************************
* History:
* 01/18/2010		 : V1.0		   initial version
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */
#include "uart.h"
#include "type.h"
#include "i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define LM75_ADDR	0x90

#define TEMPERATURE_REG_ADDR	0x00000000 /* Temperature Register, Read-only */
#define CONFIGURATION_REG_ADDR	0x00000001 /* Configuration Register,Read-write,set operating modes */
#define TOS_SET_POINT			0x00000011 /* Tos Set Point Register,Read-write */
#define THYST_SET_POINT			0x00000010 /* Thyst Set Point Register,Read-write */


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
extern volatile uint32_t I2CCount;
extern volatile uint8_t I2CMasterBuffer[I2C_BUFSIZE];
extern volatile uint8_t I2CSlaveBuffer[I2C_BUFSIZE];
extern volatile uint32_t I2CMasterState;
extern volatile uint32_t I2CReadLength, I2CWriteLength;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/ 

/**
  * @brief   I2CReadTemSensor program
  * @param  DeviceAddr  - Hardware address
  * @param  RegAddr     - Register address
  * @param  ReadSize    - Read Size (Byte)
  * @retval None
  */
uint32_t I2CReadTemSensor(uint8_t DeviceAddr, uint8_t RegAddr, uint32_t ReadSize)
{
  /* Write SLA(W), address, SLA(R), and read one byte back. */
  I2CWriteLength = 2;
  I2CReadLength = ReadSize;
  I2CMasterBuffer[0] = DeviceAddr;
  I2CMasterBuffer[1] = RegAddr;		/* address */
  I2CMasterBuffer[2] = DeviceAddr | RD_BIT;

  if (!(I2CEngine()))
  {
    printf("\n\r -E- Read fail! \n\r");
	return ( FALSE );
  }

  return ( TRUE ); 
}


/**
  * @brief   Main program
  * @param  None
  * @retval None
  */
int TemSensor_main (void)
{
  uint32_t i;
  uint8_t ErrorCount = 0;

  SystemInit();

  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);
  
  printf("\n\r-- Basic I2C Temperature Sensor Project V1.0 --\n\r");
  printf("\n\r-- EM-LPC1100 --\n\r");
  printf("\n\r-- I2C Temperature Sensor test -- \n\r");  	

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  for ( i = 0; i < I2C_BUFSIZE; i++ )
  {
	I2CSlaveBuffer[i] = 0x00;
  }

  /* Read Temperature Register */
  if (I2CReadTemSensor(LM75_ADDR, TEMPERATURE_REG_ADDR, 2))
  {    
	printf("\n\r-I- Temperature Register value:0x%X\n\r", (I2CSlaveBuffer[0] << 8 | (I2CSlaveBuffer[1] & 0x80)));
  }
  else
  {
    ErrorCount++;  
  }

  /* Read Configuration Register */
  if (I2CReadTemSensor(LM75_ADDR, CONFIGURATION_REG_ADDR, 1))
  {
    printf("\n\r-I- Configuration Register value:0x%X\n\r", I2CSlaveBuffer[0]);  
  }
  else
  {
    ErrorCount++;  
  }
  
  /* Read Tos Set Point Register */  
  if (I2CReadTemSensor(LM75_ADDR, TOS_SET_POINT, 2))
  {
    printf("\n\r-I- Tos Set Point Register value:0x%X\n\r", (I2CSlaveBuffer[0] << 8 | (I2CSlaveBuffer[1] & 0x80)));
  }
  else
  {
    ErrorCount++;  
  }

  /* Read Thyst Set Point Register */
  if (I2CReadTemSensor(LM75_ADDR, THYST_SET_POINT, 2))
  {
    printf("\n\r-I- Thyst Set Point Register value:0x%X\n\r", (I2CSlaveBuffer[0] << 8 | (I2CSlaveBuffer[1] & 0x80)));
  }
  else
  {
    ErrorCount++;  
  }	  

  if (ErrorCount == 0) /* Test success! */
  {
    printf("\n\r I2C Temperature Sensor test success!\n\r");
  }
  else	/* Test fail. */ 
  {
    printf("\n\r I2C Temperature Sensor test fail!\n\r");
  }
  return 0;
}

/**
  * @}
  */ 

/**
  * @}
  */ 

/************* (C) COPYRIGHT 2010 Wuhan R&D Center, Embest *****END OF FILE****/
