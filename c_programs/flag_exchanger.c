#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/**
 *
 */
static inline unsigned char uchar(char chr){ return chr;}

int main(int argc, char **argv){
	if(argc == 1){
		return 0;
	}
	FILE *fp;

	fp = fopen('/tmpdownload/the_flags','r');

}