/*
 * waveforms.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */
#include "waveforms.h"
#include <math.h>

// AMP should be around 1000000000
void sin_wave(int freq, int amp) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		//v[i] = (float)(1*sin((double)(i/2)*2.0*M_PI*F_sq*(1.0/Fs))); // + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		v[i] = (float)(1*sin((double)(i)*2.0*M_PI*freq*(1.0/Fs))); // + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		//waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

void square_wave(int freq, int amp, int counter, int edit, int adsr_index) {
	ADSR(adsr_index);
	int i = 0;
	int harmonicsCount = (Fs/2)/freq;
	int j = 0;
	if (edit == 1){
		for(i = 0; i < 2*N; i++) {
			if(i%2 == 1) {
				v[i] = 0;
			} else {
				v[i] = 0;
				for(j = 1; j < harmonicsCount; j += 2) {
					v[i] += mySin(i/2 + counter, freq*j)/j;
				}
				v[i] *= adsr[adsr_index];
			}
		}
	} else if (edit == 0) {
		for(i = 0; i < 2*N; i+=2) {
			float temp = 0;
			for(j = 1; j < harmonicsCount; j += 2) {
				temp += mySin(i/2 + counter, freq*j)/j;
			}
			v[i] += temp*adsr[adsr_index];

		}
	}
}

void sawtooth_wave(int freq, int amp) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		v[i] = amp*((i/2)%(Fs/freq))/((float)Fs/(float)freq) - amp/2;
		//waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

void ADSR(int adsr_index) {
	if (adsr_state[adsr_index] == 1){ // attack
		if (adsr[adsr_index] < attack_level)
			adsr[adsr_index] += attack_rate;
		else
			adsr_state[adsr_index] = 2;
	}
	if (adsr_state[adsr_index] == 2){ // decay
		if (adsr[adsr_index] > sustain_level)
			adsr[adsr_index] -= decay_rate;
		else
		{
			adsr[adsr_index] = sustain_level;
			adsr_state[adsr_index] = 3;
		}
	}
	if (adsr_state[adsr_index] == 4){ // release
		if (adsr[adsr_index] > 0.0)
			adsr[adsr_index] -= release_rate;
		else
		{
			adsr_state[adsr_index] = 0;
			adsr[adsr_index] = 0.0;
			freqs[adsr_index] = 0.0;
			pressedkeys--;
		}
	}
}

float mySin(int counter, float freq)
{
	return sinusek[(int)((float)counter*freq*((float)N/(float)Fs))%N]; // N/Fs
}

float mySqr(int counter, float freq)
{
	if(sinusek[(int)((float)counter*freq*(0.02083333333))%N] >= 0) {
		return SIG_AMP;
	} else {
		return -1*SIG_AMP;
	}
}

float myWav(int counter, float freq)
{
	if(sinusek[(int)((float)counter*freq*(0.02083333333))%N] >= 0) {
		return SIG_AMP;
	} else {
		return -1*SIG_AMP;
	}
}
