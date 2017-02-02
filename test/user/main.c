#include <stdio.h>
#include "LPC11xx.h"                        /* LPC11xx definitions */
#include "uart.h"
#include "main.h"
#include "GPIO.H"

extern volatile uint32_t UARTCount;
extern volatile uint8_t UARTBuffer[BUFSIZE];

void delay(uint32_t cnt)
{
    uint32_t i = 0;
	uint32_t j = 0, k = 0;
	for(i=0;i<cnt;i++)
	    for(j=0;j<500;j++)
		    k++;
}

uint8_t UART_GetKey(void)
{
  while ( UARTCount == 0 );

  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
  //UARTSend( (uint8_t *)UARTBuffer, UARTCount );
  UARTCount = 0;
  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

  return UARTBuffer[0];
}

uint8_t UART_GetCmdAndData( uint8_t *buff, uint8_t *cnt )
{
    uint8_t i=0;
    printf("Input:");

  while ( UARTCount == 0 );

  LPC_UART->IER = IER_THRE | IER_RLS;			/* Disable RBR */
  UARTSend( (uint8_t *)UARTBuffer, UARTCount );
  *cnt = UARTCount;
  //printf("\n");
  for(i=0;i<UARTCount;i++) 
  {
      buff[i] = UARTBuffer[i];
      //printf("%x ",UARTBuffer[i]);
  }
  //printf("\n");
  UARTCount = 0;
  LPC_UART->IER = IER_THRE | IER_RLS | IER_RBR;	/* Re-enable RBR */

  return UARTBuffer[0];
}

void Led_blink(void)
{
    uint32_t i = 0;
    for(i=0;i<4;i++)
	{
	    GPIOSetValue( 2, i%4, 0 );
        //GPIOSetValue( 2, 1, 0 );
		//GPIOSetValue( 2, 2, 0 );
        //GPIOSetValue( 2, 3, 0 );

		delay( 1000 );

		GPIOSetValue( 2, i%4, 1 );
        //GPIOSetValue( 2, 1, 1 );
		//GPIOSetValue( 2, 2, 1 );
        //GPIOSetValue( 2, 3, 1 );

		delay( 1000 );
	}
}

void Led_off( void )
{
    GPIOSetDir( 2, 0, 0 );
    GPIOSetDir( 2, 1, 0 );
	GPIOSetDir( 2, 2, 0 );
    GPIOSetDir( 2, 3, 0 );
}

int main(void)
{
    uint32_t i = 0;
    //uint8_t cnt = 0;
    uint8_t cmd_index = 0;
    uint8_t buff[50];
    SystemInit();

    /* NVIC is installed inside UARTInit file. */
    UARTInit(115200); 

	GPIOSetDir( 2, 0, 1 );
    GPIOSetDir( 2, 1, 1 );
	GPIOSetDir( 2, 2, 1 );
    GPIOSetDir( 2, 3, 1 );

	printf("Start begin sdk build \r\n");
    UARTSend( "haha test\r\n", 12 );

    while(1)
    {
        buff[cmd_index] = UART_GetKey();
        if(buff[cmd_index] != ';') // the end
        {
            cmd_index++;
            if(cmd_index == BUFSIZE)
                cmd_index = 0;
                       
            continue;
        } 

        for(i=0;i<=cmd_index;i++)  // send back the cmd
            printf("%c",buff[i]);
        
        printf("\nGet cmd\n");      

        if(cmd_index < 2) // cmd too few
            continue;

        switch( buff[0] )
        {
            case 's':
                GPIOSetValue( 2, buff[2]-'0', 0 );  
            break;
            case 'c':
                GPIOSetValue( 2, buff[2]-'0', 1 );    
            break;
            default: break;                
        }
        for(i=0;i<UARTCount;i++) 
        {
            buff[i] = 0;
            UARTBuffer[i] = 0;
        }
        cmd_index = 0;
    }
}

