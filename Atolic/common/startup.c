/*
 * File:    startup.c
 * Purpose: Generic Kinetis startup code
 *
 * Notes:
 */

#include "common.h"

extern unsigned long _sdata, _edata, _sidata, _sbss, _ebss;
extern unsigned long _estack;

/********************************************************************/
void
common_startup(void)
{
    /* Declare a counter we'll use in all of the copy loops */
    uint32 n;

    /* Addresses for VECTOR_TABLE and VECTOR_RAM come from the linker file */
    extern uint32 __VECTOR_TABLE[];
    extern uint32 __VECTOR_RAM[];

    /* Copy the vector table to RAM */
    if (__VECTOR_RAM != __VECTOR_TABLE)
    {
        for (n = 0; n < 0x104; n++)
            __VECTOR_RAM[n] = __VECTOR_TABLE[n];
    }
    /* Point the VTOR to the new copy of the vector table */
    write_vtor((uint32)__VECTOR_RAM);

    /* Data and BSS variables */
	unsigned long *srcdata, *dstdata, *sbss;

	/* Set up the stack pointer */
	asm("ldr r0,=_estack\n\t");
	asm("mov sp, r0");

	srcdata = &_sidata;
	dstdata = &_sdata;
	sbss = &_sbss;

	/* Copy data */
	while (dstdata != &_edata) {
	*(dstdata++) = *(srcdata++);
	}

	/* Clear BSS */
	while (sbss != &_ebss) {
	*(sbss++) = '\0';
	}
}
/********************************************************************/
