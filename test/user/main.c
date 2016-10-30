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

int main(void)
{
    uint32_t i = 0;
    SystemInit();

    /* NVIC is installed inside UARTInit file. */
    UARTInit(115200); 

	GPIOSetDir( 2, 0, 1 );
    GPIOSetDir( 2, 1, 1 );
	GPIOSetDir( 2, 2, 1 );
    GPIOSetDir( 2, 3, 1 );

	printf("Start begin sdk build \n");

	for(i=0;i<50000;i++)
	{
	    GPIOSetValue( 2, i%4, 0 );
        //GPIOSetValue( 2, 1, 0 );
		//GPIOSetValue( 2, 2, 0 );
        //GPIOSetValue( 2, 3, 0 );

		delay( 5000 );

		GPIOSetValue( 2, i%4, 1 );
        //GPIOSetValue( 2, 1, 1 );
		//GPIOSetValue( 2, 2, 1 );
        //GPIOSetValue( 2, 3, 1 );

		delay( 5000 );
	}

    return 0;
}

