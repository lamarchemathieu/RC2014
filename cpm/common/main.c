#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bdos.h"

__sfr __at 0x01 IO1;
__sfr __at 0x03 IO3;

uint16_t _sp = 0xFFFF;

void putstr(char *str)
{
	while(*str)
	{
		putchar(*str);
		str++;
	}
}

void print_hex(uint8_t v)
{
	const char hex[] = "0123456789ABCDEF";
	putchar(hex[(v >> 4) & 0x0F]);
	putchar(hex[(v >> 0) & 0x0F]);
}

uint8_t hex_to_bin(char *h)
{
	uint8_t v = 0;
	if ((h[1] >= '0') && (h[1] <= '9'))
		v = h[1] - '0';
	if ((h[1] >= 'A') && (h[1] <= 'F'))
		v = h[1] - 'A' + 10;

	if ((h[0] >= '0') && (h[0] <= '9'))
		v |= (h[0] - '0') << 4;
	if ((h[0] >= 'A') && (h[0] <= 'F'))
		v |= (h[0] - 'A' + 10) << 4;
	return v;
}

void delay(uint32_t d)
{
	uint32_t i;
	for(i=0;i<d;i++)
	{
	__asm
	nop
	__endasm;
	}
}

int main(void)
{
	uint8_t r;
	uint16_t version;
	uint8_t cmd_len = *((char *)0x0080);
	char *cmd = (char *)0x0081;
	cmd[cmd_len] = '\0';

	putstr("Test code start !\r\n");

	version = bdos_version();
	putstr("Version = ");
	print_hex((version >> 8)&0x00FF);
	print_hex((version >> 0)&0x00FF);
	putstr("\r\n");

	putstr("SP = ");
	print_hex((_sp >> 8)&0x00FF);
	print_hex((_sp >> 0)&0x00FF);
	putstr("\r\n");


	putchar('[');
	putstr(cmd);
	putchar(']');
	putstr("\r\n");


	IO1 = hex_to_bin(&cmd[1]);
	IO3 = hex_to_bin(&cmd[3]);

	while(1)
	{
		r = bdos_direct_console_io(BDOS_DIRECT_CONSOLE_IO_INPUTSTATUS);
		if (r)
		{
			if ((r >= 0x20) &&  (r<= 0x7F))
			{
				bdos_direct_console_io(r);
			}
			else
			{
				print_hex(r);
			}

			if (r == 0x03)
			{
				putstr("\r\nCTRL-C\r\n");
				break;
			}

			if (r == 'q)')
				bdos_reset();

		}
		else
		{
			bdos_direct_console_io('.');
		}
		delay(10000);
		IO1 = IO3;
		IO3 = IO1;
	}
	return 0;
}
