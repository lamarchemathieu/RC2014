
#include "bdos.h"

void putchar(char c)
{
	bdos_console_output(c);
}

char getchar(void)
{
	return bdos_console_input();
}