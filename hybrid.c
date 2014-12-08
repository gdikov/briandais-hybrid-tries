//
//  hybrid.c
//  Dictionary
//
//  Created by dikov on 10/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "hybrid.h"

#define MAX_WORD_SIZE 40

static int WORD_NUMERATOR = 0;

struct TernaryTrie{
    char letter;
    int value;
    struct TernaryTrie* inf;
    struct TernaryTrie* eq;
    struct TernaryTrie* sup;
};

struct TernaryTrie* create_empty_node_hybrid(){
    struct TernaryTrie* trie = malloc(sizeof(struct TernaryTrie));
    trie->letter = '\0';
    trie->value = -1;
    trie->inf = trie->sup = trie->eq = NULL;
    return trie;
}

struct TernaryTrie* create_empty_hybrid(){
    return create_empty_node_hybrid();
}

struct TernaryTrie* create_node_hybrid(char letter, int value){
    struct TernaryTrie* trie = malloc(sizeof(struct TernaryTrie));
    trie->letter = letter;
    trie->value = value;
    trie->inf = trie->sup = trie->eq = NULL;
    return trie;
}

struct TernaryTrie* create_customized_node_hybrid(char letter, int value, struct TernaryTrie* inf, struct TernaryTrie* eq, struct TernaryTrie* sup){
    struct TernaryTrie* trie = malloc(sizeof(struct TernaryTrie*));
    trie->letter = letter;
    trie->value = value;
    trie->inf = inf;
    trie->eq = eq;
    trie->sup = sup;
    return trie;
}

bool is_empty_hybrid(struct TernaryTrie* trie){
    if (trie == NULL ||
        (trie->value == -1 && trie->sup == NULL && trie->inf == NULL && trie->eq == NULL)) {
        return true;
    }
    return false;
}

char get_letter_hybrid(struct TernaryTrie* trie){
    if (trie != NULL) {
        return trie->letter;
    }
    return '\0';
}

int get_value_hybrid(struct TernaryTrie* trie){
    if (trie != NULL) {
        return trie->value;
    }
    return -1;
}

bool is_word_contained_hybrid(struct TernaryTrie* trie, char* word){
    if (word[0] == '\0' &&
        get_value_hybrid(trie) >= 0) {
        return true;
    }
    if (is_empty_hybrid(trie)) {
        return false;
    }
    if (word[0] == trie->letter) {
        if (word[1] == '\0'){
            if (trie->value >= 0) {
                return true;
            }
            return false;
        }
        return is_word_contained_hybrid(trie->eq, ++word);
    }
    if (word[0] > trie->letter) {
        return is_word_contained_hybrid(trie->sup, word);
    }
    return is_word_contained_hybrid(trie->inf, word);
}

struct TernaryTrie* insert_word_hybrid(struct TernaryTrie* trie, char* new_word){
    if (trie == NULL && new_word[0] != '\0') {
        trie = create_node_hybrid(new_word[0], -1);
        struct TernaryTrie* head = trie;
        for (int i=1; new_word[i] != '\0'; i++) {
            trie->eq = create_node_hybrid(new_word[i], -1);
            trie = trie->eq;
        }
        trie->value = WORD_NUMERATOR;
        WORD_NUMERATOR++;
        return head;
    }
    if (trie == NULL || new_word[0] == '\0') {
        return trie;
    }
    if (new_word[0] < trie->letter) {
        trie->inf = insert_word_hybrid(trie->inf, new_word);
        return trie;
    }
    if (new_word[0] > trie->letter) {
        trie->sup = insert_word_hybrid(trie->sup, new_word);
        return trie;
    }
    if (new_word[1] == '\0') {
        if (trie->value == -1) {
            trie->value = WORD_NUMERATOR;
            WORD_NUMERATOR++;
        }
        return trie;
    }
    trie->eq = insert_word_hybrid(trie->eq, ++new_word);
    return trie;
}

//working function but not well constructed, since it searches the max value. Not really counting any words. Nevertheless the performance should be the same. I just kept it here, as it might be useful for sth else.
//int word_count_hybrid(struct TernaryTrie* trie){
//    if (trie == NULL) {
//        return 0;
//    }
//    if (trie->inf == NULL && trie->eq == NULL && trie->sup == NULL) {
//        return trie->value;
//    }
//    int max_root, max_sup, max_eq, max_inf;
//    max_root = trie->value;
//    max_sup = (trie->sup != NULL ? word_count_hybrid(trie->sup) : 0);
//    max_eq = (trie->eq != NULL ? word_count_hybrid(trie->eq) : 0);
//    max_inf = (trie->inf != NULL ? word_count_hybrid(trie->inf) : 0);
//    
//    if (max_inf >= max_eq && max_inf >= max_sup) {
//        return (max_inf >= max_root ? max_inf : max_root);
//    }else if (max_sup >= max_inf && max_sup >= max_eq){
//        return (max_sup >= max_root ? max_sup : max_root);
//    }else{
//        return (max_eq >= max_root ? max_eq : max_root);
//    }
//}

int word_count_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return 0;
    }
    if (trie->value >= 0) {
        return 1 + word_count_hybrid(trie->inf) + word_count_hybrid(trie->eq) + word_count_hybrid(trie->sup);
    }
    return word_count_hybrid(trie->inf) + word_count_hybrid(trie->eq) + word_count_hybrid(trie->sup);
}

