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
	double h2_deb, h1_deb, r1_deb, h2_x, h1_r1;
	for(i = 0; i < N; i++) {
		r1[i] = 0;
	}
	for(i = nh+1; i < N; i++) {
		for(j = 0; j < nh; j++) {
			h2_deb = h2[j];
			h1_deb = h1[j+1];
			r1_deb = r1[i];
			h2_x = h2[j]*x[i-j-2];
			h1_r1 = h1[j+1]*r1[i-j-1];
			r1[i] = r1[i] + h2[j]*x[i-j-2] - h1[j+1]*r1[i-j-1];
		}
	}
}


void genNoise() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0;
	for(i = 0; i < N; i++) {
		x[i] = (double)rand()/RAND_MAX - 0.5;
	}

}
