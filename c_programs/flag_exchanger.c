#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>

/**
 *
 */
static inline unsigned char uchar(char chr){ return chr;}
void print_help(char *fname){
	fprintf(stdout,"Usage: %s -h| -u <LEVEL> -s <SECRET_STRING>\n-h=show this help string. -u <LEVEL> The level that the secret string was generated for. So for hound0 it'd be '0'.\n-s <SECRET_STRING> This is the 5-6 character string you were given upon getting the flag.\n After giving both parameters to this program it will return back to you the password to the username that you've specified if your token matches the stored one.",fname);
}
int main(int argc, char **argv){
	char secret[6] = {0,0,0,0,0,0};
	int level = 0;
	if(argc == 1){
		print_help(argv[0]);
		return 0;
	}
	else{
		int option;
		while((option = getopt(argc,argv,":hu:s:"))!= -1){
			switch(option){
				case 'h':
					print_help(argv[0]);
					return 0;

				case 'u':
					if(!optarg){
						fprintf(stderr,"Option '-u' requires an argument.\n");
						return 1;
					}
					else{
						level = atoi(optarg);
						if(level <0 || level > 19){
							fprintf(stderr,"A challenge doesn't exist for level:%d\n",level);
							return 1;
						}
					}
					break;
				case 's':
					if(!optarg){
						fprintf(stderr,"Option '-s' requires an argument.\n");
						return 1;
					}
					else{
						if(*optarg == '\0' || strlen(optarg) <= 4 || strlen(optarg) >= 7){
							fprintf(stderr,"The secret string is always either 5 or 6 characters long. Not '%lu' characters long.\n",strlen(optarg));
							return 1;
						}
						snprintf(secret,6,"%s",optarg);
					}
					break;
				case '?':
					//if they did -n then it needs an argument not another option.
					if (optopt == 's' || optopt == 'u'){
						fprintf(stderr,"Option '-%c' requires an argument.\n",optopt);
					}
						//if we have an unknown option print that info.
					else if(isprint(optopt)){
						fprintf(stderr,"Unknown option '-%c'\n",optopt);
					}
					else{
						//otherwise print this as it's no a printable character.
						//we print the hex code point.
						fprintf(stderr,"Unknown option character \\x%x\n",optopt);
					}
					//return 1 because it wasn't normal/correct.
					return 1;
				default:
					printf("opt:%d optopt:%d\n",option,optopt);
					break;
			}
		}
	}

	FILE *fp;
	if(secret[0] == '\0'){
		fprintf(stderr,"Program requires the secret string.");
		return 2;
	}
	//this directory will actually
	fp = fopen("/tmpdownload/the_flags.txt","r");

	unsigned int  seek_pad = 0;
	if(level <= 9){
		seek_pad += (level <= 8)?7:8;
		seek_pad += (level*40);
	}
	else{
		seek_pad = (9*40)+((level-9)*41) + 8;
	}
	fseek(fp,seek_pad,SEEK_SET);
	char flag[33];
	fgets(flag,33,fp);

	if(strncmp(flag,secret,5) == 0){
		fprintf(stdout,"%s\n",flag);
	}
	else{
		fprintf(stderr,"The secret string you entered was incorrect. The string '%s' is not a valid secret string.",secret);
	}
}