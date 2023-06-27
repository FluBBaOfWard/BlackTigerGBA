#ifdef __arm__

#include "ARMZ80/ARMZ80.i"

	.global empty_IO_R
	.global empty_IO_W
	.global empty_R
	.global empty_W
	.global rom_W
	.global ramZ80W7
	.global memZ80R0
	.global memZ80R7

	.syntax unified
	.arm

	.section .text
	.align 2
;@----------------------------------------------------------------------------
empty_IO_R:					;@ Read bad IO address (error)
;@----------------------------------------------------------------------------
	mov r11,r11					;@ No$GBA debugg
	mov r0,#0x10
	bx lr
;@----------------------------------------------------------------------------
empty_IO_W:					;@ Write bad IO address (error)
;@----------------------------------------------------------------------------
	mov r11,r11					;@ No$GBA debugg
	mov r0,#0x18
	bx lr
;@----------------------------------------------------------------------------
empty_R:					;@ Read bad address (error)
;@----------------------------------------------------------------------------
	mov r11,r11					;@ No$GBA debugg
	mov r0,#0
	bx lr
;@----------------------------------------------------------------------------
empty_W:					;@ Write bad address (error)
;@----------------------------------------------------------------------------
	mov r11,r11					;@ No$GBA debugg
	mov r0,#0xBA
	bx lr
;@----------------------------------------------------------------------------
rom_W:						;@ Write ROM address (error)
;@----------------------------------------------------------------------------
	mov r11,r11					;@ No$GBA debugg
	mov r0,#0xB0
	bx lr
;@----------------------------------------------------------------------------

#ifdef NDS
	.section .itcm						;@ For the NDS ARM9
#elif GBA
	.section .iwram, "ax", %progbits	;@ For the GBA
#endif
	.align 2
;@----------------------------------------------------------------------------
ramZ80W7:					;@ Ram write ($E000-$FFFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+28]
	strb r0,[r1,addy]
	bx lr

;@----------------------------------------------------------------------------
memZ80R0:					;@ Mem read ($0000-$1FFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R1:					;@ Mem read ($2000-$3FFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+4]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R2:					;@ Mem read ($4000-$5FFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+8]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R3:					;@ Mem read ($6000-$7FFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+12]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R4:					;@ Mem read ($8000-$9FFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+16]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R5:					;@ Mem read ($A000-$BFFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+20]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R6:					;@ Mem read ($C000-$DFFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+24]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
memZ80R7:					;@ Mem read ($E000-$FFFF)
;@----------------------------------------------------------------------------
	ldr r1,[z80ptr,#z80MemTbl+28]
	ldrb r0,[r1,addy]
	bx lr
;@----------------------------------------------------------------------------
;@memZ80R:					;@ Mem read ($0000-$FFFF)
;@----------------------------------------------------------------------------
;@	add r2,z80ptr,#z80MemTbl
;@	ldr r1,[r2,r1,lsr#11]			;@ r1=addy & 0xe000
;@	ldrb r0,[r1,addy]
;@	bx lr
;@----------------------------------------------------------------------------
	.end
#endif // #ifdef __arm__
