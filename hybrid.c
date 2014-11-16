//
//  hybrid.c
//  Dictionary
//
//  Created by dikov on 10/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#include <stdlib.h>
#include "list.h"
#include "hybrid.h"

struct TernaryTrie{
    char letter;
    int value;
    struct TernaryTrie* inf;
    struct TernaryTrie* eq;
    struct TernaryTrie* sup;
};

struct TernaryTrie* create_empty_node_hyb(){
    struct TernaryTrie* trie = malloc(sizeof(struct TernaryTrie));
    trie->letter = '\0';
    trie->value = -1;
    trie->inf = trie->sup = trie->eq = NULL;
    return trie;
}

struct TernaryTrie* create_empty_hybrid(){
    return create_empty_node_hyb();
}

struct TernaryTrie* create_node_hyb(char letter, int value){
    struct TernaryTrie* trie = malloc(sizeof(struct TernaryTrie));
    trie->letter = letter;
    trie->value = value;
    trie->inf = trie->sup = trie->eq = NULL;
    return trie;
}

struct TernaryTrie* create_hybrid(char letter, int value, struct TernaryTrie* inf, struct TernaryTrie* eq, struct TernaryTrie* sup){
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

char get_letter_hyb(struct TernaryTrie* trie){
    if (trie != NULL) {
        return trie->letter;
    }
    return '\0';
}

int get_value_hyb(struct TernaryTrie* trie){
    if (trie != NULL) {
        return trie->value;
    }
    return -1;
}

bool is_word_contained_hybrid(struct TernaryTrie* trie, char* word){
    if (word[0] == '\0' &&
        get_value_hyb(trie) >= 0) {
        return true;
    }
    if (is_empty_hybrid(trie)) {
        return false;
    }
    if (word[0] == trie->letter) {
        return is_word_contained_hybrid(trie->eq, ++word);
    }
    if (word[0] > trie->letter) {
        return is_word_contained_hybrid(trie->sup, ++word);
    }
    return is_word_contained_hybrid(trie->inf, ++word);
}

//struct TernaryTrie* insert_word_hybrid(struct TernaryTrie* trie, char* new_word, int value){
//    if (new_word[0] == '\0') {
//        return trie;
//    }
//    if (is_empty_hybrid(trie)) {
//        if(new_word[1] == '\0'){
//            return create_hybrid(new_word[0], value, NULL, NULL, NULL);
//        }
//        return create_hybrid(new_word[0], -1, NULL, insert_word_hybrid(trie->eq, ++new_word, value), NULL);
//    }else{
//        if (new_word[0] < get_letter_hyb(trie)) {
//            return create_hybrid(new_word[0], -1, insert_word_hybrid(trie->inf, new_word, value), NULL, NULL);
//        }
//    }
//}






