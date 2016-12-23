/*
   By Marco Sousa ( marcojsousa@ufpa.br ).
   RGN adapted from Takuji Nishimura and Makoto Matsumoto ( Copyright
   (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura, All rights
   reserved ).

   This software is for academic use only.
*/

#include <cmath>

#ifdef WIN32

#include <windows.h>

#else

#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/io.h>

#endif

#include "Rand.h"

// -----------------------Inclui manualmente---------------
#include <stdio.h>
// --------------------------------------------------------

#define RAND_M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

/* initializes mt[RAND_N] with a seed */
void Rand::SetSeed( unsigned long s ){                                      //
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<RAND_N; mti++) {
        mt[mti] = (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

void Rand::SetSeed(){
	unsigned int s = 0;

#ifdef WIN32
	s = GetTickCount();
#else
	timeval t;
    gettimeofday(&t,NULL);	
	s = (unsigned long) t.tv_usec;
#endif
    SetSeed( s );
}

/* generates a random number on [0,0xffffffff]-interval */
unsigned long Rand::RandInt(){
    unsigned long y;
    unsigned long mag01[2]={0x0UL, MATRIX_A};

    if (mti >= RAND_N){ /* generate RAND_N words at one time */
        int kk;

		for (kk = 0; kk < RAND_N - RAND_M; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + RAND_M] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		for (; kk < RAND_N - 1; kk++) {
			y = (mt[kk] & UPPER_MASK) | (mt[kk + 1] & LOWER_MASK);
			mt[kk] = mt[kk + (RAND_M - RAND_N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
		}
		y = (mt[RAND_N - 1] & UPPER_MASK) | (mt[0] & LOWER_MASK);
		mt[RAND_N - 1] = mt[RAND_M - 1] ^ (y >> 1) ^ mag01[y & 0x1UL];
		mti = 0;
    }
  
    y = mt[mti++];

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return y;
}

/* generates a random number on [0,1]-real-interval */
double Rand::Uniform(){
    return RandInt()*(1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

/* Normal random of deviation 1 and mean 0 */
double Rand::Normal(){
	double u1,s2,t;

	do{
		u1=2.0*Uniform()-1.0;
		t=2.0*Uniform()-1.0;
		s2=u1*u1+t*t;
	} while (s2>=1.0);
	return (sqrt(-2.0*log(s2)/s2)*u1);
}

