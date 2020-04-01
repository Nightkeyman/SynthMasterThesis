/*
 * filters.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */
#include "filters.h"

#define N 1024
#define Fs 96000
extern float v[2*N];
extern float vv[2*N];

void lowPassFilter(int freq) {
	freq = N - freq*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if((i > (N - freq)) && (i < (N + freq))) {	// Stworzenie filtru dolnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
		vv[i+1] = 0;
	}
}

void highPassFilter(int freq) {
	freq = N - freq*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if((i > (N + freq)) || (i < (N - freq))) {	// Stworzenie filtru górnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}

void bandPassFilter(int freqLow, int freqHigh) {
	freqLow = N - freqLow*N/Fs - 1;
	freqHigh = N - freqHigh*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if( ((i > (N - freqHigh)) && (i < (N + freqHigh))) || ((i > (N + freqLow)) || (i < (N - freqLow))) ) {	// Stworzenie filtru srodkowoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}

void bandStopFilter(int freqLow, int freqHigh) {
	freqLow = N - freqLow*N/Fs - 1;
	freqHigh = N - freqHigh*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if( !(((i > (N - freqHigh)) && (i < (N + freqHigh))) || ((i > (N + freqLow)) || (i < (N - freqLow)))) ) {	// Stworzenie filtru srodkowozaporowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}

