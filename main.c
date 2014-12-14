//
//  main.c
//  Dictionary
//
//  Created by dikov on 06/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "briandais.h"
#include "hybrid.h"

#define MAX_LINE_LENGTH 50

int main(int argc, const char * argv[]) {
    
    
    char* file_path = "input.txt"; /* insert full path to input file here */
    
    FILE* ifp = fopen(file_path, "r");
    if(!ifp){
        perror("ERROR");
    }
    char buffer[MAX_LINE_LENGTH];
    
    printf("****** BEGIN - BRIANDAIS *******\n");
    
    //Initialise time mesurement
    
    struct timeval tv1, tv2;
    long long begin, end;
    
    Briandais trie_b = NULL;
    //all tests has been executed with the complete shakespear works.
    
    /* Inserts about 900 000 words in the trie (about 23 000 are unique) */
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_b = insert_word_briandais(trie_b, buffer);
    }
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Insertion Shakespeare.txt: %lld ms\n", (end-begin)/1000);
    
    if(trie_b == NULL){
        puts("s");
    }
    
    /* Looks-up all 900 000 words in the trie. Should not print a word that has not been found */
    
    rewind(ifp);
    char* test_input = malloc(40*sizeof(char));
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    while (fscanf(ifp, "%s", test_input) != EOF) {
        if (!is_word_contained_briandais(trie_b, test_input)) {
            printf("Missing word: %s\n", test_input);
        }
    }
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Look-up Shakespeare.txt: %lld ms\n", (end-begin)/1000);
    
    
    
    /* Finds the height of the trie */
    int height;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    height = height_briandais(trie_b);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Height Briandais: %d. Calculated in: %lld us\n", height, (end-begin));
    
    /* Finds the mean height of the trie */
    float mean_height;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    mean_height = mean_depth_briandais(trie_b);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Mean height Briandais: %f. Calculated in: %lld ms\n", mean_height, (end-begin)/1000);
    
    /* Counts the number of Null pointers */
    int null_pts;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    null_pts = null_pointers_count_briandais(trie_b);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("NULL pointers Briandais: %d. Calculated in: %lld us\n", null_pts, (end-begin));
    
    /* Counts the number of words */
    int words;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    words = word_count_briandais(trie_b);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Word count Briandais: %d. Calculated in: %lld us\n", words, (end-begin));
    
    /* Prefix count briandais. Running Time = mean value of 5 measurements */
    int pc1, pc2, pc3, pc4;
    char* p1 = "wo";
    char* p2 = "th";
    char* p3 = "some";
    char* p4 = "e";
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    pc1 = prefix_count_briandais(trie_b, p1);
    pc2 = prefix_count_briandais(trie_b, p2);
    pc3 = prefix_count_briandais(trie_b, p3);
    pc4 = prefix_count_briandais(trie_b, p4);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("%d pref. of %s, %d pref. of %s, %d pref. of %s, %d pref. of %s. Calculated in: %lld us\n",
           pc1, p1, pc2, p2, pc3, p3, pc4, p4, (end-begin)/4);
    
    /* transforming to an ordered list. Works great, so no need to print it. */
    
    List list_b;
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    list_b = ordered_list_briandais(trie_b);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    print_list(list_b);
    
    printf("Ordered list Shakespear.txt: %lld ms\n", (end-begin)/1000);
    
    /* Merges two big briandais - about 45 000 words any */
    
    char* file_path_fst = "biginput_fst.txt";
    char* file_path_snd = "biginput_snd.txt";
    
    FILE* ifp2 = fopen(file_path_fst, "r");
    if(!ifp){
        perror("ERROR");
    }
    char buffer2[MAX_LINE_LENGTH];
    
    FILE* ifp3 = fopen(file_path_snd, "r");
    if(!ifp){
        perror("ERROR");
    }
    char buffer3[MAX_LINE_LENGTH];
    
    Briandais trie_b_fst = NULL;
    Briandais trie_b_snd = NULL;
    
    while (fscanf(ifp2, "%s", buffer2) != EOF) {
        trie_b_fst = insert_word_briandais(trie_b_fst, buffer);
    }
    
    while (fscanf(ifp3, "%s", buffer3) != EOF) {
        trie_b_snd = insert_word_briandais(trie_b_snd, buffer);
    }
    
    Briandais trie_b_merged = NULL;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    trie_b_merged = merge_briandais(trie_b_fst, trie_b_snd);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Merged half+half Shakespear.txt: %lld us\n", (end-begin));
    
    /* Deletes all the 900 000 words from the trie. Notice that only 23 000 are unique. */

    rewind(ifp);

    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;

    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_b = delete_word_briandais(trie_b, buffer);
    }

    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;

    printf("Delete Shakespeare.txt: %lld us\n", (end-begin));
    
    printf("****** END - BRIANDAIS *******\n");
    
    
    printf("****** BEGIN - HYBRID *******\n");
    
    Hybrid trie_h = NULL;
    
    /* Inserts about 900 000 words in the trie (about 23 000 are unique) */
    
    rewind(ifp);
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_h = insert_word_hybrid(trie_h, buffer);
    }
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Insertion Shakespeare.txt: %lld ms\n", (end-begin)/1000);
    
    /* Looks-up all 900 000 words in the trie. Should not print a word that has not been found */
    
    rewind(ifp);
    char* test_input2 = malloc(40*sizeof(char));
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    while (fscanf(ifp, "%s", test_input2) != EOF) {
        if (!is_word_contained_hybrid(trie_h, test_input2)) {
            printf("Missing word: %s\n", test_input2);
        }
    }
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Look-up Shakespeare.txt: %lld ms\n", (end-begin)/1000);
    
    /* Finds the height of the trie */
    int height2;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    height2 = height_hybrid(trie_h);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Height Hybrid: %d. Calculated in: %lld ms\n", height2, (end-begin)/1000);
    
    /* Finds the mean height of the trie */
    float mean_height2;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    mean_height2 = mean_depth_hybrid(trie_h);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Mean height Hybrid: %f. Calculated in: %lld ms\n", mean_height2, (end-begin)/1000);
    
    /* Counts the number of Null pointers */
    int null_pts2;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    null_pts2 = null_pointers_count_hybrid(trie_h);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("NULL pointers Hybrid: %d. Calculated in: %lld ms\n", null_pts2, (end-begin)/1000);
    
    /* Counts the number of words */
    int words2;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    words2 = word_count_hybrid(trie_h);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Word count Hybrid: %d. Calculated in: %lld ms\n", words2, (end-begin)/1000);
    
    /* Prefix count briandais. Running Time = mean value of 5 measurements. Note that we are using the same prefixes as for the Briandais */
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    pc1 = prefix_count_hybrid(trie_h, p1);
    pc2 = prefix_count_hybrid(trie_h, p2);
    pc3 = prefix_count_hybrid(trie_h, p3);
    pc4 = prefix_count_hybrid(trie_h, p4);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("%d pref. of %s, %d pref. of %s, %d pref. of %s, %d pref. of %s. Calculated in: %lld us\n",
           pc1, p1, pc2, p2, pc3, p3, pc4, p4, (end-begin));
    
    /* transforming to an ordered list. Works great, so no need to print it. */
    
    List list_h;
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    list_h = ordered_list_hybrid(trie_h);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Ordered list Shakespear.txt: %lld ms\n", (end-begin)/1000);
    
    /* Merges two big hybrids - about 45 000 words any */
    
    
    rewind(ifp2);
    memset(buffer2, 0, MAX_LINE_LENGTH);
    
    rewind(ifp3);
    memset(buffer3, 0, MAX_LINE_LENGTH);
    
    Hybrid trie_h_fst = NULL;
    Hybrid trie_h_snd = NULL;
    
    while (fscanf(ifp2, "%s", buffer2) != EOF) {
        trie_h_fst = insert_word_hybrid(trie_h_fst, buffer);
    }
    
    while (fscanf(ifp3, "%s", buffer3) != EOF) {
        trie_h_snd = insert_word_hybrid(trie_h_snd, buffer);
    }
    
    Hybrid trie_h_merged = NULL;
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    trie_h_merged = merge_hybrid(trie_h_fst, trie_h_snd);
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Merged half+half Shakespear.txt: %lld ms\n", (end-begin)/1000);
    
    /* Deletes all the 900 000 words from the trie. Notice that only 23 000 are unique. */
    
    rewind(ifp);
    
    gettimeofday(&tv1, NULL);
    begin = tv1.tv_usec;
    
    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_h = delete_word_hybrid(trie_h, buffer);
    }
    
    gettimeofday(&tv2, NULL);
    end = tv2.tv_usec;
    
    printf("Delete Shakespeare.txt: %lld ms\n", (end-begin)/1000);
    
    printf("****** END - HYBRID *******\n");
    
    fclose(ifp);
    fclose(ifp2);
    fclose(ifp3);
    
    return 0;
}

