int null_pointers_count_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return 1;
    }
    return null_pointers_count_hybrid(trie->inf) + null_pointers_count_hybrid(trie->eq) + null_pointers_count_hybrid(trie->sup);
}


List ordered_list_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return NULL;
    }
    
    char* prefix = malloc(MAX_WORD_SIZE*sizeof(char));
    memset(prefix, 0, MAX_WORD_SIZE);
    int i = 0;
    List sublist = NULL;
    List suffixes = NULL;
    
    if (trie->inf == NULL && trie->sup == NULL) {
        while (trie->inf == NULL && trie->sup == NULL) {
            prefix[i++] = trie->letter;
            if (trie->value >= 0) {
                sublist = simple_insert_word_list(sublist, prefix);
            }
            trie = trie->eq;
            if (trie == NULL) {
                return sublist;
            }
        }
    }
    List suff_inf = ordered_list_hybrid(trie->inf);
    List suff_sup = ordered_list_hybrid(trie->sup);
    
    struct TernaryTrie* trie_inf = trie->inf;
    struct TernaryTrie* trie_sup = trie->sup;
    trie->inf = trie->sup = NULL;
    
    List suff_eq = ordered_list_hybrid(trie);
    
    trie->inf = trie_inf;
    trie->sup = trie_sup;
    
    suffixes = concat_list(suff_inf, suff_eq);
    suffixes = concat_list(suffixes, suff_sup);
    
    char* complete_word = malloc(MAX_WORD_SIZE*sizeof(char));
    memset(complete_word, 0, MAX_WORD_SIZE);
    complete_word = strcpy(complete_word, prefix);
    //iterate over the suffixes and concatenate to build a complete word
    while (suffixes != NULL) {
        sublist = simple_insert_word_list(sublist, strcat(complete_word, get_word_list(suffixes)));
        suffixes = get_next_list(suffixes);
        strcpy(complete_word, prefix);
    }
    free(complete_word);
    free(prefix);
    return sublist;
}

int height_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return 0;
    }
    int max_height_inf, max_height_eq, max_height_sup;
    max_height_inf = 1 + height_hybrid(trie->inf);
    max_height_eq = 1 + height_hybrid(trie->eq);
    max_height_sup = 1 + height_hybrid(trie->sup);
    if (max_height_inf >= max_height_eq && max_height_inf >= max_height_sup) {
        return max_height_inf;
    }
    if (max_height_eq >= max_height_inf && max_height_eq >= max_height_sup) {
        return max_height_eq;
    }
    return max_height_sup;
}

double mean_depth_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return 0.0;
    }
    int words_inf = word_count_hybrid(trie->inf);
    int words_eq = word_count_hybrid(trie->eq);
    int words_sup = word_count_hybrid(trie->sup);
    int words_trie = word_count_hybrid(trie);
    double coefficient_inf = words_inf/(double)words_trie;
    double coefficient_eq = words_eq/(double)words_trie;
    double coefficient_sup = words_sup/(double)words_trie;
    return coefficient_inf*(1+mean_depth_hybrid(trie->inf)) +
        coefficient_eq*(1+mean_depth_hybrid(trie->eq)) +
        coefficient_sup*(1+mean_depth_hybrid(trie->sup));
}

int prefix_count_hybrid(struct TernaryTrie* trie, char* prefix){
    if (prefix[0] == '\0') {
        return word_count_hybrid(trie);
    }
    if (trie == NULL) {
        return 0;
    }
    if (prefix[0] == trie->letter) {
        if (prefix[1] == '\0' && trie->value >= 0) {
            return 1 + word_count_hybrid(trie->eq);
        }
        return prefix_count_hybrid(trie->eq, ++prefix);
    }
    if (prefix[0] > trie->letter) {
        return prefix_count_hybrid(trie->sup, prefix);
    }
    return prefix_count_hybrid(trie->inf, prefix);
}

struct TernaryTrie* merge_hybrid(struct TernaryTrie* trie1, struct TernaryTrie* trie2){
    if (is_empty_hybrid(trie1)) {
        return trie2;
    }
    if (is_empty_hybrid(trie2)) {
        return trie1;
    }
    int wt1 = word_count_hybrid(trie1);
    int wt2 = word_count_hybrid(trie2);
    if (wt1 <= wt2) {
        List list1 = ordered_list_hybrid(trie1);
        while (list1 != NULL) {
            trie2 = insert_word_hybrid(trie2, get_word_list(list1));
            list1 = get_next_list(list1);
        }
        return trie2;
    }else{
        List list2 = ordered_list_hybrid(trie2);
        while (list2 != NULL) {
            trie1 = insert_word_hybrid(trie1, get_word_list(list2));
            list2 = get_next_list(list2);
        }
        return trie1;
    }
}

struct TernaryTrie* delete_word_hybrid(struct TernaryTrie* trie, char* word){
    if (word[0] == '\0' &&
        get_value_hybrid(trie) >= 0) {
        trie->value = -1;
        return trie;
    }
    if (is_empty_hybrid(trie)) {
        return trie;
    }
    if (word[0] == trie->letter) {
        if (word[1] == '\0'){
            if (trie->value >= 0) {
                trie->value = -1;
                return trie;
            }
            return trie;
        }
        return delete_word_hybrid(trie->eq, ++word);
    }
    if (word[0] > trie->letter) {
        return delete_word_hybrid(trie->sup, word);
    }
    return delete_word_hybrid(trie->inf, word);
}





