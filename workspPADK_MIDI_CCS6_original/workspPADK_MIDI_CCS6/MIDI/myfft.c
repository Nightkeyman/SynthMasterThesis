/*
 * myfft.c
 *
 *  Created on: 2 kwi 2020
 *      Author: Jan
 */
#include "myfft.h"
#include <math.h>

void bit_rev(int n)
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
		   rtemp    = w[j*2];
		   w[j*2]   = w[i*2];
		   w[i*2]   = rtemp;
		   itemp    = w[j*2+1];
		   w[j*2+1] = w[i*2+1];
		   w[i*2+1] = itemp;
		  }
		}
}

int gen_twiddle(int n)
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

void bitrev_index(int n)
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

	table[0] = 0;
	for ( i = 1, j = n2/radix + 1; i < n2 - 1; i++)
	{
		table[i] = j - 1;

		for (k = n2/radix; k*(radix-1) < j; k /= radix)
			j -= k*(radix-1);

		j += k;
	}
	table[n2 - 1] = n2 - 1;
}

void bitrev_full() {
	bitrev_index(N);
	gen_twiddle(N);
	bit_rev(N>>1);
}

void fft_full() {
	bitrev_full();
	DSPF_sp_cfftr2_dit(v, w, N);
	DSPF_sp_bitrev_cplx((double*)v, table, N);
}

void ifft_full() {
	DSPF_sp_bitrev_cplx((double*)v,table,N);
	DSPF_sp_icfftr2_dif(v,w,N);
}
