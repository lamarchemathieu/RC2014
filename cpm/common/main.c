#include <stdint.h>
#include <stdio.h>

__sfr __at 0x81 UART_DATA ;
__sfr __at 0x80 UART_REG ;
__sfr __at 0x03 IN0 ;
__sfr __at 0x03 OUT0 ;
__sfr __at 0x01 IN1 ;
__sfr __at 0x01 OUT1 ;


void putchar(char c)
{
	
	while(1)
	{
		UART_REG = 0;
		if ((UART_REG & 0x04) != 0)
			break;
	}	

	UART_DATA = c;
}

char getchar(void)
{
	while(1)
	{
		UART_REG = 0;
		if ((UART_REG & 0x02) != 0)
			break;
	}
   return UART_DATA;
}

uint8_t cnt;

int main(void)
{
	uint32_t i;
	uint8_t bit;
	cnt = 0;

	UART_REG = 0x00;
	UART_REG = 0x18;

	UART_REG = 0x04;
	UART_REG = 0xC4;

	UART_REG = 0x01;
	UART_REG = 0x18;

	UART_REG = 0x03;
	UART_REG = 0xE1;

	UART_REG = 0x05;
	UART_REG = 0xEA;

	putchar('\r');
	putchar('\n');
	putchar('\r');
	putchar('\n');
	putchar('\r');
	putchar('\n');

	puts("Demo RC2014 module I/O\r\n");

	while(1)
	{
		
		for(bit=0;bit<8;bit++)
		{
			if (IN0 & (1<<(7-bit)))
			{
				putchar('1');
			}
			else
			{
				putchar('0');
			}
		}
		for(bit=0;bit<8;bit++)
		{
			if (IN1 & (1<<(7-bit)))
			{
				putchar('1');
			}
			else
			{
				putchar('0');
			}
		}
		putchar('\r');
		putchar('\n');

		for(i=0;i<10000;i++)
		{
			OUT1 = ~cnt;
			OUT0 = cnt;
		}

		cnt++;
	}
}
