#include<stdio.h>
#include <stdlib.h>

#include "t1.h"

unsigned long long dupMasLargo(unsigned long long x){
    unsigned int s1,s2;

    for (int i = 0; i < 32; i++){
        s1 = x;
        s1 <<= i;
        s1 >>= i;

        s2 = ((((x << 2*i)>>2*i)<<i)>>32);

        if (s1==s2){
            x = 0;
            unsigned long long large = 32 - i;
            large <<= 32;
            x = s1 + large;
            return x;

        }
    }


    return 0;
}
