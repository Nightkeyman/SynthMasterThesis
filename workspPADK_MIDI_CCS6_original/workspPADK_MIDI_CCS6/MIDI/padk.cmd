/***************************************************************************
 *
 *
 *         **   **    **  ******  ********  ********  ********  **    **    
 *        **    **   **  **   ** ********  ********  ********  **    **
 *       **     *****   **   **    **     **        **        **    **
 *      **       **    ******     **     ****      **        ********
 *     **       **    **  **     **     **        **        **    **
 *    *******  **    **   **    **     ********  ********  **    **
 *   *******  **    **    **   **     ********  ********  **    **  
 *
 *            L Y R T E C H   S I G N A L   P R O C E S S I N G              
 *
 ***************************************************************************
 *                                                                          
 *  Project     : PADK
 *  File        : PADK.cmd
 *  Description	: PADK Generic Cmf file
 *
 *						Copyright (c) Lyrtech inc. 2005-06
 *
 ***************************************************************************/
/* 
-e int00
-c
-x

-stack 0x2000
-heap  0x2000
*/

/* CSL library path */
/*
-i "C:\CCStudio_v3.3\C6000\csl_C672x\dsp\lib"
*/
/* CSL intc library path */
/*
-i "C:\CCStudio_v3.3\C6000\csl_C672x_intc\dsp\lib"
*/

/* Include TI libraries */
/*
-lrts67plus.lib
-lcsl_C6727.lib
-lcsl_C672x_intc.lib
*/




/****************************************************************************/
/*  Specify the Memory Configuration                                        */
/****************************************************************************/

MEMORY
{
  ROM_VECS : origin = 0x00000000 length = 0x00001000
  ROM      : origin = 0x00001000 length = 0x000BF000
  VEC	   : origin = 0x10000000 length = 0x00001C00
  RAM      : origin = 0x10001C00 length = 0x0003E400
  SDRAM    : origin = 0x80000000 length = 0x08000000
  ASYNC2   : origin = 0x90000000 length = 0x00008000 
}

/****************************************************************************/
/*  Specify the Output Sections                                             */
/****************************************************************************/

SECTIONS
{
    .TIBoot:        load = RAM
    .text:   	    load = RAM
    .stack          load = RAM fill = 0xdeadbeef
    .cinit          load = RAM
    .cio            load = RAM
    .const          load = RAM 
    .data           load = RAM
    .switch         load = RAM
    .far            load = RAM
    .bss            load = RAM
    .sysmem         load = RAM
    .pinit			load = RAM
	INTERNAL_MEMORY load = RAM
	EXTERNAL_MEMORY load = SDRAM
}