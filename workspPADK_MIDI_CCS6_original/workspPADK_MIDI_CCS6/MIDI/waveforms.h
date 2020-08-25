/*
 * waveforms.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */

#ifndef WAVEFORMS_H_
#define WAVEFORMS_H_

#include "additive.h"

#define N 1024
#define Fs 48000
#define M_PI 3.14159
#define MIDI_POLY_MAX 12
#define SIG_AMP 100000

extern float v[2*N];
extern float freqs[MIDI_POLY_MAX];

// ADSR GLOBALS
extern float adsr[MIDI_POLY_MAX];
extern int adsr_state[MIDI_POLY_MAX];
extern int pressedkeys;
extern float attack_rate;
extern float attack_level;
extern float decay_rate;
extern float sustain_level;
extern float release_rate;

// ADDITIVE GLOBALS
extern float add_knobAmp[HAMMOND_KNOBS];

extern float sinusek[N];
extern float kwadracik[N];
//extern int waveform[2*N];

void sin_wave(int freq, int amp, int counter);
void square_wave(int freq, int amp, int counter, int edit, int adsr_index);
void sawtooth_wave(int freq, int amp);
void ADSR(int adsr_index);
void hammond_wave(int freq, int counter, int edit, int adsr_index);
float mySin(int counter, float freq);
float mySqr(int counter, float freq);
float myWav(int counter, float freq);
float mySin_fm(int counter, float freq, int modfm, int modamp);

#endif /* WAVEFORMS_H_ */
