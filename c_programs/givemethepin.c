#include <stdio.h>
#include <stdlib.h>
#include <stropts.h>
#include <string.h>
#include <unistd.h>
/**
* The basic C Program that they're going to be brute forcing.
*
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
return 0;
}
int main(int argc, char **argv){
char correct_pin_string[]="MTUw";
char *flag_string="The flag is ";
char flag[]="-vGvr4t.3xrfx-M56kZg5f-HyUw";
if(argc > 1){
printf("This program doesn't take arguments.\n");
return -1;
}
size_t len;
int bytes=0;
int read=0;
int str_compared=0;
int return_value=0;
    fd_set read_file_descriptors;
    FD_ZERO(&read_file_descriptors);
    
    struct timeval never_wait;
    never_wait.tv_sec = 0;
    never_wait.tv_usec = 0;
    char flag_msg[41];
    sprintf(flag_msg,"%s%s",flag_string,flag);
    char message[8];
    FD_SET(STDIN_FILENO,&read_file_descriptors);
if(select(1,&read_file_descriptors,NULL,NULL,&never_wait)){
    scanf("%s",message);
    str_compared=strcmp(correct_pin_string,message);
    if(str_compared == 0){
    fprintf(stderr,flag_msg);
    fprintf(stdout,"The flmJ3nmx7QbBUtB3kNw6RS1Yb56RE6D3iW85nt6oUZeyFFrtDwsg3SEw\n");
    }
    else{
    fprintf(stderr,"The pin you've entered is incorrect.\nPlease try again.\n");
    }
    return_value=0;
    }
else{
//printf("ioctl :%d \n",bytes);
fprintf(stderr,"Nothing given.\n");
return_value=-1;
}
return return_value;
}
