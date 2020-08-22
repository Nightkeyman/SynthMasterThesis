/*
 * filters.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */
#include "filters.h"
#include <math.h>

void lowPassFilter(int freq) {
	freq = freq*N/Fs + 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {
		if((i/2 >= (freq)) && (i/2 <= (N - freq))) {	// Stworzenie filtru dolnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
	}
}

void highPassFilter(int freq) {
	freq = freq*N/Fs + 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {
		if((i/2 <= (freq)) || (i/2 >= (N - freq))) {	// Stworzenie filtru górnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
	}
}

void bandPassFilter(int freqLow, int freqHigh) {
	freqLow = freqLow*N/Fs + 1;
	freqHigh = freqHigh*N/Fs + 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {
		if( ((i/2 >= (freqHigh)) && (i/2 <= (N - freqHigh))) || ((i/2 <= (freqLow)) || (i/2 >= (N - freqLow))) ) {	// Stworzenie filtru srodkowoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
	}
}

void bandStopFilter(int freqLow, int freqHigh) {
	freqLow = freqLow*N/Fs + 1;
	freqHigh = freqHigh*N/Fs + 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {
		if( !(((i/2 >= (freqHigh)) && (i/2 <= (N - freqHigh))) || ((i/2 <= (freqLow)) || (i/2 >= (N - freqLow)))) ) {	// Stworzenie filtru srodkowozaporowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
	}
}

