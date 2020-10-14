#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

interrupt void dmax_isr( void );
interrupt void nmi_isr( void );
interrupt void uart_isr( void );
interrupt void midi_isr( void );

#include "PADK.h"
#include "audioBufConst&ExtVar.h"
#include "uart_fifo.h"
#include "midi_fifo.h"
#include "additive.h"

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

// ################## MIDI DEFINES #########
#define MIDI_TONE_RANGE 128
#define MIDI_A_SOUND_FREQ 440
#define MIDI_A_SOUND_NUM 69
#define MIDI_TONE_RANGE 128
#define MIDI_POLY_MAX 12

// ################## OTHER DEFINES #########
#define N 1024
#define OVERLAP 128
#define Fs 48000
#define M_PI 3.1416
#define UART_WAIT       1
#define UART_NO_WAIT    0
// ################## END OF DEFINES #########

int we[STEREO][NUM_CHANNEL];
int wy[STEREO][NUM_CHANNEL];
//int wl1, wp1, wl2, wp2, wl3, wp3, wl4, wp4;

int Buf_1[N];  // bufor pomocniczy do "obserwacji" danych wejsciowych
int Buf[N];  // bufor pomocniczy do "obserwacji" danych wyjœciowych
int k = 0;
extern int waveform0[N];
extern int waveform1[N];
int plot[2*N];
extern volatile int whichwaveform;
#define OVERLAP 128

int wav_iterator = 0;
volatile unsigned PP;
volatile unsigned sem_dac = 0;

#define Fs 48000
#define M_PI 3.1416
int generator_interator = 0;
int sound = 0;
int licz = 0;
double sound_double = 0;

// ADSR
#define ADSR_ATT_TIME 0.001
#define ADSR_DEC_TIME 0.001
#define ADSR_SUS_LEVEL 0.001
#define ADSR_REL_TIME 0.001
extern float attack_rate;
extern float decay_rate;
extern float sustain_level;
extern float release_rate;
extern float attack_level;
extern int adsr_state[MIDI_POLY_MAX];
extern int pressedkeys;
extern float adsr[MIDI_POLY_MAX];

// SYNTHESIS METHODS
extern enum methodtype{subtractive, additive, fm, fm_bell, flute, violin};
extern enum methodtype method;

extern enum waveformtype{square, triangle, sawtooth};
extern enum waveformtype waveformSet;
extern enum filtertype{lowpass, highpass, bandpass, bandstop};
extern enum filtertype filterSet;
extern int sub_lowfreq;
extern int sub_highfreq;

// FM GLOBALS
extern int fm_modfreq;
extern int fm_modamp;
extern double bell_adsr_coefficient;

// WOODWIND GLOBALS
extern int flag_flute;

// ADDITIVE GLOBALS
extern float add_knobAmp[HAMMOND_KNOBS];

// VIOLIN GLOBALS
extern int flag_violin;
extern double vibrato_gain;
extern double vibrato_freq;

// ################## DAC/ADC end ##################

// ################## UART RELATED VARs ############
unsigned char uartdata[1];
// ################## UART end #####################

// ################## MIDI RELATED VARs ############
extern int pressedkeys;
extern float freqs[MIDI_POLY_MAX];
int sem_new_note = 0; // 0 - 128
extern unsigned char data_midi[1];
// ################## MIDI end #####################

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
				float freq_wav = MIDI_A_SOUND_FREQ*pow(1.059463, note - MIDI_A_SOUND_NUM);
				int i = 0, keyOccupFlag = 0;
				for (i = 0; i < MIDI_POLY_MAX; i++) {
					if (freqs[i] >= freq_wav-0.5 && freqs[i] <= freq_wav+0.5) {
						adsr_state[i] = 1;
						adsr[i] = 0;
						keyOccupFlag = 1;
						break;
					}
				}
				if(keyOccupFlag == 0) {
					for (i = 0; i < MIDI_POLY_MAX; i++) {
						if (freqs[i] == 0) {
							freqs[i] = freq_wav;
							flag_flute = 1;
							flag_violin = 1;
							adsr_state[i] = 1;
							break;
						}
					}
					pressedkeys++;
				}
				MIDI_clear();
			} else if (status == 0x08) { // note off
				unsigned char note = MIDI_pull(-1)&0x7f;
				float freq_wav = MIDI_A_SOUND_FREQ*pow(1.059463,note - MIDI_A_SOUND_NUM);
				int i = 0;
				for (i = 0; i< MIDI_POLY_MAX; i++) {
					if (freqs[i] >= freq_wav-0.5 && freqs[i] <= freq_wav+0.5) {
						adsr_state[i] = 4;
						break;
					}
				}
				MIDI_clear();
			}
		}
	}
}

