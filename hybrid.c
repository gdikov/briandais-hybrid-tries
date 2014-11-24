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
        if (word[1] == '\0' && trie->value >= 0) {
            return true;
        }
        return is_word_contained_hybrid(trie->eq, ++word);
    }
    if (word[0] > trie->letter) {
        return is_word_contained_hybrid(trie->sup, word);
    }
    return is_word_contained_hybrid(trie->inf, word);
}

struct TernaryTrie* insert_word_hybrid(struct TernaryTrie* trie, char* new_word, int value){
    if (trie == NULL && new_word[0] != '\0') {
        trie = create_node_hybrid(new_word[0], -1);
        struct TernaryTrie* head = trie;
        for (int i=1; new_word[i] != '\0'; i++) {
            trie->eq = create_node_hybrid(new_word[i], -1);
            trie = trie->eq;
        }
        trie->value = value;
        return head;
    }
    if (trie == NULL || new_word[0] == '\0') {
        return trie;
    }
    if (new_word[0] < trie->letter) {
        trie->inf = insert_word_hybrid(trie->inf, new_word, value);
        return trie;
    }
    if (new_word[0] > trie->letter) {
        trie->sup = insert_word_hybrid(trie->sup, new_word, value);
        return trie;
    }
    if (new_word[1] == '\0') {
        if (trie->value == -1) {
            trie->value = value;
        }
        return trie;
    }
    trie->eq = insert_word_hybrid(trie->eq, ++new_word, value);
    return trie;
}

int word_count_hybrid(struct TernaryTrie* trie){
    if (trie == NULL) {
        return 0;
    }
    if (trie->inf == NULL && trie->eq == NULL && trie->sup == NULL) {
        return trie->value;
    }
    int max_root, max_sup, max_eq, max_inf;
    max_root = trie->value;
    max_sup = (trie->sup != NULL ? word_count_hybrid(trie->sup) : 0);
    max_eq = (trie->eq != NULL ? word_count_hybrid(trie->eq) : 0);
    max_inf = (trie->inf != NULL ? word_count_hybrid(trie->inf) : 0);
    
    if (max_inf >= max_eq && max_inf >= max_sup) {
        return (max_inf >= max_root ? max_inf : max_root);
    }else if (max_sup >= max_inf && max_sup >= max_eq){
        return (max_sup >= max_root ? max_sup : max_root);
    }else{
        return (max_eq >= max_root ? max_eq : max_root);
    }
}

//TODO

int null_pointers_count_hybrid(Hybrid);

List ordered_list_hybrid(Hybrid);

int height_hybrid(Hybrid);

double mean_depth_hybrid(Hybrid);

int prefix_count_hybrid(Hybrid, char*);

Hybrid merge_hybrid(Hybrid, Hybrid);

Briandais hybrid_to_briandais(Hybrid);







