#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "xor_rand.c"
/**
* The basic C Program that they're going to be brute forcing the pin from.
* Macathur Inbody <mdi2455@email.vccs.edu>
* 2019-
* AGPLv3 or Later
*/

unsigned int get_least_used_word(unsigned int *prev_selected_words,unsigned int *word_freq,unsigned int num_words){
    unsigned int min_index=0;
    unsigned int min_freq=0;
    unsigned int current_freq=0;
    unsigned int i=0;
    unsigned int start_index=xor_32(0,num_words);
    unsigned int j=start_index;
    for(i=0;i<=num_words;i++){
        current_freq=word_freq[j];
        if(j==0){
            min_freq=current_freq;
        }
        if(current_freq == 0 ){
            return j;
        }
        if( (current_freq <= min_freq)){
            min_index=j;
            min_freq=current_freq;
        }
        j++;
        if( j>num_words ){
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
    char *line=malloc(8);
    unsigned int lines=0;
    while(getline(&line,&len,fp) != -1 ){
        lines++;
    }
    free(line);
    fclose(fp);
    return lines;
}

int main(int argc, char **argv){
    unsigned int total_lines=num_lines_file("../dict/hound_dict");
    unsigned int *word_freq=malloc(4*total_lines);
    memset(word_freq,0,4*total_lines);
    unsigned char num_flags=17;
    unsigned char num_words_per_flag=7;
    unsigned int i=0;
    unsigned int j=0;
    unsigned int min_word=0;
    unsigned int *prev_selected_words=malloc(total_lines);
    unsigned int word_array[num_flags][num_words_per_flag];
    fprintf(stdout,"\r");
    for(j=0;j<=num_flags;j++){
        for(i=0;i<num_words_per_flag;i++){
            min_word=get_least_used_word(prev_selected_words,word_freq,total_lines);
            word_freq[min_word]+=1;
            prev_selected_words[min_word]+=1;
            word_array[j][i]=min_word;
        }
    }

unsigned int the_word=0;
    for(j=0;j<=num_flags;j++){
        printf("flag_num:%u WORD_ARRAY=(",j);
        for(i=0;i<num_words_per_flag;i++){
            //printf("\n%u\n",((j*num_flags)+i));
            //printf("%u,",word_array[(j*num_flags)+(i+4)]);
            the_word=(unsigned int ) word_array[j][i];
            printf("%u",the_word);
            if( i <= (num_words_per_flag - 2 )){
                printf(" ");
            }
        }
        printf(")\n");
    }
    return 0;
}
