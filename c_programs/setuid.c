#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
/**
* A super simple setuid program.
* This program lets them to run a program as another user. The compiled binary will have
* it's suid and sgid bits set to houndxx+1. 
* Then the compiled binary will be named houndxx_do.
* base32 encoded string.
* Macathur Inbody <mdi2455@email.vccs.edu>
* 2019-
* AGPLv3 or Later
*/
int main(int argc,char **argv){
    char command[80];
    int realid=getuid();
    setuid(geteuid());
    if ((argc >= 2) && (argv[1] == "rm" | argv[1] == "rmdir" )){
        printf("We're not going to let you delete files!\n");
        return -1;
    }

    switch(argc){
        case 2:
            snprintf(command,6,"%s %s",argv[1],argv[2]);
            system(command);
        break;
        case 3     
            sprintf(command,"%s %s",argv[1],argv[2]);
            system(command);
        break;
        default:
            printf("Usage: ./setuid <COMMAND1> <COMMANDn>\n");
        break;
    }
    setuid(realid);
    return 0;
 }
