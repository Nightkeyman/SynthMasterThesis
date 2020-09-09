/*
 * woodwind.h
 *
 *  Created on: 9 wrz 2020
 *      Author: Jan
 */

#ifndef WOODWIND_H_
#define WOODWIND_H_

#define N 1024
#define nh 5

extern short r1[N];
extern short r2[N];
extern short x[N];
extern short h2[nh];
extern short h1[nh];
extern short nr;

void filterARMA();
void genNoise();

#endif /* WOODWIND_H_ */
