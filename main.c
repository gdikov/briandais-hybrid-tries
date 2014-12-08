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

    
    Briandais trie_b = NULL;
    Hybrid trie_h = NULL;
    char* file_path = "input.txt";
    
    FILE* ifp = fopen(file_path, "r");
    
    if(!ifp){
        perror("ERROR");
    }
    
    char buffer[MAX_LINE_LENGTH];
//    
//    while (fscanf(ifp, "%s", buffer) != EOF) {
//        trie_b = insert_word_briandais(trie_b, buffer);
//    }
//

    
//    if (is_word_contained_briandais(trie_b, "wonderfully")) {
//        puts("y");
//    }else{
//        puts("n");
//    }
    
//    rewind(ifp);
//

//    
    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_h = insert_word_hybrid(trie_h, buffer);
    }
    
//    struct timeval tv1, tv2;
//    gettimeofday(&tv1, NULL);
//    long long begin = tv1.tv_usec;
//
//    memset(buffer, 0, MAX_LINE_LENGTH);
//
//    FILE* ifp2 = fopen(file_path2, "r");
//    
//    if(!ifp2){
//        perror("ERROR");
//    }
    rewind(ifp);
    while (fscanf(ifp, "%s", buffer) != EOF) {
        trie_h = delete_word_hybrid(trie_h, buffer);
    }
//    fclose(ifp2);
//    rewind(ifp);
//
//    char* user_input = malloc(40*sizeof(char));
//    scanf("%s", user_input);
//    while (strcmp(user_input, "stop")) {
//        if (!is_word_contained_hybrid(trie, user_input)) {
//            printf("NO\n");
//            scanf("%s", user_input);
//        }else{
//            printf("YES\n");
//            scanf("%s", user_input);
//        }
//    }
//
//
//    rewind(ifp);
    char* test_input = malloc(40*sizeof(char));
//    while (fscanf(ifp, "%s", test_input) != EOF) {
//        if (!is_word_contained_briandais(trie_b, test_input)) {
//            printf("Badly constructed trie Briandais!!: %s\n", test_input);
//        }
//    }
//
    rewind(ifp);
    while (fscanf(ifp, "%s", test_input) != EOF) {
        if (!is_word_contained_hybrid(trie_h, test_input)) {
            printf("Badly constructed trie Hybrid!!: %s\n", test_input);
        }
    }
    

//    printf("Word count Briandais: %d\n", word_count_briandais(trie_b));
//    printf("Word count Hybird: %d\n", word_count_hybrid(trie_h));
//
//    printf("NULL pointers Briandais: %d\n", null_pointers_count_briandais(trie_b));
//    printf("NULL pointers Hybrid: %d\n", null_pointers_count_hybrid(trie_h));
//
//    printf("Height Briandais: %d\n", height_briandais(trie_b));
//    printf("Height Hybrid: %d\n", height_hybrid(trie_h));
//
//    printf("Mean height Briandais: %f\n", mean_depth_briandais(trie_b));
//    printf("Mean height Hybrid: %f\n", mean_depth_hybrid(trie_h));

//    char* user_input = malloc(40*sizeof(char));
//    scanf("%s", user_input);
//    printf("Prefix of Hybrid: %d\n", prefix_count_hybrid(trie_h, "wond"));
//    printf("Prefix of Briandais: %d\n", prefix_count_briandais(trie_b, "wond"));
//    printf("%s\n", is_word_contained_briandais(trie_b, "10")? "yep" : "nope");
//    List list_b = ordered_list_briandais(trie_b);
//    List list_h = ordered_list_hybrid(trie_h);
//
//    List head = list_b;
//
//    
//    rewind(ifp);
//    list_b = head;
//    char* test_input = malloc(40*sizeof(char));
//    while (fscanf(ifp, "%s", test_input) != EOF) {
//        if (!is_word_contained_list(list_b, test_input)) {
//            printf("Missing word: %s\n", test_input);
//        }
//    }
    
    
//    while (list_b != NULL) {
//        if (!is_word_contained_briandais(trie_b, get_word_list(list_b))) {
//            printf("Badly constructed list Briandais!! : %s\n", get_word_list(list_b));
//        }
//        list_b = get_next_list(list_b);
//    }
//    print_list(head);
    
//    List list_h = ordered_list_hybrid(trie_h);
//    head = list_h;
//    while (list_h != NULL) {
//        if (!is_word_contained_hybrid(trie_h, get_word_list(list_h))) {
//            printf("Badly constructed list Hybrid!! : %s\n", get_word_list(list_h));
//        }
//        list_h = get_next_list(list_h);
//    }
//    print_list(head);
    
    
//
//    print_list(list);
//
//    gettimeofday(&tv2, NULL);
//    long long end = tv2.tv_usec;
//    printf("Running time: %lld us\n", (end-begin));
    
//    Briandais trie3 = merge_briandais(trie, trie2);
    
//    
//    
//    while (fscanf(ifp, "%s", buffer) != EOF) {
//        delete_word_briandais(trie, buffer);
//    }
//    
//    destroy_briandais(trie_b);

    fclose(ifp);
    
    return 0;
}















