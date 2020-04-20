/*
 * myfft.h
 *
 *  Created on: 2 kwi 2020
 *      Author: Jan
 */

#ifndef MYFFT_H_
#define MYFFT_H_

#define M_PI 3.14159
#define N 2048

extern float w[N];
extern short table[64];
extern float v[2*N];

// FUNCTIONS //
void bit_rev(int n);
int gen_twiddle(int n);
void bitrev_index(int n);
void bitrev_full();
void fft_full();
void ifft_full();


#endif /* MYFFT_H_ */
