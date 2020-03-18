// This demo shows how to perform an analog audio loopback on the PADK.
//
// The sampling rate will be set to 96 kHz and will be generated
// by one of the onboard oscillators. The sampling frequency source will 
// be configured using the module CLKGEN of the PADK library.
//
// Each ADC channel will be sent to the corresponding DAC channel:
//      ADC #1 -> DAC #1
//      ADC #2 -> DAC #2
//      ADC #3 -> DAC #3
//      ADC #4 -> DAC #4
//
// The ADC and the DAC devices will be initialized using the functions
// of the PADK library. These devices are connected to the DSP through 
// the serializers of the McASP #0. 
//      ADC #1 -> McASP0 Serializer 0 (AXR0_0)
//      ADC #2 -> McASP0 Serializer 1 (AXR0_1)
//      ADC #3 -> McASP0 Serializer 2 (AXR0_2)
//      ADC #4 -> McASP0 Serializer 3 (AXR0_3)
//      DAC #1 -> McASP0 Serializer 4 (AXR0_4)
//      DAC #2 -> McASP0 Serializer 5 (AXR0_5)
//      DAC #3 -> McASP0 Serializer 6 (AXR0_6)
//      DAC #4 -> McASP0 Serializer 10 (AXR0_10)
//
// The McASP and the dMAX will be initialized using TI's CSL library.
// The dMAX will be used to sort the input data coming from the ADCs 
// into a separate buffer for each stereo channel (left and right buffer). 
// The same organisation will be used for the DAC output data.
// 
//      ADC #0 Left Sample 0
//      ADC #0 Left Sample 1
//      ...
//      ADC #0 Left Sample n-1
//      ADC #0 Left Sample n
//      ADC #1 Left Sample 0
//      ADC #1 Left Sample 1
//      ...
//      ADC #1 Left Sample n-1
//      ADC #2 Left Sample n
//      ADC #2 Left Sample 0
//      ADC #2 Left Sample 1
//      ...
//      ADC #2 Left Sample n-1
//      ADC #2 Left Sample n
//      ADC #3 Left Sample 0
//      ADC #3 Left Sample 1
//      ...
//      ADC #3 Left Sample n-1
//      ADC #3 Left Sample n
//

// CSL Modules
#include <soc.h>
#include <csl_chip.h>
#include <csl_intc.h>
#include <csl_dmax.h>
#include <csl_mcasp.h>
#include <math.h>
// PADK Library
//#include "api/PADK.h"
#include "PADK.h"
#include <stdio.h>
#include <stdlib.h>

#include "PADK_UART.h"

	unsigned char int2bcd[16] = {
		0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71
	};//  0     1	  2		3	  4		5	  6		7	  8		9	  A		b	  C		d	  E		F

//  Kody wskaźnika 7-segmentowego
//   H - byte      L - byte
//  X7 X6 X5 X4   X3 X2 X1 X0
//
//       --X0--
//      |      |
//     X5      X1
//      |      |
//       --X6--
//      |      |
//     X4      X2
//      |      |
//       --X3-- o X7
//
	unsigned char data;
	unsigned char bcd;
	unsigned char data_midi[32];
	int btn1, btn2;

#define MIDI_buff_length 3
volatile unsigned char MIDI_buff[MIDI_buff_length] = {{0}};
unsigned char MIDI_buff_iterator = 0;

#include "var&fun.h"

MIDI_Params params = MIDI_DEFAULT_PARAMS;  // structure of MIDI params

//int 	xx = MIDI_Reset();
#define M_PI 3.1416

void bit_rev(float* x, int n);
int gen_twiddle(float *w, int n);
void bitrev_index(short *index, int n);
void MIDI_push(unsigned char data);
unsigned char MIDI_pull(  char offset);
void MIDI_clear();

void MIDI_push(unsigned char data){ // 600 nanoseconds
	MIDI_buff_iterator++;
    if (MIDI_buff_iterator >= MIDI_buff_length)
    	MIDI_buff_iterator = 0;
    MIDI_buff[MIDI_buff_iterator] = data;
}

