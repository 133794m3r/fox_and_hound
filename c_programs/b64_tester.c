#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/**
* The basic C Program that they're going to be brute forcing the pin from.
* Macathur Inbody <mdi2455@email.vccs.edu>
* 2019-
* AGPLv3 or Later
*/
/**
* This function encodes a string passed to it as an argument into base64. It's
* ~1.5x as fast as the built in base64 program from gnulib. I am not allowing for
* pipes at this time though that is a feature for a future release.
*
*/
int base64_encode(unsigned char *dest, const unsigned char *src, int srclen){
    const char table[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned int i=0;
    unsigned int j=0;
    unsigned int a=0;
    unsigned int b=0;
    unsigned int c=0;
    unsigned int t=0;
    const char padding[1]="=";
    while (i < srclen){
        a=i < srclen ? src[i++] : 0;
        b=i < srclen ? src[i++] : 0;
        c=i < srclen ? src[i++] : 0;
        t= (a << 16) + (b << 8) + c;
        dest[j++]=table[ (t >> (3*6)) & 63];
        dest[j++]=table[ (t >> (2*6)) & 63];
        dest[j++]=table[ (t >> (1*6)) & 63];
        dest[j++]=table[ (t>>0) & 63];
    }
    if( ( srclen % 3) > 0){
        dest[j-1]=padding[0];
        if(( srclen %3) == 1){
            dest[j-2]=padding[0];
        }
    }
    return 0;
}
int main(int argc,char **argv){
    char *dest=malloc(8);
    char *help="-h";
    if(argc > 1 && strncmp(argv[1],help,3) != 0){
    char *src=malloc(4);
    src=argv[1];
    unsigned int srclen=strlen(src);
    base64_encode((unsigned char*)dest,(unsigned char*)src,srclen);
    printf("%s",dest);
    }
    else{
        printf("This program reads in from the single input a string to encode with base64.\n It does not read from stdin. -h will show this help.\n");
    }
    return 0;
}
