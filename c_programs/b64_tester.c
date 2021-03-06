#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
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
static inline unsigned char uchar(char chr){ return chr;};
int base64_encode(char *dest, const char *src, int srclen){
    const char table[64]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    unsigned int i=0;
    unsigned int j=0;
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int t;
    const char padding[1]="=";
    while (i < srclen){
        //ternary's are used to save some sloc and b/c I'm lazy.       
        a=i < srclen ? uchar(src[i++]) : 0;
        b=i < srclen ? uchar(src[i++]) : 0;
        c=i < srclen ? uchar(src[i++]) : 0;
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
    char *dest=malloc(14);
    char *help="-h";
    char *src_buffer=malloc(sizeof *src_buffer);
    char *total_buffer=malloc(sizeof *total_buffer);    
    char *src;
    struct timeval never_wait;   
    never_wait.tv_sec = 0;
    never_wait.tv_usec = 0;
    unsigned int srclen;
    char message[8];
    int i;
    int j;
    fd_set read_file_descriptors;
    FD_ZERO(&read_file_descriptors);
    FD_SET(STDIN_FILENO,&read_file_descriptors);     
    if(argc > 1 && strncmp(argv[1],help,3) != 0){
        src=argv[1];
        srclen=strlen(src);
        dest=malloc(srclen*4/3);
        base64_encode((unsigned char*)dest,(unsigned char*)src,srclen);
        printf("%s",dest);
    }
    else if(select(1,&read_file_descriptors,NULL,NULL,&never_wait)){
        int read_bytes=0;
        int read_status;
        size_t len=0;
        read_status = getline(&src_buffer, &len, stdin);    
        while (read_status >= 0){
            //this should work as I did 100K iterations in bash with random data and it worked everytime
            for(i=read_bytes;i<len;i++){
                total_buffer[i]=src_buffer[j++];
            }
            read_bytes+=read_status;            


            read_status = getline(&src_buffer, &len, stdin);
        }
        base64_encode(dest,src,read_bytes);
        printf("%s",dest);
    }
    else{
        printf("%s","If no arguments given it reads from stdin until the first newline character. It's not meant to read entire lines of text so it's only compatible with \n echo -n <string> | base64\n or printf '%s' <string> | base64 \n");
    }
    return 0;
}
