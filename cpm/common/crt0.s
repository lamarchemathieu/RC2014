	.module crt0
	.globl	_main
	.globl  __sp
	.area	_HEADER (ABS)

	.org 	0x0100
init:
	call	gsinit
	ld hl, #0x0000
	add hl, sp
	ld de, #__sp
	ld a, l
	ld (de), a
	inc de
	ld a, h
	ld (de), a
	call	_main
	ret

.area   _HOME
	.area	_CODE
	.area   _INITIALIZER
	.area   _GSINIT
	.area   _GSFINAL
	.area	_DATA
	.area   _INITIALIZED
	.area   _BSEG
	.area   _BSS
	.area   _HEAP

	.area   _GSINIT
gsinit::
	ld      bc, #l__INITIALIZER
	ld      a, b
	or      a, c
	jr      Z, gsinit_next
	ld      de, #s__INITIALIZED
	ld      hl, #s__INITIALIZER
	ldir
gsinit_next:
        .area   _GSFINAL
        ret