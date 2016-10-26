/******************** (C) COPYRIGHT 2010 Embest Info&Tech Co.,LTD. ************
* File Name          : EEPROM_main.c
* Author             : Wuhan R&D Center, Embest
* Date First Issued  : 01/18/2010
* Description        : EEPROM_main program body.
*******************************************************************************
*******************************************************************************
* History:
* 01/18/2010		 : V1.0		   initial version
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC11xx.h"			/* LPC11xx Peripheral Registers */
#include "type.h"
#include "uart.h"
#include "i2c.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
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
  * @brief   Main program
  * @param  None
  * @retval None
  */
int EEPROM_main (void)
{
  uint32_t i;
  uint8_t ErrorCount = 0;	

  SystemInit();

  /* NVIC is installed inside UARTInit file. */
  UARTInit(115200);
  
  printf("\n\r-- Basic I2C EEPROM Project V1.0 --\n\r");
  printf("\n\r-- EM-LPC1100 --\n\r");
  printf("\n\r-- I2C Read/Write EEPROM test -- \n\r");  

  if ( I2CInit( (uint32_t)I2CMASTER ) == FALSE )	/* initialize I2c */
  {
	while ( 1 );				/* Fatal error */
  }

  /* In order to start the I2CEngine, the all the parameters 
  must be set in advance, including I2CWriteLength, I2CReadLength,
  I2CCmd, and the I2cMasterBuffer which contains the stream
  command/data to the I2c slave device. 
  (1) If it's a I2C write only, the number of bytes to be written is 
  I2CWriteLength, I2CReadLength is zero, the content will be filled 
  in the I2CMasterBuffer. 
  (2) If it's a I2C read only, the number of bytes to be read is 
  I2CReadLength, I2CWriteLength is 0, the read value will be filled 
  in the I2CMasterBuffer. 
  (3) If it's a I2C Write/Read with repeated start, specify the 
  I2CWriteLength, fill the content of bytes to be written in 
  I2CMasterBuffer, specify the I2CReadLength, after the repeated 
  start and the device address with RD bit set, the content of the 
  reading will be filled in I2CMasterBuffer index at 
  I2CMasterBuffer[I2CWriteLength+2]. 
  
  e.g. Start, DevAddr(W), WRByte1...WRByteN, Repeated-Start, DevAddr(R), 
  RDByte1...RDByteN Stop. The content of the reading will be filled 
  after (I2CWriteLength + two devaddr) bytes. */

  /* Write SLA(W), address and one data byte */
  I2CWriteLength = 6;
  I2CReadLength = 0;
  I2CMasterBuffer[0] = PCF8594_ADDR;
  I2CMasterBuffer[1] = 0x00;		/* address */
  I2CMasterBuffer[2] = 0x00;		/* address */
  I2CMasterBuffer[3] = 0xAA;		/* Data0 */
  I2CMasterBuffer[4] = 0x12;		/* Data1 */
  I2CMasterBuffer[5] = 0x34;		/* Data2 */
  I2CEngine();
  for ( i = 0; i < 0x20000; i++ );	/* Delay after write */

  for ( i = 0; i < I2C_BUFSIZE; i++ )
  {
	I2CSlaveBuffer[i] = 0x00;
  }
  /* Write SLA(W), address, SLA(R), and read one byte back. */
  I2CWriteLength = 3;
  I2CReadLength = 3;
  I2CMasterBuffer[0] = PCF8594_ADDR;
  I2CMasterBuffer[1] = 0x00;		/* address */
  I2CMasterBuffer[2] = 0x00;		/* address */
  I2CMasterBuffer[3] = PCF8594_ADDR | RD_BIT;
  I2CEngine();

  /* Compare and check the data send and received */
  for (i = 0; i < 3; i++ )
  {
    if (I2CSlaveBuffer[i] != I2CMasterBuffer[i + 3])
	{
	  ErrorCount++;
	}	  
  }
	
  if (ErrorCount == 3) /* Test fail. */
  {
    printf("\n\r I2C EEPROM test failed! \n\r");
  }
  else	 /* Test success! */
  {
    printf("\n\r I2C EEPROM test success!\n\r");
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
