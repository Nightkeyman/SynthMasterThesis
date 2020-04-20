/*
 * filters.h
 *
 *  Created on: 1 kwi 2020
 *      Author: Jan
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#define N 2048
#define Fs 96000
extern float v[2*N];
extern float vv[2*N];

void lowPassFilter(int freq);
void highPassFilter(int freq);
void bandPassFilter(int freqLow, int freqHigh);
void bandStopFilter(int freqLow, int freqHigh);

#endif /* FILTERS_H_ */