unsigned char MIDI_pull(char offset){

	int index = 0;
	if (MIDI_buff_iterator + offset >= 0)
		index = MIDI_buff_iterator + offset ;
	else
		index = MIDI_buff_length + MIDI_buff_iterator + offset;
	return MIDI_buff[index];

}
void MIDI_clear(){
	unsigned char i = 0;
	for (i = 0; i < MIDI_buff_length; i++)
		MIDI_buff[i] = 0;
}


#define N 1024
 short  table[64];
#pragma DATA_ALIGN(v, 8)
 float  v[2*N];
#pragma DATA_ALIGN(w, 8)
 float  w[N];

void bit_rev(float* x, int n)
{
	 int i, j, k;
	 float rtemp, itemp;

	 j = 0;
	 for(i=1; i < (n-1); i++)
		{
		k = n >> 1;
		while(k <= j)
			 {
			 j -= k;
			 k >>= 1;
			 }
		j += k;
		if(i < j)
		  {
		   rtemp    = x[j*2];
		   x[j*2]   = x[i*2];
		   x[i*2]   = rtemp;
		   itemp    = x[j*2+1];
		   x[j*2+1] = x[i*2+1];
		   x[i*2+1] = itemp;
		  }
		}
}

int gen_twiddle(float *w, int n)
{
	double delta = 2 * M_PI / n;
	int i;
	for(i = 0; i < n/2; i++)
	{
		w[2 * i + 1] = sin(i * delta);
		w[2 * i] = cos(i * delta);
	}

 return n;
}

void bitrev_index(short *index, int n)
{
	int   i, j, k, radix = 2;
	short nbits, nbot, ntop, ndiff, n2, raddiv2;

	nbits = 0;
	i = n;
	while (i > 1)
	{
		i = i >> 1;
		nbits++;
	}

	raddiv2 = radix >> 1;
	nbot    = nbits >> raddiv2;
	nbot    = nbot << raddiv2 - 1;
	ndiff   = nbits & raddiv2;
	ntop    = nbot + ndiff;
	n2      = 1 << ntop;

	index[0] = 0;
	for ( i = 1, j = n2/radix + 1; i < n2 - 1; i++)
	{
		index[i] = j - 1;

		for (k = n2/radix; k*(radix-1) < j; k /= radix)
			j -= k*(radix-1);

		j += k;
	}
	index[n2 - 1] = n2 - 1;
}

