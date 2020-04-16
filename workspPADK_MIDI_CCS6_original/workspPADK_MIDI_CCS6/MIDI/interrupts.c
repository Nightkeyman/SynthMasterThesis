#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <stdint.h>
#include <math.h>

interrupt void dmax_isr( void );
interrupt void nmi_isr( void );
interrupt void uart_isr( void );
interrupt void midi_isr( void );

#include "audioBufConst&ExtVar.h"
#include "midi_fifo.h"
#include "sinustable.h"

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

#define N 4096
int Buf_1[N];  // bufor pomocniczy do "obserwacji" danych wejsciowych
int Buf[N];  // bufor pomocniczy do "obserwacji" danych wyjœciowych
int k=0;
extern double waveform[N/2];
int wav_iterator = 0;

#define Fs 96000
#define M_PI 3.1416
extern int notes[128];
int generator_iterator = 0;
float sound = 0;
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
    UART_Read(uartdata, 1, UART_NO_WAIT);
    UART_Write(uartdata, 1, UART_NO_WAIT);
}

interrupt void dmax_isr( void )
{
	unsigned PP;
    volatile unsigned *GPTransferEntry;
    static int *pDac = (int *)dmaxDacBuffer[0];
    static int *pAdc = (int *)dmaxAdcBuffer[0];

    sound = 0;
    if (notes[0] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[1] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[2] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[3] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[4] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[5] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[6] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[7] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[8] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[9] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[10] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[11] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[12] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[13] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[14] == 1) {
    	sound += notes[(int)round(generator_iterator*0)%N_LUT];
    }
    if (notes[15] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[16] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[17] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[18] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[19] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[20] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[21] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[22] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[23] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[24] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[25] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[26] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[27] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[28] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[29] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[30] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[31] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[32] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[33] == 1) {
    	sound += notes[(int)round(generator_iterator*1)%N_LUT];
    }
    if (notes[34] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[35] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[36] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[37] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[38] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[39] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[40] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[41] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[42] == 1) {
    	sound += notes[(int)round(generator_iterator*2)%N_LUT];
    }
    if (notes[43] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[44] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[45] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[46] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[47] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[48] == 1) {
    	sound += notes[(int)round(generator_iterator*3)%N_LUT];
    }
    if (notes[49] == 1) {
    	sound += notes[(int)round(generator_iterator*4)%N_LUT];
    }
    if (notes[50] == 1) {
    	sound += notes[(int)round(generator_iterator*4)%N_LUT];
    }
    if (notes[51] == 1) {
    	sound += notes[(int)round(generator_iterator*4)%N_LUT];
    }
    if (notes[52] == 1) {
    	sound += notes[(int)round(generator_iterator*4)%N_LUT];
    }
    if (notes[53] == 1) {
    	sound += notes[(int)round(generator_iterator*5)%N_LUT];
    }
    if (notes[54] == 1) {
    	sound += notes[(int)round(generator_iterator*5)%N_LUT];
    }
    if (notes[55] == 1) {
    	sound += notes[(int)round(generator_iterator*5)%N_LUT];
    }
    if (notes[56] == 1) {
    	sound += notes[(int)round(generator_iterator*6)%N_LUT];
    }
    if (notes[57] == 1) {
    	sound += notes[(int)round(generator_iterator*6)%N_LUT];
    }
    if (notes[58] == 1) {
    	sound += notes[(int)round(generator_iterator*6)%N_LUT];
    }
    if (notes[59] == 1) {
    	sound += notes[(int)round(generator_iterator*7)%N_LUT];
    }
    if (notes[60] == 1) {
    	sound += notes[(int)round(generator_iterator*7)%N_LUT];
    }
    if (notes[61] == 1) {
    	sound += notes[(int)round(generator_iterator*7)%N_LUT];
    }
    if (notes[62] == 1) {
    	sound += notes[(int)round(generator_iterator*8)%N_LUT];
    }
    if (notes[63] == 1) {
    	sound += notes[(int)round(generator_iterator*8)%N_LUT];
    }
    if (notes[64] == 1) {
    	sound += notes[(int)round(generator_iterator*9)%N_LUT];
    }
    if (notes[65] == 1) {
    	sound += notes[(int)round(generator_iterator*9)%N_LUT];
    }
    if (notes[66] == 1) {
    	sound += notes[(int)round(generator_iterator*10)%N_LUT];
    }
    if (notes[67] == 1) {
    	sound += notes[(int)round(generator_iterator*10)%N_LUT];
    }
    if (notes[68] == 1) {
    	sound += notes[(int)round(generator_iterator*11)%N_LUT];
    }
    if (notes[69] == 1) {
    	sound += notes[(int)round(generator_iterator*12)%N_LUT];
    }
    if (notes[70] == 1) {
    	sound += notes[(int)round(generator_iterator*12)%N_LUT];
    }
    if (notes[71] == 1) {
    	sound += notes[(int)round(generator_iterator*13)%N_LUT];
    }
    if (notes[72] == 1) {
    	sound += notes[(int)round(generator_iterator*14)%N_LUT];
    }
    if (notes[73] == 1) {
    	sound += notes[(int)round(generator_iterator*15)%N_LUT];
    }
    if (notes[74] == 1) {
    	sound += notes[(int)round(generator_iterator*16)%N_LUT];
    }
    if (notes[75] == 1) {
    	sound += notes[(int)round(generator_iterator*16)%N_LUT];
    }
    if (notes[76] == 1) {
    	sound += notes[(int)round(generator_iterator*17)%N_LUT];
    }
    if (notes[77] == 1) {
    	sound += notes[(int)round(generator_iterator*18)%N_LUT];
    }
    if (notes[78] == 1) {
    	sound += notes[(int)round(generator_iterator*20)%N_LUT];
    }
    if (notes[79] == 1) {
    	sound += notes[(int)round(generator_iterator*21)%N_LUT];
    }
    if (notes[80] == 1) {
    	sound += notes[(int)round(generator_iterator*22)%N_LUT];
    }
    if (notes[81] == 1) {
    	sound += notes[(int)round(generator_iterator*23)%N_LUT];
    }
    if (notes[82] == 1) {
    	sound += notes[(int)round(generator_iterator*25)%N_LUT];
    }
    if (notes[83] == 1) {
    	sound += notes[(int)round(generator_iterator*26)%N_LUT];
    }
    if (notes[84] == 1) {
    	sound += notes[(int)round(generator_iterator*28)%N_LUT];
    }
    if (notes[85] == 1) {
    	sound += notes[(int)round(generator_iterator*29)%N_LUT];
    }
    if (notes[86] == 1) {
    	sound += notes[(int)round(generator_iterator*31)%N_LUT];
    }
    if (notes[87] == 1) {
    	sound += notes[(int)round(generator_iterator*33)%N_LUT];
    }
    if (notes[88] == 1) {
    	sound += notes[(int)round(generator_iterator*35)%N_LUT];
    }
    if (notes[89] == 1) {
    	sound += notes[(int)round(generator_iterator*37)%N_LUT];
    }
    if (notes[90] == 1) {
    	sound += notes[(int)round(generator_iterator*39)%N_LUT];
    }
    if (notes[91] == 1) {
    	sound += notes[(int)round(generator_iterator*42)%N_LUT];
    }
    if (notes[92] == 1) {
    	sound += notes[(int)round(generator_iterator*44)%N_LUT];
    }
    if (notes[93] == 1) {
    	sound += notes[(int)round(generator_iterator*47)%N_LUT];
    }
    if (notes[94] == 1) {
    	sound += notes[(int)round(generator_iterator*49)%N_LUT];
    }
    if (notes[95] == 1) {
    	sound += notes[(int)round(generator_iterator*52)%N_LUT];
    }
    if (notes[96] == 1) {
    	sound += notes[(int)round(generator_iterator*55)%N_LUT];
    }
    if (notes[97] == 1) {
    	sound += notes[(int)round(generator_iterator*59)%N_LUT];
    }
    if (notes[98] == 1) {
    	sound += notes[(int)round(generator_iterator*62)%N_LUT];
    }
    if (notes[99] == 1) {
    	sound += notes[(int)round(generator_iterator*66)%N_LUT];
    }
    if (notes[100] == 1) {
    	sound += notes[(int)round(generator_iterator*70)%N_LUT];
    }
    if (notes[101] == 1) {
    	sound += notes[(int)round(generator_iterator*74)%N_LUT];
    }
    if (notes[102] == 1) {
    	sound += notes[(int)round(generator_iterator*78)%N_LUT];
    }
    if (notes[103] == 1) {
    	sound += notes[(int)round(generator_iterator*83)%N_LUT];
    }
    if (notes[104] == 1) {
    	sound += notes[(int)round(generator_iterator*88)%N_LUT];
    }
    if (notes[105] == 1) {
    	sound += notes[(int)round(generator_iterator*93)%N_LUT];
    }
    if (notes[106] == 1) {
    	sound += notes[(int)round(generator_iterator*99)%N_LUT];
    }
    if (notes[107] == 1) {
    	sound += notes[(int)round(generator_iterator*105)%N_LUT];
    }
    if (notes[108] == 1) {
    	sound += notes[(int)round(generator_iterator*111)%N_LUT];
    }
    if (notes[109] == 1) {
    	sound += notes[(int)round(generator_iterator*117)%N_LUT];
    }
    if (notes[110] == 1) {
    	sound += notes[(int)round(generator_iterator*124)%N_LUT];
    }
    if (notes[111] == 1) {
    	sound += notes[(int)round(generator_iterator*132)%N_LUT];
    }
    if (notes[112] == 1) {
    	sound += notes[(int)round(generator_iterator*140)%N_LUT];
    }
    if (notes[113] == 1) {
    	sound += notes[(int)round(generator_iterator*148)%N_LUT];
    }
    if (notes[114] == 1) {
    	sound += notes[(int)round(generator_iterator*157)%N_LUT];
    }
    if (notes[115] == 1) {
    	sound += notes[(int)round(generator_iterator*166)%N_LUT];
    }
    if (notes[116] == 1) {
    	sound += notes[(int)round(generator_iterator*176)%N_LUT];
    }
    if (notes[117] == 1) {
    	sound += notes[(int)round(generator_iterator*186)%N_LUT];
    }
    if (notes[118] == 1) {
    	sound += notes[(int)round(generator_iterator*198)%N_LUT];
    }
    if (notes[119] == 1) {
    	sound += notes[(int)round(generator_iterator*209)%N_LUT];
    }
    if (notes[120] == 1) {
    	sound += notes[(int)round(generator_iterator*222)%N_LUT];
    }
    if (notes[121] == 1) {
    	sound += notes[(int)round(generator_iterator*235)%N_LUT];
    }
    if (notes[122] == 1) {
    	sound += notes[(int)round(generator_iterator*249)%N_LUT];
    }
    if (notes[123] == 1) {
    	sound += notes[(int)round(generator_iterator*264)%N_LUT];
    }
    if (notes[124] == 1) {
    	sound += notes[(int)round(generator_iterator*279)%N_LUT];
    }
    if (notes[125] == 1) {
    	sound += notes[(int)round(generator_iterator*296)%N_LUT];
    }
    if (notes[126] == 1) {
    	sound += notes[(int)round(generator_iterator*314)%N_LUT];
    }
    if (notes[127] == 1) {
    	sound += notes[(int)round(generator_iterator*332)%N_LUT];
    }




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
		OBuf2.ptab[LEFT][CH_0] = (int)(sound*100000.0);
		OBuf2.ptab[RIGHT][CH_0] = (int)(sound*100000.0);
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

		generator_iterator++;
		if (generator_iterator >= 96000)
			generator_iterator = 0;
		wav_iterator++;
		if(wav_iterator >= N/2)
			wav_iterator = 0;

        Buf[k] = OBuf2.ptab[LEFT][CH_0];  //Zapamiêtanie próbki wyjœciowej
        k++;							  //w buforze pomocniczym
        if (k == N) { k = 0; }
	}
}

