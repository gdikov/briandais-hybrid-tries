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

#define MAX_LINE_LENGTH 50

int main(int argc, const char * argv[]) {
//    Briandais trie = NULL;
//    Briandais trie2 = NULL;
    
//    char* file_path = "Shakespeare/richardiii.txt";
//    char* file_path = "biginput.txt";
//    char* file_path2 = "in90000.txt";
    
//    FILE* ifp = fopen(file_path, "r");
//    
//    if(!ifp){
//        perror("ERROR");
//    }
//    
//    char buffer[MAX_LINE_LENGTH];
    
//    struct timeval tv1, tv2;
//    gettimeofday(&tv1, NULL);
//    
//    long begin = tv1.tv_usec;
//    
//    while (fscanf(ifp, "%s", buffer) != EOF) {
//        trie = insert_word_briandais(trie, buffer);
//    }
//    fclose(ifp);
//    
//    memset(buffer, 0, MAX_LINE_LENGTH);
//    
//    FILE* ifp2 = fopen(file_path2, "r");
//    
//    if(!ifp2){
//        perror("ERROR");
//    }
//    while (fscanf(ifp2, "%s", buffer) != EOF) {
//        trie = delete_word_briandais(trie, buffer);
//    }
//    fclose(ifp2);
//    rewind(ifp);
//
//    char* user_input = malloc(40*sizeof(char));
//    scanf("%s", user_input);
//    while (strcmp(user_input, "stop")) {
//        if (!is_word_contained_briandais(trie, user_input)) {
//            printf("NO\n");
//            scanf("%s", user_input);
//        }else{
//            printf("YES\n");
//            scanf("%s", user_input);
//        }
//    }
//    
//    
//    char* test_input = malloc(40*sizeof(char));
//    while (fscanf(ifp, "%s", test_input) != EOF) {
//        if (!is_word_contained(trie, test_input)) {
//            printf("Missing word: %s\n", test_input);
//        }
//    }
    
//    printf("Word count: %d\n", word_count(trie));
//
//    printf("NULL pointers: %d\n", null_pointers_count(trie));
//
//    printf("Height: %d\n", height(trie));
    
//    printf("Mean height: %f", mean_depth(trie));
//
//    char* user_input = malloc(40*sizeof(char));
//    scanf("%s", user_input);
//    printf("Prefix of: %d\n", prefix_count(trie, user_input));
    
//    List list = ordered_list_briandais(trie);
    
//    gettimeofday(&tv2, NULL);
//    long end = tv2.tv_usec;
//    
//    printf("Running time: %ld ms\n", (end-begin)/1000);
    
//    Briandais trie3 = merge_briandais(trie, trie2);
    
//    
//    
//    while (fscanf(ifp, "%s", buffer) != EOF) {
//        delete_word_briandais(trie, buffer);
//    }
//    
//    destroy_briandais(trie);
//    fclose(ifp);
    
    return 0;
}















