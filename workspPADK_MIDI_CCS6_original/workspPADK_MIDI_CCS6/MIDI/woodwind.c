/*
 * woodwind.c
 *
 *  Created on: 9 wrz 2020
 *      Author: Jan
 */

#include "woodwind.h"
#include <stdlib.h>

void filterARMA() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0, j = 0;
	for(i = nh; i < N; i++) {
		r1[i] = h2[0]*x[i];
		for(j = 1; j < nh; j++) {
			r1[i] = r1[i] + h2[j]*x[i-j] - h1[j]*r1[i-j];
		}
	}
}


void genNoise() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0;
	for(i = 0; i < N; i++) {
		x[i] = rand();
	}
}
