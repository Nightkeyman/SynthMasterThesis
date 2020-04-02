/*
 * myfft.h
 *
 *  Created on: 2 kwi 2020
 *      Author: Jan
 */

#ifndef MYFFT_H_
#define MYFFT_H_

#define M_PI 3.14159
#define N 1024
extern float w[N];
extern short table[64];

void bit_rev(float* x, int n);

int gen_twiddle(float *w, int n);

void bitrev_index(short *index, int n);

void bitrev_full(short *index, float *w, );

#endif /* MYFFT_H_ */
