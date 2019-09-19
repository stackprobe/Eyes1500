/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
/*
   A C-program for MT19937, with initialization improved 2002/1/26.
   Coded by Takuji Nishimura and Makoto Matsumoto.

   Before using, initialize the state by using init_genrand(seed)
   or init_by_array(init_key, key_length).

   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

     1. Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.

     2. Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.

     3. The names of its contributors may not be used to endorse or promote
        products derived from this software without specific prior written
        permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


   Any feedback is very welcome.
   http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
   email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
*/

#include "all.h"
//#include <stdio.h>

/* Period parameters */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define N MT19937_N // 624
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define M 397
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define UPPER_MASK 0x80000000UL /* most significant w-r bits */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
#define LOWER_MASK 0x7fffffffUL /* least significant r bits */

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static unsigned long mt2[N];
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static unsigned long *mt = mt2; // mt[N]; /* the array for the state vector  */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int mti=N+1; /* mti==N+1 means mt[N] is not initialized */

/* initializes mt[N] with a seed */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static __inline void MT19937_init_genrand(unsigned long s)
{
    mt[0]= s & 0xffffffffUL;
    for (mti=1; mti<N; mti++) {
        mt[mti] =
	    (1812433253UL * (mt[mti-1] ^ (mt[mti-1] >> 30)) + mti);
        /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
        /* In the previous versions, MSBs of the seed affect   */
        /* only MSBs of the array mt[].                        */
        /* 2002/01/09 modified by Makoto Matsumoto             */
        mt[mti] &= 0xffffffffUL;
        /* for >32 bit machines */
    }
}

