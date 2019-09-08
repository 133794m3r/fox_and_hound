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


unsigned int get_least_used_word(unsigned int *prev_selected_words,unsigned int *word_freq,unsigned int num_words,unsigned int seed){
    unsigned int min_index=0;
    unsigned int min_freq=0;
    unsigned int current_freq=0;
    unsigned int i=0;
    unsigned int start_index=0;
    unsigned int j=0;
    if(seed!=0){
        start_index=xor_32(0,num_words,seed);
    }
    else{
        start_index=xor_32(0,num_words,0);
    }
    j=start_index;
    for(i=0;i<=num_words;i++){
        current_freq=word_freq[j];
        if(i==0){
            min_freq=current_freq;
        }
        if(current_freq == 0 ){
            return j;
        }
        if(current_freq <= min_freq){
            min_index=j;
            min_freq=current_freq;
        }

        if( j <num_words ){
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
    unsigned int total_lines=num_lines_file("../dict/hound_dict");
    unsigned int word_freq[4*total_lines];
    memset(word_freq,0,4*total_lines);
    //=calloc(4*total_lines,4);
    unsigned char num_flags=0;
    unsigned int seed=0;
    unsigned char num_words_per_flag=7;
    unsigned int i=0;
    unsigned int j=0;
    unsigned int min_word=0;
    unsigned int prev_selected_words[4*total_lines];
    memset(prev_selected_words,0,4*total_lines);
    if(argc == 1){
        printf("Usage: select_the_flag_array <number_of_flags> optional|<seed>\n");
        return 0;
    }
    else if(argc>=2){
       num_flags=atoi(argv[1]);
    }
    if(argc == 3 ){
        seed=atoi(argv[2]);
    }
    else{
        seed=microtime();
    }

    unsigned int word_array[num_flags][num_words_per_flag];
    unsigned int the_word=0;
    fprintf(stdout,"\r");
    for(j=0;j<=num_flags;j++){
        for(i=0;i<num_words_per_flag;i++){
            min_word=get_least_used_word(prev_selected_words,word_freq,total_lines,seed);
            word_freq[min_word]++;
            //*prev_selected_words[min_word]=*
            prev_selected_words[min_word]++;
            word_array[j][i]=min_word;
        }
    }

    for(j=0;j<=num_flags;j++){
        printf("flag_num:%u\nWORD_ARRAY=(",j);
        //printf("",j);
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

    for(j=0;j<=num_flags;j++){
        //printf("flag_num:%u\nWORD_ARRAY=(",j);
        //printf("",j);
        for(i=0;i<num_words_per_flag;i++){
            //printf("\n%u\n",((j*num_flags)+i));
            //printf("%u,",word_array[(j*num_flags)+(i+4)]);
            the_word=(unsigned int ) word_array[j][i];
            printf("%u",the_word+1);
            if( i <= (num_words_per_flag - 2 )){
                printf(" ");
            }
        }
        printf("\n");
    }
    unsigned int sum=0;
    for(j=0;j<total_lines;j++){
        ///printf("index:%u freq:%u\n",j,word_freq[j]);
        sum+=word_freq[j];
    }
    printf("sum:%u\n",sum);
    printf("seed: %u\n",seed);
    return 0;
}
