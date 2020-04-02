/*
 * myfft.c
 *
 *  Created on: 2 kwi 2020
 *      Author: Jan
 */
#include "myfft.h"

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

void bitrev_full() {
	bitrev_index(table,N);
	gen_twiddle(w, N);
	bit_rev(w,N>>1);
}