/* initialize by an array with array-length */
/* init_key is the array for initializing keys */
/* key_length is its length */
/* slight change for C++, 2004/2/26 */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static __inline void MT19937_init_by_array(unsigned long init_key[], int key_length)
{
    int i, j, k;
    MT19937_init_genrand(19650218UL);
    i=1; j=0;
    k = (N>key_length ? N : key_length);
    for (; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++; j++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
        if (j>=key_length) j=0;
    }
    for (k=N-1; k; k--) {
        mt[i] = (mt[i] ^ ((mt[i-1] ^ (mt[i-1] >> 30)) * 1566083941UL))
          - i; /* non linear */
        mt[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
        i++;
        if (i>=N) { mt[0] = mt[N-1]; i=1; }
    }

    mt[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */
}

/* generates a random number on [0,0xffffffff]-interval */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static __inline unsigned long MT19937_genrand_int32(void)
{
    unsigned long y;
    static unsigned long mag01[2]={0x0UL, MATRIX_A};
    /* mag01[x] = x * MATRIX_A  for x=0,1 */

    if (mti >= N) { /* generate N words at one time */
        int kk;

        if (mti == N+1)   /* if init_genrand() has not been called, */
            MT19937_init_genrand(5489UL); /* a default initial seed is used */

        for (kk=0;kk<N-M;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        for (;kk<N-1;kk++) {
            y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
            mt[kk] = mt[kk+(M-N)] ^ (y >> 1) ^ mag01[y & 0x1UL];
        }
        y = (mt[N-1]&UPPER_MASK)|(mt[0]&LOWER_MASK);
        mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1UL];

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

#if 0
/* generates a random number on [0,0x7fffffff]-interval */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000118 $$$$ //	static __inline long MT19937_genrand_int31(void)
// #### DELETED ==== 0000118 $$$$ //	{
// #### DELETED ==== 0000118 $$$$ //	    return (long)(MT19937_genrand_int32()>>1);
// #### DELETED ==== 0000118 $$$$ //	}

/* generates a random number on [0,1]-real-interval */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000119 $$$$ //	static __inline double MT19937_genrand_real1(void)
// #### DELETED ==== 0000119 $$$$ //	{
// #### DELETED ==== 0000119 $$$$ //	    return MT19937_genrand_int32()*(1.0/4294967295.0);
// #### DELETED ==== 0000119 $$$$ //	    /* divided by 2^32-1 –/
// #### DELETED ==== 0000119 $$$$ //	}

/* generates a random number on [0,1)-real-interval */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000120 $$$$ //	static __inline double MT19937_genrand_real2(void)
// #### DELETED ==== 0000120 $$$$ //	{
// #### DELETED ==== 0000120 $$$$ //	    return MT19937_genrand_int32()*(1.0/4294967296.0);
// #### DELETED ==== 0000120 $$$$ //	    /* divided by 2^32 –/
// #### DELETED ==== 0000120 $$$$ //	}

/* generates a random number on (0,1)-real-interval */
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000121 $$$$ //	static __inline double MT19937_genrand_real3(void)
// #### DELETED ==== 0000121 $$$$ //	{
// #### DELETED ==== 0000121 $$$$ //	    return (((double)MT19937_genrand_int32()) + 0.5)*(1.0/4294967296.0);
// #### DELETED ==== 0000121 $$$$ //	    /* divided by 2^32 –/
// #### DELETED ==== 0000121 $$$$ //	}

/* generates a random number on [0,1) with 53-bit resolution*/
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000122 $$$$ //	static __inline double MT19937_genrand_res53(void)
// #### DELETED ==== 0000122 $$$$ //	{
// #### DELETED ==== 0000122 $$$$ //	    unsigned long a=MT19937_genrand_int32()>>5, b=MT19937_genrand_int32()>>6;
// #### DELETED ==== 0000122 $$$$ //	    return(a*67108864.0+b)*(1.0/9007199254740992.0);
// #### DELETED ==== 0000122 $$$$ //	}
/* These real versions are due to Isaku Wada, 2002/01/09 added */

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000123 $$$$ //	static __inline int MT19937_main(void)
// #### DELETED ==== 0000123 $$$$ //	{
// #### DELETED ==== 0000123 $$$$ //	    int i;
// #### DELETED ==== 0000123 $$$$ //	    unsigned long init[4]={0x123, 0x234, 0x345, 0x456}, length=4;
// #### DELETED ==== 0000123 $$$$ //	    MT19937_init_by_array(init, length);
// #### DELETED ==== 0000123 $$$$ //	    printf("1000 outputs of genrand_int32()\n");
// #### DELETED ==== 0000123 $$$$ //	    for (i=0; i<1000; i++) {
// #### DELETED ==== 0000123 $$$$ //	      printf("%10lu ", MT19937_genrand_int32());
// #### DELETED ==== 0000123 $$$$ //	      if (i%5==4) printf("\n");
// #### DELETED ==== 0000123 $$$$ //	    }
// #### DELETED ==== 0000123 $$$$ //	    printf("\n1000 outputs of genrand_real2()\n");
// #### DELETED ==== 0000123 $$$$ //	    for (i=0; i<1000; i++) {
// #### DELETED ==== 0000123 $$$$ //	      printf("%10.8f ", MT19937_genrand_real2());
// #### DELETED ==== 0000123 $$$$ //	      if (i%5==4) printf("\n");
// #### DELETED ==== 0000123 $$$$ //	    }
// #### DELETED ==== 0000123 $$$$ //	    return 0;
// #### DELETED ==== 0000123 $$$$ //	}
#endif

// <-- original code

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
void initRnd(int seed)
{
	autoList<uchar> *initKey = sha512_expand(seed, 39); // (SEED_SIZE + (SHA512_SIZE * 39)) / ULONG_SIZE == (4 + (64 * 39)) / 4 == 625 == N + 1

	MT19937_init_by_array((unsigned long *)initKey->ElementAt(0), initKey->GetCount() / sizeof(unsigned long));
	delete initKey;
}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
static int Back_mti;

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000124 $$$$ //	void enterRnd(unsigned long *lmt, int lmti)
// #### DELETED ==== 0000124 $$$$ //	{
// #### DELETED ==== 0000124 $$$$ //		Back_mti = mti;
// #### DELETED ==== 0000124 $$$$ //	
// #### DELETED ==== 0000124 $$$$ //		mt = lmt;
// #### DELETED ==== 0000124 $$$$ //		mti = lmti;
// #### DELETED ==== 0000124 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000125 $$$$ //	void leaveRnd(int *p_lmti)
// #### DELETED ==== 0000125 $$$$ //	{
// #### DELETED ==== 0000125 $$$$ //		*p_lmti = mti;
// #### DELETED ==== 0000125 $$$$ //	
// #### DELETED ==== 0000125 $$$$ //		mt = mt2;
// #### DELETED ==== 0000125 $$$$ //		mti = Back_mti;
// #### DELETED ==== 0000125 $$$$ //	}

/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
int rnd(int modulo) // ret: 0 - (modulo - 1)
{
	errorCase(modulo < 1 || IMAX < modulo);

	if(modulo == 1)
	{
		return 0;
	}
	int r_mod = 0x40000000 % modulo;
	int r;

	do
	{
		r = MT19937_genrand_int32() >> 2;
	}
	while(r < r_mod);

#if 1
	r -= r_mod;
	r /= 0x40000000 / modulo;
#else
	r %= modulo;
#endif

	return r;
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000126 $$$$ //	int bRnd(int minval, int maxval) // ret: minval - maxval
// #### DELETED ==== 0000126 $$$$ //	{
// #### DELETED ==== 0000126 $$$$ //		errorCase(minval < -IMAX);
// #### DELETED ==== 0000126 $$$$ //		errorCase(maxval < minval);
// #### DELETED ==== 0000126 $$$$ //		errorCase(IMAX < maxval);
// #### DELETED ==== 0000126 $$$$ //	
// #### DELETED ==== 0000126 $$$$ //		return rnd(maxval - minval + 1) + minval;
// #### DELETED ==== 0000126 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000127 $$$$ //	int sRnd(void) // ret: -1 or 1
// #### DELETED ==== 0000127 $$$$ //	{
// #### DELETED ==== 0000127 $$$$ //		return rnd(2) ? -1 : 1;
// #### DELETED ==== 0000127 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
double dRnd(void) // ret: 0.0 - 1.0
{
	return rnd(IMAX) / (double)(IMAX - 1);
}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000128 $$$$ //	double eRnd(void) // ret: -1.0 - 1.0
// #### DELETED ==== 0000128 $$$$ //	{
// #### DELETED ==== 0000128 $$$$ //		return dRnd() * 2.0 - 1.0;
// #### DELETED ==== 0000128 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000129 $$$$ //	int rndPct(int pct) // pct: 0 - 100
// #### DELETED ==== 0000129 $$$$ //	{
// #### DELETED ==== 0000129 $$$$ //		return rnd(IMAX) < pct * (IMAX / 100);
// #### DELETED ==== 0000129 $$$$ //	}
/*
	copied the source file by https://github.com/stackprobe/Factory/blob/master/SubTools/CopyLib.c
*/
// #### DELETED ==== 0000130 $$$$ //	int rndPermil(int permil) // permil: 0 - 1000
// #### DELETED ==== 0000130 $$$$ //	{
// #### DELETED ==== 0000130 $$$$ //		return rnd(IMAX) < permil * (IMAX / 1000);
// #### DELETED ==== 0000130 $$$$ //	}
