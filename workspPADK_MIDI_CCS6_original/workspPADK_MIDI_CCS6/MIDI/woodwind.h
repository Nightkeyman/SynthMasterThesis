/*
 * woodwind.h
 *
 *  Created on: 9 wrz 2020
 *      Author: Jan
 */

#ifndef WOODWIND_H_
#define WOODWIND_H_

#define N 1024
#define nh 13

extern double r1[N];
extern float r2[N];
extern double x[N];
extern double h2[nh+1];
extern double h1[nh+1];
extern short nr;

void filterARMA();
void genNoise();

#endif /* WOODWIND_H_ */
