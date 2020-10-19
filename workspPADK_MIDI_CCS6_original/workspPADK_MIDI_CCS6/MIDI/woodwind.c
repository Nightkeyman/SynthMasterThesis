/*
 * woodwind.c
 *
 *  Created on: 9 wrz 2020
 *      Author: Jan
 */

#include "woodwind.h"
#include <stdlib.h>


//////// FUNCTIONS FOR SYNTHESIS VIA WAVEGUIDE ////////
void genNoise_full() {
	// ARMA filter: http://software-dl.ti.com/jacinto7/esd/processor-sdk-rtos-jacinto7/latest/exports/docs/dsplib_c66x_3_4_0_0/docs/doxygen/html/dsplib_html/group___d_s_p__iir.html
	int i = 0;
	for(i = 0; i < N; i++) {
		x[i] = (double)rand()/RAND_MAX - 0.5;
	}
}
