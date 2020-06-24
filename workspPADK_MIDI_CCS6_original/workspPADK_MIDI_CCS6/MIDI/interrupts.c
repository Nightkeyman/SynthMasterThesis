#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

interrupt void dmax_isr( void );
interrupt void nmi_isr( void );
interrupt void uart_isr( void );
interrupt void midi_isr( void );

#include "audioBufConst&ExtVar.h"
#include "uart_fifo.h"
#include "midi_fifo.h"

int SetupInterrupts()
{
	CSL_Status                    status;
    CSL_IntcGlobalEnableState     state;

    /*---------------------------------------------------------------*/
	/* INTC Module Initialization                                    */
	/*---------------------------------------------------------------*/
	status = CSL_intcInit( NULL );

    /*---------------------------------------------------------------*/
    /* Hook Transfert completion Notification from DMAX (INT11)      */
    /*---------------------------------------------------------------*/
    hIntc_uart = CSL_intcOpen( &intcObj_uart, CSL_INTC_EVENTID_DMAXEVTOUT4, NULL, &status );
	if( (hIntc_uart == NULL) || (status != CSL_SOK) )
	{
		return -1;
	}

    /*---------------------------------------------------------------*/
    /* Hook Transfert completion Notification from DMAX (INT13)      */
    /*---------------------------------------------------------------*/
    hIntc_midi = CSL_intcOpen( &intcObj_midi, CSL_INTC_EVENTID_DMAXEVTOUT6, NULL, &status );
	if( (hIntc_midi == NULL) || (status != CSL_SOK) )
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
    CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT6, (Uint32)midi_isr );
    CSL_intcHookIsr( CSL_INTC_EVENTID_NMI, (Uint32)nmi_isr );
    CSL_intcHookIsr( CSL_INTC_EVENTID_DMAXEVTOUT1, (Uint32)dmax_isr );

    // DMAXEVTOUT4 for UART
    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT4, &eventStat );
    CSL_intcEventEnable( CSL_INTC_EVENTID_DMAXEVTOUT6, &eventStat );
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

#define N 4096 // musi byc 2x tablica wystawiana na przerwanie (??)
int Buf_1[N];  // bufor pomocniczy do "obserwacji" danych wejsciowych
int Buf[N];  // bufor pomocniczy do "obserwacji" danych wyjœciowych
int k=0;
extern float waveform[N];
int wav_iterator = 0;

#define Fs 96000
#define M_PI 3.1416
extern int notes[128];
int generator_interator = 0;
int sound = 0;
double sound_double = 0;
// ################## DAC/ADC end ##################


// ################## UART RELATED VARs ############
#define UART_WAIT       1
#define UART_NO_WAIT    0
unsigned char uartdata[1];
extern unsigned char data_midi[1];
// ################## UART end #####################

interrupt void nmi_isr( void )
{
    while(1);
}

interrupt void midi_isr( void )
{
	static int toggle_midi = 0;
	MIDI_EnableLed1(toggle_midi ^= 1);
	MIDI_EnableLed2(!toggle_midi);
	if(MIDI_Read(data_midi, 1, 1) > 0) {
		if(data_midi[0] != 248) {
			MIDI_push(data_midi[0]);
			unsigned char status = (MIDI_pull(-2)>>4)&0x0F;
			if (status == 0x09) { // note on
				unsigned char note = MIDI_pull(-1)&0x7f;
				notes[note] = 1;
				MIDI_clear();
			} else if (status == 0x08) { // note off
				unsigned char note = MIDI_pull(-1)&0x7f;
				notes[note] = 0;
				MIDI_clear();
			}
		}
	}
	UART_Write(data_midi, 1, UART_NO_WAIT);
}

interrupt void uart_isr( void )
{
    static int toggle = 0;
	UART_EnableLed1( toggle ^= 1 );
    UART_EnableLed2( !toggle );
    UART_Read(uartdata, 1, UART_WAIT);
    UART_push(uartdata[0]);
    switch(UART_pull(0)){
    case 100:
    	if (UART_pull(7) == 101){
    		if (UART_pull(8) == UART_checksum()){
    			if (UART_pull(1) == 1){
    				UART_send(100, 1, 0,0,0,0,0);
    			} else if (UART_pull(1) == 2){
    				UART_send(100, 2, 0,0,0,0,0);
    			}
    		}
    	}
    	break;
    }
}

interrupt void dmax_isr( void )
{
	unsigned PP;
    volatile unsigned *GPTransferEntry;
    static int *pDac = (int *)dmaxDacBuffer[0];
    static int *pAdc = (int *)dmaxAdcBuffer[0];

	// Verify if a DAC transfer completed
	if( hDmaxDac->regs->DTCR0 & (1<<DAC_TCC) )
	{
		hDmaxDac->regs->DTCR0 = (1<<DAC_TCC);

		// Save the pointer of the audio buffer that has just been transmitted
	    GPTransferEntry  = (unsigned *)&hDmaxDac->regs->HiPriorityEventTable;
		GPTransferEntry += ((*(hDmaxDac->hiTableEventEntryPtr)>>8)&0x07F);
	    PP = GPTransferEntry[2] >> 31;
		pDac = (int *)dmaxDacBuffer[!PP];

		OBuf2.pBuf = pDac;
		//memcpy((int)waveform[wav_iterator], OBuf2.ptab[LEFT][CH_0], FRAME_SIZE);
		OBuf2.ptab[LEFT][CH_0] = (int)waveform[wav_iterator];
		OBuf2.ptab[RIGHT][CH_0] = (int)waveform[wav_iterator];

		wav_iterator = wav_iterator + 1;
		if(wav_iterator >= N)
			wav_iterator = 0;

        Buf[k] = OBuf2.ptab[LEFT][CH_0];  //Zapamiêtanie próbki wyjœciowej
        k++;							  //w buforze pomocniczym
        if (k == N) { k = 0; }
	}
}

