#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
/**
* The basic base32 encoder.
* This program encodes either an argument or a file passed to it through a pipe into a
* base32 encoded string.
* Macathur Inbody <mdi2455@email.vccs.edu>
* 2019-
* AGPLv3 or Later
*/

//TODO: Figure out some way to handle NULL input at the front of  stdin buffer.
// the chances of this happening are next to zero but it's still possible.
// This is just a macro like thing to make it a little less to type.
static inline unsigned char uchar(char chr){ return chr;}
/**
* This function encodes a string passed to it as a bas32 string.
*
*/
int base32_encode(char *dest, const char *src, unsigned int srclen, unsigned int outlen){
    const char table[32]="ybndrfg8ejkmcpqxot1uwisza345h769";
    //const char table[32]="ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";
    unsigned int i=0;
    unsigned int j=0;
    unsigned char a=0;
    unsigned char b=0;
    unsigned char c=0;
    unsigned char d=0;
    unsigned char e=0;
  //  unsigned int t=0;
    unsigned char leftover_bytes=(srclen % 5);
    unsigned char replace_bytes=0;
    const char padding[1]="=";
    //unsigned int iters=(srclen / 5);
    while (i < srclen && j< outlen){

        //ternary's are used to save some sloc and b/c I'm lazy.
        a=i < srclen ? uchar(src[i++]) : 0;
        b=i < srclen ? uchar(src[i++]) : 0;
        c=i < srclen ? uchar(src[i++]) : 0;
        d=i < srclen ? uchar(src[i++]) : 0;
        e=i < srclen ? uchar(src[i++]) : 0;
 //       t= (a << 16) + (b << 8) + c;
/*
(a >> 3)
( ((a & 0x07) << 2) | (b >> 6))
( ((b & 0x3F) >> 1) )
( ((b & 0x01) << 4) | (c >> 4))
( ((c & 0x0F) << 1) | (d >> 7))
( ((d & 0x7F) >> 2))
( ((d & 0x03) << 3) | (e >> 5))
( ((e & 0x1F) ))
*/
    dest[j++]=table[(a >> 3)];
    dest[j++]=table[( ((a & 0x07) << 2) | (b >> 6))];
    dest[j++]=table[( ((b & 0x3F) >> 1) )];
    dest[j++]=table[( ((b & 0x01) << 4) | (c >> 4))];
    dest[j++]=table[( ((c & 0x0F) << 1) | (d >> 7))];
    dest[j++]=table[( ((d & 0x7F) >> 2))];
    dest[j++]=table[( ((d & 0x03) << 3) | (e >> 5))];
    dest[j++]=table[( ((e & 0x1F) ))];
    }

    if (leftover_bytes == 1) replace_bytes = 6;
    else if (leftover_bytes == 2) replace_bytes = 4;
    else if (leftover_bytes == 3) replace_bytes = 3;
    else if (leftover_bytes == 4) replace_bytes = 1;
    j--;
    for(i=0;i<replace_bytes;i++){
        dest[j--]=padding[0];
    }
    return 0;
}



int main(int argc,char **argv){
    char *dest=malloc(sizeof *dest);
    char *help="-h";
    char *src;
    int i=0;
    int j=0;
    struct timeval never_wait;
    never_wait.tv_sec = 1;
    never_wait.tv_usec = 5000;
    unsigned int srclen=0;
    unsigned int outlen=0;
    fd_set read_file_descriptors;
    FD_ZERO(&read_file_descriptors);
    FD_SET(STDIN_FILENO,&read_file_descriptors);
    if(argc > 1 && strncmp(argv[1],help,3) != 0){
        src=argv[1];
        srclen=strlen(src);
        outlen=(srclen*8/5);
        outlen=outlen+(8-(outlen % 8 ));
        dest=malloc(outlen);
        base32_encode(dest,src,srclen,outlen);
        printf("%s\n",dest);
    }

    else if(select(1,&read_file_descriptors,NULL,NULL,&never_wait) > 0){
        char *src_buffer=malloc(sizeof *src_buffer);
        char *total_buffer=malloc(sizeof *total_buffer);

        int read_bytes=0;
        int read_status=0;

        size_t len=0;
        //a line of text should never be more than 4KiB.
        src_buffer=malloc(4096);
        //right now we're not allowing them to do more than ~4MiB of total data piped to it.
        total_buffer=malloc(4096*1024);
        read_status = getline(&src_buffer, &len, stdin);
        while (read_status >= 0){
            i=0;
            j=0;
		//this should work as I did 100K iterations in bash with random data and it worked everytime
            for(i=read_bytes;i<len;i++){
                total_buffer[i]=src_buffer[j++];
            }
            read_bytes+=read_status;


            read_status = getline(&src_buffer, &len, stdin);
        }
        //printf("bytes read:%d\n",read_bytes);
        outlen=(read_bytes*8/5);
        outlen=outlen+(8-(outlen % 8 ));
        dest=malloc(outlen);
        base32_encode(dest,total_buffer,read_bytes,outlen);
        printf("%s\n",dest);
    }
    else{
        printf("%s","If no arguments given it reads from stdin until it's at the end. Otherwise it reads the first argument passed to the program as a string to encode.\n");
    }
    return 0;
}

