/*
 * waveforms.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */

#ifndef WAVEFORMS_H_
#define WAVEFORMS_H_

#define N 2048
#define Fs 96000
#define M_PI 3.14159
extern float v[2*N];
extern float waveform[2*N];

void sin_wave(int freq, int amp);
void square_wave(int freq, int amp);
void sawtooth_wave(int freq, int amp);


#endif /* WAVEFORMS_H_ */
