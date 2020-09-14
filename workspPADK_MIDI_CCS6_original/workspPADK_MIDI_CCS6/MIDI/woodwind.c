/*
 * woodwind.c
 *
 *  Created on: 9 wrz 2020
 *      Author: Jan
 */

#include "woodwind.h"
#include <stdlib.h>


//////// FUNCTIONS FOR SYNTHESIS VIA ARMA ////////
void filterARMA() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0, j = 0, p = 0;
	for(i = 0; i < N; i++) {
		if(i == N/4) {
			genNoise_half(N/2);
			for(p = N/2; p < N; p++) {
				r1[p] = 0;
			}
		}
		for(j = 0; j < nh; j++) {
			if((i <= nh) && (i-j-1+N <= N-1)) { //TU ZA PEWNO NIE MA BYC N-1 TYLKO CO INNEGO
				r1[i] = r1[i] + h2[j]*x[i-j-2+N] - h1[j+1]*r1[i-j-1+N];
			} else if(i-j-2 <= -1) { //TU ZA PEWNO NIE MA BYC -1 TYLKO CO INNEGO
				r1[i] = r1[i] + h2[j]*x[i-j-2+N] - h1[j+1]*r1[i-j-1];
			} else {
				r1[i] = r1[i] + h2[j]*x[i-j-2] - h1[j+1]*r1[i-j-1];
			}
		}
	}
}


void genNoise_half(int start) {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = start;
	for(i = start; i < (start + N/2); i++) {
		x[i] = (double)rand()/RAND_MAX - 0.5;
	}
}

//////// FUNCTIONS FOR SYNTHESIS VIA WAVEGUIDE ////////
void genNoise_full(int start) {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0;
	for(i = 0; i < N; i++) {
		x[i] = (double)rand()/RAND_MAX - 0.5;
	}
}
