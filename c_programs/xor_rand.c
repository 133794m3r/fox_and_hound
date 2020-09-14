#ifndef XOR_RANDOM_LIB
#define XOR_RANDOM_LIB
#ifndef uint64
typedef unsigned long long uint64;
#endif



#include "functions.h"
#include "functions.c"
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
bool XOR_SHIFT_32_SEEDED=false;
unsigned int XOR_32_STATE=0;


void seed_xor32(unsigned int seed){
	if(XOR_SHIFT_32_SEEDED){
		return;
	}
	
    if(seed!=0){
        XOR_32_STATE=seed;
    }
    else{
    	unsigned long long z = 0;
        seed=microtime()^clock()^getpid();
    	z=(seed+0x9E3779B97F4A7C15LL);
		z=(z^(z>>30))*0xBF58476D1CE4E5B9LL;
		z=(z^(z >> 27))*0x94D049BB133111EBLL;
		XOR_32_STATE = z >> 32;
    }
    // we discard some amount of initial values since most likely this is called w/o an inital seed.
    // we will get a value either 1,3,5, or 7 to do some "warmup" work.
    unsigned int iters = ((XOR_32_STATE & 3) << 1) + 1;
    unsigned int x = XOR_32_STATE;
    for(unsigned int i=0;i<iters;i++){
    	x ^= XOR_32_STATE << 13;
    	x ^= XOR_32_STATE << 17;
    	x ^= XOR_32_STATE << 5;
    }
    XOR_32_STATE = x;
}

unsigned int xor_32(unsigned int min, unsigned int max){
    if(!min&&!max){
        min=0;
        max=4294967295;
    }
    unsigned int range=(max-min);
    unsigned int x=0;
    x=XOR_32_STATE;
    x ^= XOR_32_STATE << 13;
    x ^= XOR_32_STATE << 17;
    x ^= XOR_32_STATE << 5;
    XOR_32_STATE=x;
	x=(x/4294967295)*range;
   
    return x;
}
#endif
