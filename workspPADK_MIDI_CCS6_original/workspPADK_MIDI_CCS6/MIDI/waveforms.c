/*
 * waveforms.c
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */
#include "waveforms.h"
#include <math.h>

// AMP should be around 1000000000
void sin_wave(int freq, int amp, int counter) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		//v[i] = (float)(1*sin((double)(i/2)*2.0*M_PI*F_sq*(1.0/Fs))); // + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		v[i] = (float)(1*sin((double)(i/2 + counter)*2.0*M_PI*freq*(1.0/Fs))); // + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		//waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}

void square_wave(int freq, int amp, int counter, int edit, int adsr_index) {
	ADSR(adsr_index);
	int i = 0;
	if (edit == 1){
		for(i = 0; i < 2*N; i++) {
			if(mySin(i/2 + counter, freq) >= 0)
				v[i] = 1*adsr[adsr_index];
			else
				v[i] = -1*adsr[adsr_index];
			if(i%2 == 1) v[i] = 0;
		}
	} else if (edit == 0) {
		for(i = 0; i < 2*N; i+=2) {
			if(mySin(i/2 + counter, freq) >= 0)
				v[i] += 1*adsr[adsr_index];
			else
				v[i] += -1*adsr[adsr_index];
		}
	}
}
void triangle_wave(int freq, int amp, int counter, int edit, int adsr_index) {
	ADSR(adsr_index);
	int i = 0;
	float p = (float)Fs/(float)freq;
	float p1 = 4.0/p;
	float p2 = p/2.0;
	if (edit == 1){
		for(i = 0; i < 2*N; i++) {
			v[i] = ((p1)*((float)abs( (float)((i/2 +counter)%((int)(p+1))) - p2)) - 1.0)*adsr[adsr_index];
			if(i%2 == 1) v[i] = 0;
		}
	} else if (edit == 0) {
		for(i = 0; i < 2*N; i+=2) {
			v[i] += ((p1)*((float)abs( (float)((i/2 +counter)%((int)(p+1))) - p2)) - 1.0)*adsr[adsr_index];
		}
	}
}
void sawtooth_wave(int freq, int amp, int counter, int edit, int adsr_index) {
	ADSR(adsr_index);
	int i = 0;
	float p = (float)Fs/(float)freq;
	float p1 = 2.0/p;
	float p2 = p/2.0;
	if (edit == 1){
		for(i = 0; i < 2*N; i++) {
			v[i] = ((p1)*((float)( (float)((i/2 +counter)%((int)(p+1))) - p2)) )*adsr[adsr_index];
			if(i%2 == 1) v[i] = 0;
		}
	} else if (edit == 0) {
		for(i = 0; i < 2*N; i+=2) {
			v[i] += ((p1)*((float)( (float)((i/2 +counter)%((int)(p+1))) - p2)) )*adsr[adsr_index];
		}
	}
}
/*
 * nie bylem pewny czy mozna to usunac
void sawtooth_wave(int freq, int amp) {
	int i = 0;
	for(i = 0; i < 2*N; i++) {
		v[i] = amp*((i/2)%(Fs/freq))/((float)Fs/(float)freq) - amp/2;
		//waveform[i] = amp*v[i];
		if(i%2 == 1) v[i] = 0;
	}
}
*/

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

float mySin_fm(int counter, float freq, int modfm, int modamp)
{
	//return sinusek[(int)((float)N*((float)counter*freq/(float)Fs +  (float)modamp*mySin(counter, modfm)/(2*M_PI))) %N];
	return sinf(2*M_PI*counter*freq/(float)Fs);// + (float)modamp*sinf(2*M_PI*counter*modfm/(float)Fs));
}

float mySin_adv(int counter, float freq)
{
	/* KOD Z MATLABA KTORY DZIALA
	indf = (counter*freq*(N/Fs)) - fix(  counter*freq/Fs)*N;
	ind = fix(indf);
	wspa = indf - ind;
	ind2 = mod(ind+1, N);
	x = (1.0-wsp)*sinusek( ind+1) + wsp*sinusek(ind2+1);
	*/
	float indf = (float)counter*freq*(float)N/(float)Fs - (float)((int)(counter*freq/Fs)*N);
	int ind = (int)indf;
	float wsp = indf - (float)ind;
	int ind2 = (ind+1)%N;

	return ((1.0-wsp)*sinusek[ind] + wsp*sinusek[ind2]);
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

void hammond_wave(int freq, int counter, int edit, int adsr_index) {
	float phase = 0;
	int j = 0;
	ADSR(adsr_index);
	if (edit == 1) {
		for(j = 0; j < N; j++) {
			v[j*2] = adsr[adsr_index]*(add_knobAmp[HAMMOND_KNOB1]*mySin(j+counter, freq*0.5) + add_knobAmp[HAMMOND_KNOB2]*mySin(j+counter, freq) + add_knobAmp[HAMMOND_KNOB3]*mySin(j+counter, freq*1.5)
					+ add_knobAmp[HAMMOND_KNOB4]*mySin(j+counter, freq*2) + add_knobAmp[HAMMOND_KNOB5]*mySin(j+counter, freq*3) + add_knobAmp[HAMMOND_KNOB6]*mySin(j+counter, freq*4)
					+ add_knobAmp[HAMMOND_KNOB7]*mySin(j+counter, freq*5) + add_knobAmp[HAMMOND_KNOB8]*mySin(j+counter, freq*6) + add_knobAmp[HAMMOND_KNOB9]*mySin(j+counter, freq*8));
		}
	} else if(edit == 0) {
		for(j = 0; j < N; j++) {
			v[j*2] += adsr[adsr_index]*(add_knobAmp[HAMMOND_KNOB1]*mySin(j+counter, freq*0.5) + add_knobAmp[HAMMOND_KNOB2]*mySin(j+counter, freq) + add_knobAmp[HAMMOND_KNOB3]*mySin(j+counter, freq*1.5)
					+ add_knobAmp[HAMMOND_KNOB4]*mySin(j+counter, freq*2) + add_knobAmp[HAMMOND_KNOB5]*mySin(j+counter, freq*3) + add_knobAmp[HAMMOND_KNOB6]*mySin(j+counter, freq*4)
					+ add_knobAmp[HAMMOND_KNOB7]*mySin(j+counter, freq*5) + add_knobAmp[HAMMOND_KNOB8]*mySin(j+counter, freq*6) + add_knobAmp[HAMMOND_KNOB9]*mySin(j+counter, freq*8));
		}
	}
}
