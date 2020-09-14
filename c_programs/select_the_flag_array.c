/**
 * A program to create the word arrays for the flag generators.
 *
 * This program will select items for the passwords so that they can more easily get them all the way through.
 * These word arrays are setup so that they can be recreated if new levels are added without having to go back and then
 * redo all of the previous passwords as the old ones won't work anymore.
 *
 * Macathur Inbody <mdi2455@email.vccs.edu> <admin-contact@transcendental.us>
 * 2019-
 * AGPLv3 or Later
*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "xor_rand.c"


unsigned int get_least_used_word(unsigned int *word_freq,unsigned int num_words){
	unsigned int min_index=0;
	unsigned int min_freq=0;
	unsigned int current_freq=0;
	unsigned int i=0;
	unsigned int start_index=0;
	unsigned int j=0;
	start_index=xor_32(0,num_words);
	j=start_index;
	min_freq=word_freq[start_index];
	min_index=j;

	for(i=0;i<=num_words;i++){
		current_freq=word_freq[j];
		if(current_freq == 0 ){
			return j;
		}
		if(current_freq < min_freq){
			min_index=j;
			min_freq=current_freq;
		}
		if( j < num_words ){
			j++;
		}
		else{
			j=0;
		}
	}
	return min_index;
}

unsigned int num_lines_file(char *the_file){
	FILE *fp = fopen(the_file,"r");
	if (!fp){
		fprintf(stderr,"The file was empty or nonexistant");
		return 0;
	}
	size_t len=0;
	char *line=malloc(17);
	unsigned int lines=0;
	while(getline(&line,&len,fp) != -1 ){
		lines++;
	}
	free(line);
	fclose(fp);
	return lines;
}

int main(int argc, char **argv){
	unsigned int total_lines=0;

	//char dictionary[70];
	//calloc(4*total_lines,4);
	unsigned char num_flags=0;
	unsigned char num_words_per_flag=12;
	int i=0;
	unsigned int j=0;
	unsigned int min_word=0;
	unsigned int initial_seed=0;

	if(argc == 1){
		printf("Usage: select_the_flag_array <dictionary_file> <number_of_flags> optional|<seed>\n");
		return 0;
	}
	if(argc >=2 ){
		total_lines=num_lines_file(argv[1]);
		if (total_lines == 0)
			return 1
	}
	if(argc>=3){
	   num_flags=atoi(argv[2]);
	}
	if(argc == 4 ){
		seed_xor32(atoi(argv[3]));
	}
	else{
		seed_xor32(0);
	}
	unsigned int word_freq[4*total_lines+4];
	memset(word_freq,0,4*total_lines+4);
	initial_seed=XOR_32_STATE;
	unsigned int word_array[num_flags][num_words_per_flag];
	unsigned int the_word=0;

	for(j=0;j<num_flags;j++){
		for(i=0;i<num_words_per_flag;i++){
			min_word=get_least_used_word(word_freq,total_lines-1);
			word_freq[min_word]++;
			word_array[j][i]=min_word;
		}
	}
	
	for(j=0;j<=num_flags;j++){
		printf("flag_num:%u\nWORD_ARRAY=(",j);
		for(i=0;i<num_words_per_flag;i++){
			the_word=(unsigned int ) word_array[j][i];
			printf("%u",the_word);
			if( i <= (num_words_per_flag - 2 )){
				printf(" ");
			}
		}
		printf(");\n\n");
	}

	for(j=0;j<=num_flags;j++){
		for(i=0;i<num_words_per_flag;i++){
			the_word=(unsigned int ) word_array[j][i];
			printf("%u",the_word+1);
			if( i <= (num_words_per_flag - 2 )){
				printf(" ");
			}
		}
		printf("\n");
	}
	
	unsigned int sum=0;
	printf("\n");
	for(j=0;j<total_lines;j++){
		printf("%u,",word_freq[j]);
	}
	
	for(j=0;j<total_lines;j++){
		sum+=word_freq[j];
	}
	
	printf("\nsum:%u\n",sum);
	printf("initial seed: %u\n",initial_seed);
	return 0;
}
