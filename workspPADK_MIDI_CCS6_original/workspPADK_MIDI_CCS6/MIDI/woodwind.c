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
	int i = 0, j = 0, n = 0;
	for(i = 0; i < N; i++) {
		r1[i] = 0;
	}
	for(n = nh; n < N; n++) {
		//r1[i] = h2[0]*x[i];
		for(j = 0; j < nh; j++) {
			r1[n] = r1[n] + h2[j]*x[n-j] - h1[j]*r1[n-j];
		}
	}
}


void genNoise() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0;
	for(i = 0; i < N; i++) {
		x[i] = (float)rand()/RAND_MAX - 0.5;
	}
}