interrupt void uart_isr( void )
{
    static int toggle = 0;
	UART_EnableLed1( toggle ^= 1 );
    UART_EnableLed2( !toggle );
    UART_Read(uartdata, 1, UART_WAIT);
    UART_push(uartdata[0]);
    switch(UART_pull(0)) {
		case 100: // SUBTRACTIVE
			if (UART_pull(7) == 101){
				if (UART_pull(8) == UART_checksum()){
					if (UART_pull(1) == 1){
						UART_send(100, 1, 0,0,0,0,0);
						method = subtractive;
					} else if (UART_pull(1) == 2){
						UART_send(100, 2, 0,0,0,0,0);
					}

					if (UART_pull(1) == 3){
						sub_highfreq = UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256;
					}
					if (UART_pull(1) == 4){
						sub_lowfreq = UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256;
					}
					if (UART_pull(1) == 5){
						filterSet = UART_pull(2);
					}
					if (UART_pull(1) == 6){
						waveformSet = UART_pull(2);
					}
				}
			}
			break;
	    case 101: // ADDITIVE
	    	if (UART_pull(7) == 102){
	    		if (UART_pull(8) == UART_checksum()) {
	    			if (UART_pull(1) == 1){
	    				UART_send(101, 1, 0, 0, 0, 0, 0);
	    				method = additive;
	    			} else if (UART_pull(1) == 2){
	    				UART_send(101, 2, 0, 0, 0, 0, 0);
	    			}
					if (UART_pull(1) == HAMMOND_KNOB1_UART){
						add_knobAmp[HAMMOND_KNOB1] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB2_UART){
						add_knobAmp[HAMMOND_KNOB2] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB3_UART){
						add_knobAmp[HAMMOND_KNOB3] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB4_UART){
						add_knobAmp[HAMMOND_KNOB4] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB5_UART){
						add_knobAmp[HAMMOND_KNOB5] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB6_UART){
						add_knobAmp[HAMMOND_KNOB6] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB7_UART){
						add_knobAmp[HAMMOND_KNOB7] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB8_UART){
						add_knobAmp[HAMMOND_KNOB8] = (UART_pull(2))*0.125;
					}
					if (UART_pull(1) == HAMMOND_KNOB9_UART){
						add_knobAmp[HAMMOND_KNOB9] = (UART_pull(2))*0.125;
					}
	    		}
	    	}
	    	break;
		case 102: // FM
			if (UART_pull(7) == 103){
				if (UART_pull(8) == UART_checksum()){
					if (UART_pull(1) == 1){
						UART_send(102, 1, 0,0,0,0,0);
						method = fm;
					} else if (UART_pull(1) == 2){
						UART_send(102, 2, 0,0,0,0,0);
					}

					if (UART_pull(1) == 5){
						UART_send(102, 5, 0,0,0,0,0);
						method = fm_bell;
					} else if (UART_pull(1) == 6){
						UART_send(102, 6, 0,0,0,0,0);
					}

					if (UART_pull(1) == 3){
							fm_modfreq = UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256;
						}
					if (UART_pull(1) == 4){
							fm_modamp = UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256;
						}
					if (UART_pull(1) == 7){
						bell_adsr_coefficient = (double)(UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256)/100.0;
					}
				}
			}
			break;
		case 109: // Flute
			if (UART_pull(7) == 110){
				if (UART_pull(8) == UART_checksum()) {
					if (UART_pull(1) == 1) {
						UART_send(109, 1, 0, 0, 0, 0, 0);
						method = flute;
						release_rate = 1.0;
						attack_rate = 1.0;
					} else if (UART_pull(1) == 2) {
						UART_send(109, 2, 0, 0, 0, 0, 0);
					}
					if (UART_pull(1) == 3) {
						fm_modfreq = UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256;
					}
				}
			}
			break;
		case 105: // violin
			if (UART_pull(7) == 106){
				if (UART_pull(8) == UART_checksum()){
					if (UART_pull(1) == 1){
						UART_send(105, 1, 0,0,0,0,0);
						method = violin;
					} else if (UART_pull(1) == 2){
						UART_send(105, 2, 0,0,0,0,0);
					}


					if (UART_pull(1) == 3){
							vibrato_freq = (double)(UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256)/1000.0;
						}
					if (UART_pull(1) == 4){
							vibrato_gain = (double)(UART_pull(2) + UART_pull(3)*256 + UART_pull(4)*256*256 + UART_pull(5)*256*256*256)/1000.0;
						}
				}
			}
			break;
		case 200: // ADSR
			if (UART_pull(7) == 201){
				if (UART_pull(8) == UART_checksum()){
					if (UART_pull(1) == 1) {
						attack_rate = (UART_pull(2) + UART_pull(3)*256)*ADSR_ATT_TIME;
					} else if (UART_pull(1) == 2) {
						decay_rate = (UART_pull(2) + UART_pull(3)*256)*ADSR_DEC_TIME;
					} else if (UART_pull(1) == 3) {
						sustain_level = (UART_pull(2) + UART_pull(3)*256)*ADSR_SUS_LEVEL;
						attack_level = sustain_level*1.3;
					} else if (UART_pull(1) == 4) {
						release_rate = (UART_pull(2) + UART_pull(3)*256)*ADSR_REL_TIME;
					}
				}
			}
			break;
    }
}

