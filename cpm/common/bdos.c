
#include "bdos.h"



/*
void bdos_console_output(uint8_t c) __naked
{
	(void)c;
	__asm
	ld	hl, #2+0
	add	hl, sp
	ld e,(hl)
	ld c, #0x02
	call #0x0005
	ret
	__endasm;
}*/

uint8_t bdos_console_output_c;

void bdos_console_output(uint8_t c)
{
	bdos_console_output_c = c;
	__asm
	.globl _bdos_console_output_c
	ld hl, #_bdos_console_output_c
	ld e,(hl)
	ld c, #0x02
	call #0x0005
	ret
	__endasm;
}

uint8_t bdos_console_input(void)  __naked
{
	__asm
	ld c, #0x01
	call #0x0005
	ld l,a
	ret
	__endasm;
}


uint8_t bdos_reset(void)  __naked
{
	__asm
	ld c, #0x00
	call #0x0005
	ret
	__endasm;
}


uint16_t bdos_version(void)  __naked
{
	__asm
	ld c, #0x0c
	call #0x0005
	ret
	__endasm;
}


#define BDOS_DIRECT_CONSOLE_IO_INPUTSTATUS 0xFF

uint8_t bdos_direct_console_io(uint8_t c) __naked
{
	(void)c;
	__asm
	ld	hl, #2+0
	add	hl, sp
	ld e,(hl)
	ld c, #0x06
	call #0x0005
	ld l,a
	ret
	__endasm;
}
