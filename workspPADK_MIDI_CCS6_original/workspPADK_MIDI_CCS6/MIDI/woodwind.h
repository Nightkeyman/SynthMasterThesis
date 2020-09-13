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

extern float r1[N];
extern float r2[N];
extern float x[N];
extern float h2[nh];
extern float h1[nh];
extern short nr;

void filterARMA();
void genNoise();

#endif /* WOODWIND_H_ */
