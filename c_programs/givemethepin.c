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
* Basic base64 encoder.
* t=tuplet aka 3 bytes of data.
* a=first byte.
* b=second byte.
* c=third byte.
* I'm using shifting so that it's a bit faster. also the table is the same as the
* base64 program from bash so that they can actually give it the same thing.
*/
int base64_encode(unsigned char *dest, unsigned char *src, int srclen){
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
/**
* The flag is going to be replaced with the value <pinflag> so that it's more
* easily edited with sed in a future version. Also the correct_pin string will
* similarly be changed too once I make sure that it works to be <correct_pin>
* so that I can sed it away more easily.
* 
*
*/
int main(int argc, char **argv){
    char *correct_pin=malloc(3);
    //correct_pin="111";
    correct_pin="<correct_pin_placeholder>";
    //char correct_pin_string[4]="MTEx";
    char *correct_pin_string=malloc(4);
    char *flag_string="The flag is ";
    char *flag=malloc(28);
    char *incorrect_flag1=malloc(28);
    char *incorrect_flag2=malloc(28);
    
    
    flag="9uusTDCfzE2MbhpT3tc0R9rwG5o";
    incorrect_flag1="Nl5fo2fp3U1AwyPMvwZIj_6FIdg";
    incorrect_flag2="xAWAIn1TsR7EXZsUrX4yr-f_FDI";
    /*
    flag="-vGvr4t.3xrfx-M56kZg5f-HyUw";
    incorrect_flag1="-vGvr4t.3xrfx-M56kZg5f-HyUy";
    incorrect_flag2="-vGvr4t.3xrfx-M56kZg5f-HyUz";        
    */
    if(argc > 1){
        printf("This program doesn't take arguments.\n");
        return -1;
    }
    base64_encode((unsigned char*)correct_pin_string,(unsigned char*)correct_pin,strlen(correct_pin));
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
        str_compared=strncmp(correct_pin_string,message,4);
        if(strlen(message) == 8){
            fprintf(stderr,"You should run it as `echo -n | base64` to make sure that newline isn't included.\n");
            fprintf(stdout,"You should run it as `echo -n | base64` to make sure that newline isn't included.");
        }
        else{
            if(str_compared == 0){
            /**
            * Flag1 will be replaced by string <false_flag1>
            * Flag 2 will be replaced by string <false_flag2>
            * TODO:setup 2 false flags that are changed via the strings.
            * The false flags will just be data read from /dev/urandom that's base64 encoded.
            */
            fprintf(stdout,"The flag is %s\n",incorrect_flag1);
            fprintf(stderr,"%s\n",flag_msg);
            fprintf(stdout,"The flag is %s\n",incorrect_flag2);
            fprintf(stdout,"Which flag is the correct one?\n");
            }
            else{
            fprintf(stderr,"The pin you've entered is incorrect.\nPlease try again.\n");
            }
            return_value=0;
       }
    }
    else{
        fprintf(stderr,"Nothing given.\n");
        return_value=-1;
    }
    return return_value;
}