#define Fs 96000
#define F_sq 1000
#define F_sqq 10000
double waveform[2*N];
float vv[2*N];
float vv_test[2*N];
//float hann[256] = {0,0.00015177,0.000607,0.0013654,0.0024265,0.0037897,0.0054542,0.0074189,0.0096826,0.012244,0.015102,0.018253,0.021698,0.025433,0.029455,0.033764,0.038355,0.043227,0.048376,0.0538,0.059494,0.065456,0.071681,0.078166,0.084908,0.091902,0.099143,0.10663,0.11435,0.12231,0.1305,0.13891,0.14754,0.15638,0.16543,0.17469,0.18414,0.19379,0.20362,0.21363,0.22382,0.23417,0.24468,0.25535,0.26617,0.27713,0.28823,0.29945,0.31079,0.32225,0.33382,0.34549,0.35725,0.3691,0.38103,0.39303,0.4051,0.41722,0.4294,0.44161,0.45387,0.46615,0.47845,0.49076,0.50308,0.5154,0.52771,0.54,0.55226,0.5645,0.5767,0.58885,0.60094,0.61298,0.62494,0.63683,0.64864,0.66036,0.67197,0.68349,0.69489,0.70618,0.71734,0.72837,0.73926,0.75,0.76059,0.77103,0.7813,0.7914,0.80132,0.81106,0.82061,0.82996,0.83912,0.84807,0.85681,0.86533,0.87363,0.8817,0.88954,0.89714,0.90451,0.91163,0.91849,0.92511,0.93146,0.93756,0.94339,0.94895,0.95423,0.95924,0.96398,0.96843,0.97259,0.97647,0.98006,0.98336,0.98636,0.98907,0.99149,0.9936,0.99542,0.99693,0.99814,0.99905,0.99966,0.99996,0.99996,0.99966,0.99905,0.99814,0.99693,0.99542,0.9936,0.99149,0.98907,0.98636,0.98336,0.98006,0.97647,0.97259,0.96843,0.96398,0.95924,0.95423,0.94895,0.94339,0.93756,0.93146,0.92511,0.91849,0.91163,0.90451,0.89714,0.88954,0.8817,0.87363,0.86533,0.85681,0.84807,0.83912,0.82996,0.82061,0.81106,0.80132,0.7914,0.7813,0.77103,0.76059,0.75,0.73926,0.72837,0.71734,0.70618,0.69489,0.68349,0.67197,0.66036,0.64864,0.63683,0.62494,0.61298,0.60094,0.58885,0.5767,0.5645,0.55226,0.54,0.52771,0.5154,0.50308,0.49076,0.47845,0.46615,0.45387,0.44161,0.4294,0.41722,0.4051,0.39303,0.38103,0.3691,0.35725,0.34549,0.33382,0.32225,0.31079,0.29945,0.28823,0.27713,0.26617,0.25535,0.24468,0.23417,0.22382,0.21363,0.20362,0.19379,0.18414,0.17469,0.16543,0.15638,0.14754,0.13891,0.1305,0.12231,0.11435,0.10663,0.099143,0.091902,0.084908,0.078166,0.071681,0.065456,0.059494,0.0538,0.048376,0.043227,0.038355,0.033764,0.029455,0.025433,0.021698,0.018253,0.015102,0.012244,0.0096826,0.0074189,0.0054542,0.0037897,0.0024265,0.0013654,0.000607,0.00015177,0};
float hann[1024] = {0,9.4308e-06,3.7723e-05,8.4875e-05,0.00015089,0.00023575,0.00033947,0.00046204,0.00060345,0.0007637,0.00094278,0.0011407,0.0013574,0.001593,0.0018473,0.0021204,0.0024123,0.002723,0.0030525,0.0034007,0.0037676,0.0041532,0.0045576,0.0049806,0.0054223,0.0058827,0.0063617,0.0068593,0.0073755,0.0079104,0.0084637,0.0090357,0.0096261,0.010235,0.010862,0.011508,0.012173,0.012855,0.013556,0.014276,0.015014,0.01577,0.016544,0.017336,0.018147,0.018976,0.019823,0.020688,0.021572,0.022473,0.023392,0.02433,0.025285,0.026258,0.027249,0.028258,0.029285,0.030329,0.031391,0.032471,0.033568,0.034683,0.035816,0.036966,0.038134,0.039319,0.040521,0.041741,0.042978,0.044232,0.045503,0.046792,0.048098,0.04942,0.05076,0.052117,0.05349,0.054881,0.056288,0.057712,0.059153,0.06061,0.062084,0.063574,0.065081,0.066604,0.068143,0.069699,0.071271,0.07286,0.074464,0.076084,0.077721,0.079373,0.081041,0.082725,0.084425,0.086141,0.087872,0.089618,0.09138,0.093158,0.094951,0.096759,0.098582,0.10042,0.10227,0.10414,0.10603,0.10792,0.10984,0.11177,0.11371,0.11567,0.11764,0.11962,0.12162,0.12364,0.12567,0.12771,0.12977,0.13184,0.13392,0.13602,0.13813,0.14026,0.1424,0.14455,0.14672,0.1489,0.15109,0.1533,0.15552,0.15775,0.15999,0.16225,0.16452,0.16681,0.1691,0.17141,0.17373,0.17606,0.17841,0.18077,0.18314,0.18552,0.18791,0.19032,0.19273,0.19516,0.1976,0.20005,0.20252,0.20499,0.20748,0.20997,0.21248,0.215,0.21752,0.22006,0.22261,0.22517,0.22774,0.23033,0.23292,0.23552,0.23813,0.24075,0.24338,0.24602,0.24867,0.25133,0.254,0.25668,0.25937,0.26206,0.26477,0.26748,0.2702,0.27294,0.27568,0.27843,0.28118,0.28395,0.28672,0.2895,0.29229,0.29509,0.29789,0.30071,0.30353,0.30636,0.30919,0.31203,0.31488,0.31774,0.3206,0.32347,0.32635,0.32923,0.33212,0.33502,0.33792,0.34083,0.34374,0.34666,0.34959,0.35252,0.35545,0.3584,0.36135,0.3643,0.36726,0.37022,0.37319,0.37616,0.37914,0.38212,0.38511,0.3881,0.39109,0.39409,0.3971,0.4001,0.40311,0.40613,0.40915,0.41217,0.41519,0.41822,0.42125,0.42429,0.42732,0.43036,0.43341,0.43645,0.4395,0.44255,0.4456,0.44865,0.45171,0.45477,0.45782,0.46089,0.46395,0.46701,0.47008,0.47314,0.47621,0.47928,0.48235,0.48542,0.48848,0.49156,0.49463,0.4977,0.50077,0.50384,0.50691,0.50998,0.51305,0.51612,0.51919,0.52226,0.52532,0.52839,0.53146,0.53452,0.53758,0.54065,0.54371,0.54676,0.54982,0.55288,0.55593,0.55898,0.56203,0.56507,0.56812,0.57116,0.5742,0.57723,0.58026,0.58329,0.58632,0.58934,0.59236,0.59538,0.59839,0.6014,0.60441,0.60741,0.6104,0.6134,0.61639,0.61937,0.62235,0.62533,0.6283,0.63126,0.63422,0.63718,0.64013,0.64307,0.64601,0.64895,0.65188,0.6548,0.65772,0.66063,0.66353,0.66643,0.66933,0.67221,0.67509,0.67796,0.68083,0.68369,0.68654,0.68939,0.69223,0.69506,0.69788,0.7007,0.70351,0.70631,0.7091,0.71189,0.71467,0.71744,0.7202,0.72295,0.72569,0.72843,0.73116,0.73388,0.73659,0.73929,0.74198,0.74466,0.74734,0.75,0.75265,0.7553,0.75794,0.76056,0.76318,0.76578,0.76838,0.77097,0.77354,0.77611,0.77866,0.78121,0.78374,0.78626,0.78878,0.79128,0.79377,0.79625,0.79872,0.80117,0.80362,0.80605,0.80848,0.81089,0.81329,0.81567,0.81805,0.82041,0.82276,0.8251,0.82743,0.82975,0.83205,0.83434,0.83661,0.83888,0.84113,0.84337,0.84559,0.84781,0.85001,0.85219,0.85437,0.85653,0.85867,0.86081,0.86292,0.86503,0.86712,0.8692,0.87126,0.87331,0.87535,0.87737,0.87938,0.88137,0.88335,0.88532,0.88727,0.8892,0.89112,0.89303,0.89492,0.89679,0.89865,0.9005,0.90233,0.90415,0.90595,0.90773,0.9095,0.91126,0.913,0.91472,0.91643,0.91812,0.91979,0.92145,0.9231,0.92473,0.92634,0.92794,0.92952,0.93108,0.93263,0.93416,0.93567,0.93717,0.93866,0.94012,0.94157,0.943,0.94442,0.94582,0.9472,0.94856,0.94991,0.95124,0.95256,0.95385,0.95513,0.9564,0.95764,0.95887,0.96008,0.96128,0.96245,0.96361,0.96475,0.96588,0.96698,0.96807,0.96914,0.9702,0.97123,0.97225,0.97325,0.97423,0.9752,0.97614,0.97707,0.97798,0.97887,0.97975,0.9806,0.98144,0.98226,0.98306,0.98385,0.98461,0.98536,0.98609,0.9868,0.98749,0.98816,0.98882,0.98945,0.99007,0.99067,0.99125,0.99182,0.99236,0.99288,0.99339,0.99388,0.99435,0.9948,0.99523,0.99565,0.99604,0.99642,0.99678,0.99711,0.99743,0.99774,0.99802,0.99828,0.99853,0.99875,0.99896,0.99915,0.99932,0.99947,0.9996,0.99971,0.99981,0.99988,0.99994,0.99998,1,1,0.99998,0.99994,0.99988,0.99981,0.99971,0.9996,0.99947,0.99932,0.99915,0.99896,0.99875,0.99853,0.99828,0.99802,0.99774,0.99743,0.99711,0.99678,0.99642,0.99604,0.99565,0.99523,0.9948,0.99435,0.99388,0.99339,0.99288,0.99236,0.99182,0.99125,0.99067,0.99007,0.98945,0.98882,0.98816,0.98749,0.9868,0.98609,0.98536,0.98461,0.98385,0.98306,0.98226,0.98144,0.9806,0.97975,0.97887,0.97798,0.97707,0.97614,0.9752,0.97423,0.97325,0.97225,0.97123,0.9702,0.96914,0.96807,0.96698,0.96588,0.96475,0.96361,0.96245,0.96128,0.96008,0.95887,0.95764,0.9564,0.95513,0.95385,0.95256,0.95124,0.94991,0.94856,0.9472,0.94582,0.94442,0.943,0.94157,0.94012,0.93866,0.93717,0.93567,0.93416,0.93263,0.93108,0.92952,0.92794,0.92634,0.92473,0.9231,0.92145,0.91979,0.91812,0.91643,0.91472,0.913,0.91126,0.9095,0.90773,0.90595,0.90415,0.90233,0.9005,0.89865,0.89679,0.89492,0.89303,0.89112,0.8892,0.88727,0.88532,0.88335,0.88137,0.87938,0.87737,0.87535,0.87331,0.87126,0.8692,0.86712,0.86503,0.86292,0.86081,0.85867,0.85653,0.85437,0.85219,0.85001,0.84781,0.84559,0.84337,0.84113,0.83888,0.83661,0.83434,0.83205,0.82975,0.82743,0.8251,0.82276,0.82041,0.81805,0.81567,0.81329,0.81089,0.80848,0.80605,0.80362,0.80117,0.79872,0.79625,0.79377,0.79128,0.78878,0.78626,0.78374,0.78121,0.77866,0.77611,0.77354,0.77097,0.76838,0.76578,0.76318,0.76056,0.75794,0.7553,0.75265,0.75,0.74734,0.74466,0.74198,0.73929,0.73659,0.73388,0.73116,0.72843,0.72569,0.72295,0.7202,0.71744,0.71467,0.71189,0.7091,0.70631,0.70351,0.7007,0.69788,0.69506,0.69223,0.68939,0.68654,0.68369,0.68083,0.67796,0.67509,0.67221,0.66933,0.66643,0.66353,0.66063,0.65772,0.6548,0.65188,0.64895,0.64601,0.64307,0.64013,0.63718,0.63422,0.63126,0.6283,0.62533,0.62235,0.61937,0.61639,0.6134,0.6104,0.60741,0.60441,0.6014,0.59839,0.59538,0.59236,0.58934,0.58632,0.58329,0.58026,0.57723,0.5742,0.57116,0.56812,0.56507,0.56203,0.55898,0.55593,0.55288,0.54982,0.54676,0.54371,0.54065,0.53758,0.53452,0.53146,0.52839,0.52532,0.52226,0.51919,0.51612,0.51305,0.50998,0.50691,0.50384,0.50077,0.4977,0.49463,0.49156,0.48848,0.48542,0.48235,0.47928,0.47621,0.47314,0.47008,0.46701,0.46395,0.46089,0.45782,0.45477,0.45171,0.44865,0.4456,0.44255,0.4395,0.43645,0.43341,0.43036,0.42732,0.42429,0.42125,0.41822,0.41519,0.41217,0.40915,0.40613,0.40311,0.4001,0.3971,0.39409,0.39109,0.3881,0.38511,0.38212,0.37914,0.37616,0.37319,0.37022,0.36726,0.3643,0.36135,0.3584,0.35545,0.35252,0.34959,0.34666,0.34374,0.34083,0.33792,0.33502,0.33212,0.32923,0.32635,0.32347,0.3206,0.31774,0.31488,0.31203,0.30919,0.30636,0.30353,0.30071,0.29789,0.29509,0.29229,0.2895,0.28672,0.28395,0.28118,0.27843,0.27568,0.27294,0.2702,0.26748,0.26477,0.26206,0.25937,0.25668,0.254,0.25133,0.24867,0.24602,0.24338,0.24075,0.23813,0.23552,0.23292,0.23033,0.22774,0.22517,0.22261,0.22006,0.21752,0.215,0.21248,0.20997,0.20748,0.20499,0.20252,0.20005,0.1976,0.19516,0.19273,0.19032,0.18791,0.18552,0.18314,0.18077,0.17841,0.17606,0.17373,0.17141,0.1691,0.16681,0.16452,0.16225,0.15999,0.15775,0.15552,0.1533,0.15109,0.1489,0.14672,0.14455,0.1424,0.14026,0.13813,0.13602,0.13392,0.13184,0.12977,0.12771,0.12567,0.12364,0.12162,0.11962,0.11764,0.11567,0.11371,0.11177,0.10984,0.10792,0.10603,0.10414,0.10227,0.10042,0.098582,0.096759,0.094951,0.093158,0.09138,0.089618,0.087872,0.086141,0.084425,0.082725,0.081041,0.079373,0.077721,0.076084,0.074464,0.07286,0.071271,0.069699,0.068143,0.066604,0.065081,0.063574,0.062084,0.06061,0.059153,0.057712,0.056288,0.054881,0.05349,0.052117,0.05076,0.04942,0.048098,0.046792,0.045503,0.044232,0.042978,0.041741,0.040521,0.039319,0.038134,0.036966,0.035816,0.034683,0.033568,0.032471,0.031391,0.030329,0.029285,0.028258,0.027249,0.026258,0.025285,0.02433,0.023392,0.022473,0.021572,0.020688,0.019823,0.018976,0.018147,0.017336,0.016544,0.01577,0.015014,0.014276,0.013556,0.012855,0.012173,0.011508,0.010862,0.010235,0.0096261,0.0090357,0.0084637,0.0079104,0.0073755,0.0068593,0.0063617,0.0058827,0.0054223,0.0049806,0.0045576,0.0041532,0.0037676,0.0034007,0.0030525,0.002723,0.0024123,0.0021204,0.0018473,0.001593,0.0013574,0.0011407,0.00094278,0.0007637,0.00060345,0.00046204,0.00033947,0.00023575,0.00015089,8.4875e-05,3.7723e-05,9.4308e-06,0};


