#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/**
* The basic C Program that they're going to be passing the string to get the flag
* for the vim level.
* Macathur Inbody <mdi2455@email.vccs.edu>
* 2019-
* AGPLv3 or Later
*/

int main(int argc, char **argv){
    char *correct_string=malloc(8);
    correct_string="ge4uocti";
    //correct_string="12345678";
    char *flag_string="The flag is ";    
    char *flag=malloc(28);
    //char *false_flag0=malloc(28);
   // char *false_flag1=malloc(28);
    //flag="ABCDEFGHIJKLMNO";
    flag="d88p9gjz4f9bpe75a3febhaucq9cgjw5";
    
    /*
    * This whole if else if thing is a hacky thing to avoid declaring another variable and
    * having nested loops.
    */
    
    if( argc > 2 ){
        printf("The program only takes one argument.\n");
    }
    else if(argc == 1 ){
        printf("No arguments given. \nStandard operation is %s <STRING>\n",argv[0]);
    }
    else if(! strncmp(correct_string,argv[1],8) ){
        printf("\n%s %s\n",flag_string,flag);
    }
    else{
        printf("Sorry you have given me the wrong string.\n");
    }
    return 0;
}
