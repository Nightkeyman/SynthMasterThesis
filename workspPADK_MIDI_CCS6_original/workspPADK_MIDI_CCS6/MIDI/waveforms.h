/*
 * waveforms.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */

#ifndef WAVEFORMS_H_
#define WAVEFORMS_H_

#define N 1024
#define Fs 96000
#define M_PI 3.14159
extern float v[2*N];
extern float freqs[128];
// ADSR GLOBALS
extern float adsr[6];
extern int adsr_state[6];
extern int pressedkeys;

extern float attack_rate;
extern float attack_level;

extern float decay_rate;
extern float sustain_level;

extern float release_rate;

//extern int waveform[2*N];

void sin_wave(int freq, int amp);
void square_wave(int freq, int amp, int counter, int edit, int adsr_index);
void sawtooth_wave(int freq, int amp);


#endif /* WAVEFORMS_H_ */