void lowPassFilter(int freq) {
	freq = N - freq*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if((i > (N - freq)) && (i < (N + freq))) {	// Stworzenie filtru dolnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
		vv[i+1] = 0;
	}
}

void highPassFilter(int freq) {
	freq = N - freq*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if((i > (N + freq)) || (i < (N - freq))) {	// Stworzenie filtru górnoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}

void bandPassFilter(int freqLow, int freqHigh) {
	freqLow = N - freqLow*N/Fs - 1;
	freqHigh = N - freqHigh*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if( ((i > (N - freqHigh)) && (i < (N + freqHigh))) || ((i > (N + freqLow)) || (i < (N - freqLow))) ) {	// Stworzenie filtru srodkowoprzepustowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}

void bandStopFilter(int freqLow, int freqHigh) {
	freqLow = N - freqLow*N/Fs - 1;
	freqHigh = N - freqHigh*N/Fs - 1;
	int i = 0;
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		if( !(((i > (N - freqHigh)) && (i < (N + freqHigh))) || ((i > (N + freqLow)) || (i < (N - freqLow)))) ) {	// Stworzenie filtru srodkowozaporowego idealnego
			v[i] = 0;
			v[i+1] = 0;
		}
		vv[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
	}
}
//
//  Main Functions
//

CSL_DmaxCpuintEventSetup uartEventSetup =
{
	CSL_DMAX_EVENT28_ETYPE_CPUINT,
	CSL_DMAX_EVENT28_INT_INT11
};

CSL_DmaxHwSetup	uartDmaxHwSetup =
{
	// DMAX Priority (priority)
	CSL_DMAX_HI_PRIORITY,

	//DMAX Polarity (polarity)
    CSL_DMAX_POLARITY_RISING_EDGE,

	// DMAX Event initialization structure (eventSetup)
	&uartEventSetup
};


int notes[128] = {{0}};

int main( int argc, char *argv[] ) {

	#include "ALL_init.h"

	//int ret = SetupInterruptsUART();

	int i = 0;
	//clkgenParams.adc_scki
	// SINUSOID //
	for(i = 0; i < 2*N; i++) {
		v[i] = (float)(1*sin((double)(i/2)*2.0*M_PI*F_sq*(1.0/Fs))); // + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		waveform[i] = v[i];
		if(i%2 == 1) v[i] = 0;
	}

	// SQUARE//
	/*for(i = 0; i < 2*N; i++) {
		v[i] = (float)(1*sin((double)(i/2)*2.0*M_PI*F_sq*(1.0/Fs)));// + (float)(5*sin((double)(i/2)*2.0*M_PI*F_sqq*(1.0/Fs)));
		if(v[i] >= 0) v[i] = 1;
		else v[i] = -1;
		waveform[i] = v[i];
		if(i%2 == 1) v[i] = 0;
	}*/

	// SAWTOOTH //
	/*float amp = 3.0;
	for(i = 0; i < 2*N; i++) {
		v[i] = amp*((i/2)%(Fs/F_sq))/((float)Fs/(float)F_sq) - amp/2;
		waveform[i] = v[i];
		if(i%2 == 1) v[i] = 0;
	}*/

	// OKNO HANNINGA
	//for(i = 0; i < 2*N; i+=2) v[i] = v[i]*hann[i/2];

	bitrev_index(table,N);
	gen_twiddle(w, N);
	bit_rev(w,N>>1);

	// FFT
	DSPF_sp_cfftr2_dit(v,w,N);
	DSPF_sp_bitrev_cplx((double*)v,table,N);
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		v[i] = v[i]/(float)N;		// Skalowanie do najwyzszej probki --> moze to zrobic jakos lepiej ze znalezieniem najwiekszej wartosci?
		v[i+1] = v[i+1]/(float)N;
	}
	for(i = 0; i < 2*N; i+=2) {		// Liczenie modulu widma
		vv_test[i] = sqrt(v[i]*v[i] + v[i+1]*v[i+1]);
		vv_test[i+1] = 0;
	}
	lowPassFilter(20625);
	//highPassFilter(20625);
	//bandPassFilter(10500, 20625);
	//bandStopFilter(10500, 20625);

	// Inverse FFT
	DSPF_sp_bitrev_cplx((double*)v,table,N);
	DSPF_sp_icfftr2_dif(v,w,N);

	/*---------------------------------------------------------------*/
	/* Initialise the MIDI receiver/transmitter                      */
	/*---------------------------------------------------------------*/
	MIDI_Init(&params);

	/*---------------------------------------------------------------*/
	/* Read and send the initial status of the push button           */
	/*---------------------------------------------------------------*/
	btn1 = GPIO_GetPushButton( 1 );
	btn2 = GPIO_GetPushButton( 2 );
	data = (btn2<<1) | btn1;
	GPIO_SetBCD( int2bcd[0] );
	//USB_Write( USB_DSP2HOST_PIPE1, &data, 1, 1 );
	int bcditer = 0;
	int toggle_midi = 0;
    while(1)  {
    	if(MIDI_Read(data_midi, 1, 1) > 0) {
			MIDI_EnableLed1(toggle_midi ^= 1);
			MIDI_EnableLed2(!toggle_midi);
			if(data_midi[0] != 248) {
				MIDI_push(data_midi[0]);
				unsigned char status = (MIDI_pull(-2)>>4)&0x0F;
				if (status == 0x09) { // note on
					printf(" [MIDI note on] pitch: %d, velocity: %d \n", MIDI_pull(-1), MIDI_pull(0));
					unsigned char note = MIDI_pull(-1)&0x7f;
					notes[note] = 1;
					MIDI_clear();
				} else if (status == 0x08) { // note off
					printf(" [MIDI note off] pitch: %d, velocity: %d \n", MIDI_pull(-1), MIDI_pull(0));
					unsigned char note = MIDI_pull(-1)&0x7f;
					notes[note] = 0;
					MIDI_clear();
				}
			}
    	}
    }	
}
