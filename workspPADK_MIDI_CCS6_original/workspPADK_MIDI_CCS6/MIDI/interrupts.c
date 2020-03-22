#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <stdint.h>


interrupt void dmax_isr( void );
interrupt void nmi_isr( void );
interrupt void uart_isr( void );

#include "audioBufConst&ExtVar.h"

int SetupInterrupts()
{
	CSL_Status                    status;
    CSL_IntcGlobalEnableState     state;

    /*---------------------------------------------------------------*/
	/* INTC Module Initialization                                    */
	/*---------------------------------------------------------------*/
	status = CSL_intcInit( NULL );

    /*---------------------------------------------------------------*/
    /* Hook Transfert completion Notification from DMAX (INT11)       */
    /*---------------------------------------------------------------*/
    hIntc_uart = CSL_intcOpen( &intcObj_uart, CSL_INTC_EVENTID_DMAXEVTOUT4, NULL, &status );
	if( (hIntc_uart == NULL) || (status != CSL_SOK) )
	{
		return -1;
	}

    /*---------------------------------------------------------------*/
    /* Hook Transfert completion Notification from DMAX (INT8)       */
    /*---------------------------------------------------------------*/
    hIntc = CSL_intcOpen( &intcObj, CSL_INTC_EVENTID_DMAXEVTOUT1, NULL, &status );
	if( (hIntc == NULL) || (status != CSL_SOK) )
	{
		return -1;
	}

    CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT4, (Uint32)uart_isr );
    CSL_intcHookIsr( CSL_INTC_EVENTID_NMI, (Uint32)nmi_isr );
    CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT1, (Uint32)dmax_isr );

    // DMAXEVTOUT4 for UART
    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT4, &eventStat );
    CSL_intcEventEnable( CSL_INTC_EVENTID_NMI, &eventStat );
    // DMAXEVTOUT1 for DAC/ADC
    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT1, &eventStat );

    CSL_intcGlobalEnable( &state );

	return 0;
}

// ################## DAC/ADC RELATED VARs #########
#define LEFT		(0)
#define RIGHT		(1)
#define LEFT_o		(1) /* odwrotne oznaczenie kanalów */
#define RIGHT_o		(0)
#define CH_0		(0)
#define CH_1		(1)
#define CH_2		(2)
#define CH_3		(3)

int we[STEREO][NUM_CHANNEL];
int wy[STEREO][NUM_CHANNEL];
//int wl1, wp1, wl2, wp2, wl3, wp3, wl4, wp4;

#define N 4098
int Buf_1[N];  // bufor pomocniczy do "obserwacji" danych wejsciowych
int Buf[N];  // bufor pomocniczy do "obserwacji" danych wyjœciowych
int k=0;

#define Fs 96000
#define M_PI 3.1416
extern int notes[128];
int generator_interator = 0;
// ################## DAC/ADC end ##################


// ################## UART RELATED VARs ############
#define UART_WAIT       1
#define UART_NO_WAIT    0
unsigned char uartdata[1];
// ################## UART end #####################

interrupt void nmi_isr( void )
{
    while(1);
}

interrupt void uart_isr( void )
{
    static int toggle = 0;
	UART_EnableLed1( toggle ^= 1 );
    UART_EnableLed2( !toggle );
    UART_Read(  uartdata, 1, UART_NO_WAIT );
    UART_Write( uartdata, 1, UART_NO_WAIT);
}

