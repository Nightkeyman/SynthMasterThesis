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
		waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

void square_wave(int freq, int amp, int counter) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		v[i] = (float)(1*sin((double)(i/2 + counter)*2.0*M_PI*freq*(1.0/Fs)));// + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		if(v[i] >= 0) v[i] = 1;
		else v[i] = -1;
		//waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

void sawtooth_wave(int freq, int amp) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		v[i] = amp*((i/2)%(Fs/freq))/((float)Fs/(float)freq) - amp/2;
		waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