interrupt void dmax_isr( void )
{
    volatile unsigned *GPTransferEntry;
    static int *pDac = (int *)dmaxDacBuffer[0];

	// Verify if a DAC transfer completed
	if( hDmaxDac->regs->DTCR0 & (1<<DAC_TCC) )
	{
		hDmaxDac->regs->DTCR0 = (1<<DAC_TCC);

		// Save the pointer of the audio buffer that has just been transmitted
		GPTransferEntry  = (unsigned *)&hDmaxDac->regs->HiPriorityEventTable;
	    GPTransferEntry += ((*(hDmaxDac->hiTableEventEntryPtr)>>8)&0x07F);
		PP = GPTransferEntry[2] >> 31;
		pDac = (int *)dmaxDacBuffer[!PP];
		//pDac = (int *)waveform[licz*128];

		OBuf3.pBuf = pDac;

		int i = 0;
		if (licz == 0){
			licz = OVERLAP/FRAME_SIZE;
			i = OVERLAP%FRAME_SIZE;
		}
		int index = 0;
		for(i = 0; i < FRAME_SIZE; i++) {
			index = licz*FRAME_SIZE + i;
			if (index < 1024 - OVERLAP) {
				if (whichwaveform){
					dmaxDacBuffer[!PP][0][0][i] = waveform1[index];
					dmaxDacBuffer[!PP][1][0][i] = waveform1[index];
					plot[index] = waveform1[index];
				} else {
					dmaxDacBuffer[!PP][0][0][i] = waveform0[index];
					dmaxDacBuffer[!PP][1][0][i] = waveform0[index];
					plot[index + 1024 - OVERLAP] = waveform0[index];
				}
			} else {
				int wsp = -1024 + OVERLAP + index;
				if (whichwaveform){
					dmaxDacBuffer[!PP][0][0][i] = waveform1[index] + waveform0[wsp];
					dmaxDacBuffer[!PP][1][0][i] = waveform1[index] + waveform0[wsp];
					plot[index] = waveform1[index] + waveform0[wsp];
				} else {
					dmaxDacBuffer[!PP][0][0][i] = waveform0[index] + waveform1[wsp];
					dmaxDacBuffer[!PP][1][0][i] = waveform0[index] + waveform1[wsp];
					plot[index + 1024 - OVERLAP] = waveform0[index] + waveform1[wsp];
				}
				if (index >= 1024-1){
					if(whichwaveform == 1) {
						whichwaveform = 0;
					} else if(whichwaveform == 0) {
						whichwaveform = 1;
					}
					sem_dac = 1;
				}
			}
		}

		/*
		OBuf2.ptab[LEFT][CH_0] = (int)waveform[wav_iterator];
		OBuf2.ptab[RIGHT][CH_0] = (int)waveform[wav_iterator];

		wav_iterator = wav_iterator + 1;
		if(wav_iterator >= N)
			wav_iterator = 0;

        Buf[k] = OBuf3.ptab[LEFT][CH_0][20];  //Zapamiêtanie próbki wyjœciowej
        k++;							  //w buforze pomocniczym
        if (k == N) { k = 0; }
		 */

        licz++;
        if(licz >= 8) {
        	licz = 0;
        }
	}
}