interrupt void dmax_isr( void )
{
	unsigned PP;
    volatile unsigned *GPTransferEntry;
    static int *pDac = (int *)dmaxDacBuffer[0];
    static int *pAdc = (int *)dmaxAdcBuffer[0];
    int sound = 0;
    int i;
    //sound = generator_interator - Fs/200;
    sound = (int)(1000.0*sin((double)(generator_interator)*2.0*M_PI*(1*100.0)*(1.0/Fs)));
    //sound = sound*100000;
    /*for(i = 0; i < 128; i++) {
    	if (notes[i] == 1){
    		sound += (int)(1000.0*sin((double)(generator_interator)*2.0*M_PI*(i*100.0)*(1.0/Fs)));
    	}
	}*/
    generator_interator++;
    if (generator_interator >= Fs/100-1)
    	generator_interator = 0;
	// Verify if a DAC transfer completed
	if( hDmaxDac->regs->DTCR0 & (1<<DAC_TCC) )
	{
		hDmaxDac->regs->DTCR0 = (1<<DAC_TCC);

		// Save the pointer of the audio buffer that has just been transmitted
	    GPTransferEntry  = (unsigned *)&hDmaxDac->regs->HiPriorityEventTable;
		GPTransferEntry += ((*(hDmaxDac->hiTableEventEntryPtr)>>8)&0x07F);
	    PP = GPTransferEntry[2] >> 31;     	
		pDac = (int *)dmaxDacBuffer[!PP]; 
	}
	// Verify if a ADC transfer completed
	if( hDmaxAdc->regs->DTCR0 & (1<<ADC_TCC) )
	{
		hDmaxAdc->regs->DTCR0 = (1<<ADC_TCC);

		// Save the pointer of the audio buffer that has just been filled
		GPTransferEntry  = (unsigned *)&hDmaxAdc->regs->HiPriorityEventTable;
		GPTransferEntry += ((*(hDmaxAdc->hiTableEventEntryPtr)>>8)&0x07F);
	    PP = GPTransferEntry[2] >> 31;     	
		pAdc = (int *)dmaxAdcBuffer[!PP];
		IBuf2.pBuf = pAdc;
		we[LEFT][CH_0] = IBuf2.ptab[LEFT][CH_0];
		we[RIGHT][CH_0] = IBuf2.ptab[RIGHT][CH_0];
		we[LEFT][CH_1] = IBuf2.ptab[LEFT][CH_1];
		we[RIGHT][CH_1] = IBuf2.ptab[RIGHT][CH_1];
		we[LEFT][CH_2] = IBuf2.ptab[LEFT][CH_2];
		we[RIGHT][CH_2] = IBuf2.ptab[RIGHT][CH_2];
		we[LEFT][CH_3] = IBuf2.ptab[LEFT][CH_3];
		we[RIGHT][CH_3] = IBuf2.ptab[RIGHT][CH_3];


		wy[LEFT][CH_0] = gain * we[LEFT][CH_0];
		wy[RIGHT][CH_0] = gain * we[RIGHT][CH_0];
		wy[LEFT][CH_1] = gain * we[LEFT][CH_1];
		wy[RIGHT][CH_1] = gain * we[RIGHT][CH_1];
		wy[LEFT][CH_2] = gain * we[LEFT][CH_2];
		wy[RIGHT][CH_2] = gain * we[RIGHT][CH_2];
		wy[LEFT][CH_3] = gain * we[LEFT][CH_3];
		wy[RIGHT][CH_3] = gain * we[RIGHT][CH_3];

		
		OBuf2.pBuf = pDac;
		OBuf2.ptab[LEFT][CH_0] = sound;
		OBuf2.ptab[RIGHT][CH_0] = wy[RIGHT][CH_0];
		OBuf2.ptab[LEFT][CH_1] = wy[LEFT][CH_1];
		OBuf2.ptab[RIGHT][CH_1] = wy[RIGHT][CH_1];
		OBuf2.ptab[LEFT][CH_2] = wy[LEFT][CH_2];
		OBuf2.ptab[RIGHT][CH_2] = wy[RIGHT][CH_2];
		OBuf2.ptab[LEFT][CH_3] = wy[LEFT][CH_3];
		OBuf2.ptab[RIGHT][CH_3] = wy[RIGHT][CH_3];

//		OBuf2.ptab[LEFT_o][CH_0] = wy[LEFT][CH_0];  // zamiana kanalów: Left <-> Right
//		OBuf2.ptab[RIGHT_o][CH_0] = wy[RIGHT][CH_0];
//		OBuf2.ptab[LEFT_o][CH_1] = wy[LEFT][CH_1];
//		OBuf2.ptab[RIGHT_o][CH_1] = wy[RIGHT][CH_1];
//		OBuf2.ptab[LEFT_o][CH_2] = wy[LEFT][CH_2];
//		OBuf2.ptab[RIGHT_o][CH_2] = wy[RIGHT][CH_2];
//		OBuf2.ptab[LEFT_o][CH_3] = wy[LEFT][CH_3];
//		OBuf2.ptab[RIGHT_o][CH_3] = wy[RIGHT][CH_3];

        Buf[k] = IBuf2.ptab[RIGHT][CH_3];  //Zapamiêtanie próbki wyjœciowej
        k++;							  //w buforze pomocniczym
        if (k == N) { k = 0; }
	}
}

