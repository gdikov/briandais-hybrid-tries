//
//  briandais.c
//  Dictionary
//
//  Created by dikov on 06/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#include <stdlib.h>
#include <string.h>
#include "briandais.h"

#define END_OF_WORD '\0'
#define MAX_WORD_SIZE 40


struct ListOfLists {
    char letter;
    struct ListOfLists* next_member;
    struct ListOfLists* sub_member;
};

struct ListOfLists* create_empty_node_braindais(){
    struct ListOfLists* empty_trie = malloc(sizeof(struct ListOfLists));
    empty_trie->letter      = END_OF_WORD;
    empty_trie->next_member = NULL;
    empty_trie->sub_member  = NULL;
    return empty_trie;
}

//O(1)
struct ListOfLists* create_empty_briandais(){
    struct ListOfLists* empty = create_empty_node_braindais();
    return empty;
}

struct ListOfLists* create_node_braindais(char letter){
    struct ListOfLists* empty_trie = malloc(sizeof(struct ListOfLists));
    empty_trie->letter      = letter;
    empty_trie->next_member = NULL;
    empty_trie->sub_member  = NULL;
    return empty_trie;
}

//O(n), where n is the total number of nodes in the trie
void destroy_briandais(struct ListOfLists* trie){
    if (trie->sub_member != NULL &&
        trie->next_member != NULL) {
        destroy_briandais(trie->next_member);
        destroy_briandais(trie->sub_member);
        free(trie);
        return;
    }
    if (trie->next_member != NULL) {
        destroy_briandais(trie->next_member);
        free(trie);
        return;
    }
    if (trie->sub_member != NULL) {
        destroy_briandais(trie->sub_member);
        free(trie);
        return;
    }
    free(trie);   
}

//O(1)
bool is_empty_briandais(struct ListOfLists* trie){
    if (trie == NULL ||
        (trie != NULL
        && trie->letter == END_OF_WORD
        && trie->next_member == NULL)) {
        return true;
    }
    return false;
}

char get_root_value(struct ListOfLists* trie){
    if (trie != NULL) {
        return trie->letter;
    }
    return END_OF_WORD;
}

void set_root_value(struct ListOfLists* trie, char value){
    if (trie != NULL) {
        trie->letter = value;
    }
}

struct ListOfLists* get_next_member(struct ListOfLists* current){
    if (current != NULL) {
        return current->next_member;
    }
    return NULL;
}

struct ListOfLists* get_sub_member(struct ListOfLists* current){
    if (current != NULL) {
        return current->sub_member;
    }
    return NULL;
}

void set_next_member(struct ListOfLists* current, struct ListOfLists* next){
    if (current != NULL) {
        current->next_member = next;
    }
}

void set_sub_member(struct ListOfLists* current, struct ListOfLists* sub){
    if (current != NULL) {
        current->sub_member = sub;
    }
}


/* 
 * by definition the empty word is contained in any trie, although the trie self should not start with a node
 * containing this empty word. The assumption simplifies also the case, when an empty word should be inserted
 * Complexity: O(m) where m is the length of the looked-up word
 */
 bool is_word_contained_briandais(struct ListOfLists* trie, char* word){
    if (word[0] == '\0' || word[0] == END_OF_WORD) {
        return true;
    }
    for (int i=0; word[i] != '\0'; i++) {
        //reached the end of a list or sth is just wrong woth the trie
        if (is_empty_briandais(trie)) {
            return false;
        }
        //this will be repeated maximum n times, where n is the number of distinct letters in the trie. Consider a case where they all occur in a same level. 
        while (!is_empty_briandais(trie)) {
            //search from beging till the end of the trie-line. If the letter in word is greater the the current letter at a given level, then return false, as the letters are alphabetically ordered
            if (word[i] < trie->letter) {
                return false;
            }
            //letter matched, so continue to search in a deeper node level
            if (word[i] == trie->letter) {
                trie = trie->sub_member;
                break;
            }
            //otherwise the letter in the word is greater than the current and the search continues at the same level
            trie = trie->next_member;
        }
    }
    //word is exhausted so check if the current node marks an end of trie (NULL), an end of the word (END_OF_WORD) or it contains another letter
    if (trie == NULL) {
        return false;
    }
    if (get_root_value(trie) == END_OF_WORD) {
        return true;
    }else{
        //the searched word is prefix from another in the trie
        return false;
    }
}

/*
 * A trie of type (e,0,0) should be considered as a trie containing the empty word and thus the new word
 * will be inserted after it (e,0, new_word). This could happen if one creates an empty trie and than inserts
 * all other words. This should be changed if incorrect!
 * Complexity: O(m) where m is the word length
 */
 struct ListOfLists* insert_word_briandais(struct ListOfLists* trie, char* word){
    //the very first words is being inserted
    if (trie == NULL) {
        if (word[0] == '\0') {
            return trie = create_empty_node_braindais();
        }
        trie = create_node_braindais(*word);
        struct ListOfLists* head = trie;
        for (int i=1; word[i] != '\0'; i++) {
            trie->sub_member = create_node_braindais(word[i]);
            trie = trie->sub_member;
        }
        trie->sub_member = create_empty_node_braindais();
        return head;
    }
    if (*word == '\0') {
        if (get_root_value(trie) == END_OF_WORD) {
            return trie;
        }
        struct ListOfLists* end = create_empty_node_braindais();
        end->next_member = trie;
        return end;
    }
    //trie contains the empty word (normally should not occur, but if the trie is created as an empty one this case is inevitable
    if (is_empty_briandais(trie)) {
        trie->next_member = insert_word_briandais(trie->next_member, word);
        return trie;
    }
    if (*word == trie->letter) {
        trie->sub_member = insert_word_briandais(trie->sub_member, ++word);
        return trie;
    }
    if (*word < trie->letter) {
        struct ListOfLists* new_head = create_node_braindais(*word);
        new_head->sub_member = insert_word_briandais(new_head->sub_member, ++word);
        new_head->next_member = trie;
        return new_head;
    }
    struct ListOfLists* head = trie;
     //previous node stores the "history" of a one node back in the list, so that the pointers could be swapped
    struct ListOfLists* previous = NULL;
    while (*word > trie->letter) {
        if (trie->next_member == NULL) {
            trie->next_member = insert_word_briandais(trie->next_member, word);
            return head;
        }
        previous = trie;
        trie = trie->next_member;
    }
    if (*word == trie->letter) {
        trie->sub_member = insert_word_briandais(trie->sub_member, ++word);
        return head;
    }else{
        previous->next_member = create_node_braindais(*word);
        previous->next_member->next_member = trie;
        previous->next_member->sub_member = insert_word_briandais(previous->next_member->sub_member, ++word);
        return head;
    }
}

/*
 * slightly more complex algorithm, deploying a depth search techniques, removing the letters backwards
 * and thus ensuring that only a sufix will be deleted if prefix of the word is a prefix of another one.
 * Complexity: O(2m) = O(m) where m is the word length
 */
struct ListOfLists* delete_word_briandais(struct ListOfLists* trie, char* word){
    if (word[0] == '\0' || is_empty_briandais(trie)) {
        return trie;
    }
    struct ListOfLists* head = trie;
    struct HistoryStack{
        struct ListOfLists* node;
        bool is_first_in_the_list;
        struct ListOfLists* previous_in_the_list;
    };
    struct HistoryStack** stack_of_node_pointers = malloc(MAX_WORD_SIZE*sizeof(struct HistoryStack));
    int sp = 0;
    struct ListOfLists* one_back_on_the_stack = malloc(sizeof(struct ListOfLists));
    //indicates if a letter is part of list with others or is the only letter and thus the only branch and can be peacefully deleted
    for (int i=sp=0; word[i] != '\0'; i++,sp++) {
        (stack_of_node_pointers[sp]) = malloc(sizeof(struct HistoryStack));
        (stack_of_node_pointers[sp])->previous_in_the_list = NULL;
        if (is_empty_briandais(trie)) {
            return head;
        }
        while (!is_empty_briandais(trie)) {
            if (word[i] < trie->letter) {
                return head;
            }
            if (word[i] == trie->letter) {
                (stack_of_node_pointers[sp])->node = trie;
                if ((stack_of_node_pointers[sp])->previous_in_the_list == NULL) {
                    (stack_of_node_pointers[sp])->is_first_in_the_list = true;
                }else{
                    (stack_of_node_pointers[sp])->is_first_in_the_list = false;
                }
                trie = trie->sub_member;
                break;
            }
            (stack_of_node_pointers[sp])->previous_in_the_list = trie;
            trie = trie->next_member;
            (stack_of_node_pointers[sp])->is_first_in_the_list = false;
            
        }
    }
    if (trie == NULL) {
        return head;
    }
    if (get_root_value(trie) == END_OF_WORD) {
        (stack_of_node_pointers[sp]) = malloc(sizeof(struct HistoryStack));
        (stack_of_node_pointers[sp])->node = trie;
        (stack_of_node_pointers[sp])->previous_in_the_list = NULL;
        (stack_of_node_pointers[sp])->is_first_in_the_list = true;
        while ((stack_of_node_pointers[sp])->node->next_member == NULL &&
               (stack_of_node_pointers[sp])->is_first_in_the_list) {
            if (sp == 0) {
                destroy_briandais(head);
                return head = create_empty_briandais();
            }
            sp--;
            (stack_of_node_pointers[sp])->node->sub_member = NULL;
            free((stack_of_node_pointers[sp+1])->node);
        }
        //in the middle of the list
        if ((stack_of_node_pointers[sp])->node->next_member != NULL &&
            !(stack_of_node_pointers[sp])->is_first_in_the_list) {
            (stack_of_node_pointers[sp])->previous_in_the_list->next_member = (stack_of_node_pointers[sp])->node->next_member;
            free((stack_of_node_pointers[sp])->node);
            return head;
        }
        //at the beginning of the list
        if ((stack_of_node_pointers[sp])->is_first_in_the_list) {
            //the very first letter of the trie should be removed
            if (sp == 0) {
                free((stack_of_node_pointers[sp])->node);
                return head->next_member;
            }
            one_back_on_the_stack = (stack_of_node_pointers[sp-1])->node;
            one_back_on_the_stack->sub_member = (stack_of_node_pointers[sp])->node->next_member;
            free((stack_of_node_pointers[sp])->node);
            return head;
        }
        //end of list
        (stack_of_node_pointers[sp])->previous_in_the_list->next_member = NULL;
        free((stack_of_node_pointers[sp])->node);
        return head;
        
    }
    return head;
}

/* 
 * Complexity: O(n) where n is the total number of nodes in the trie
 */
int word_count_briandais(struct ListOfLists* trie){
    if (trie == NULL) {
        return 0;
    }
    if (get_root_value(trie) == END_OF_WORD) {
        return 1+(word_count_briandais(trie->next_member) + word_count_briandais(trie->sub_member));
    }
    return (word_count_briandais(trie->next_member) + word_count_briandais(trie->sub_member));
}

/*
 * Complexity: O(n) where n is the total number of nodes in the trie
 */
int null_pointers_count_briandais(struct ListOfLists* trie){
    if (trie == NULL) {
        return 1;
    }
    return (null_pointers_count_briandais(trie->next_member) + null_pointers_count_briandais(trie->sub_member));
}

/*
 * Complexity: O(n) where n is the total number of nodes in the trie
 */
int height_briandais(struct ListOfLists* trie){
    int max_height_next, max_height_sub = 0;
    if (is_empty_briandais(trie)) {
        return max_height_next = max_height_sub = 0;
    }
    if ((max_height_next = height_briandais(trie->next_member)) > (max_height_sub = 1 + height_briandais(trie->sub_member))) {
        return max_height_next;
    }else{
        return max_height_sub;
    }
}

/*
 * Assuming that the function won't be called often, the code was ment to be easily understandable. The worse time complexity is not such a bad compromise.
 * Complexity: O(n^2) where n is the total number of nodes in the trie
 */
double mean_depth_briandais(struct ListOfLists* trie){
    int words_trie = word_count_briandais(trie);
    if (is_empty_briandais(trie)) {
        return 0.0;
    }
    int words_next = word_count_briandais(trie->next_member);
    int words_sub = word_count_briandais(trie->sub_member);
    double coefficient_next = words_next/(double)words_trie;
    double coefficient_sub = words_sub/(double)words_trie;
    
    return coefficient_next*mean_depth_briandais(trie->next_member) + coefficient_sub*(1+mean_depth_briandais(trie->sub_member));
}


/*
 * Complexity; O(P) where P is the number of the prefixed words
 */
int prefix_count_briandais(struct ListOfLists* trie, char* prefix){
    //all words start with the empty word
    if (prefix[0] == '\0' || is_empty_briandais(trie)) {
        return word_count_briandais(trie);
    }
    int i = 0;
    for (i=0; prefix[i+1] != '\0'; ++i) {
        if (is_empty_briandais(trie)) {
            return 0;
        }
        while (!is_empty_briandais(trie)) {
            if (prefix[i] < trie->letter){
                return 0;
            }
            if (prefix[i] == trie->letter) {
                trie = trie->sub_member;
                break;
            }
            trie = trie->next_member;
        }
    }
    while (trie != NULL) {
        if (prefix[i] == trie->letter) {
            return word_count_briandais(trie->sub_member);
        }
        trie = trie->next_member;
    }
    return 0;
}



struct ListOfLists* merge_briandais(struct ListOfLists* trie1, struct ListOfLists* trie2){
    if (is_empty_briandais(trie1)) {
        return trie2;
    }
    if (is_empty_briandais(trie2)) {
        return trie1;
    }
    List words_in_trie2 = ordered_list_briandais(trie2);
    while (!is_empty_list(words_in_trie2)) {
        trie1 = insert_word_briandais(trie1, get_word_list(words_in_trie2));
        words_in_trie2 = get_next_list(words_in_trie2);
    }
    return trie1;
}

/*
 * once again, using depth search allows traversing the trie in a manner that the words found are
 * alphabetically ordered
 */
 List ordered_list_briandais(struct ListOfLists* trie){
    if (is_empty_briandais(trie)) {
        return create_empty_list();
    }
    List list = NULL;
    //a stack which stores the pointer to the current trie-node. Popping a word gives an access to the parent node and eventually branching in the next ordered word
    struct ListOfLists** stack_of_nodes = malloc(MAX_WORD_SIZE*sizeof(struct ListOfLists*));
    //sp - stack pointer, pointing to the current node; decreasing means going back in history; increases when a new pointer to a node is being added
    int sp = 0;
    char* word = malloc(MAX_WORD_SIZE*sizeof(char));
    while (1) {
        while (get_root_value(trie) != END_OF_WORD) {
            stack_of_nodes[sp] = trie;
            word[sp] = trie->letter;
            trie = trie->sub_member;
            sp++;
        }
        if (trie->letter == END_OF_WORD && trie->next_member != NULL) {
            stack_of_nodes[sp] = trie;
        }
        //substitute with "complex_insert_word_list(list, word)" if you want an order in wich the word length matters, i.e. a < z < aa < zz < aaa....
        list = simple_insert_word_list(list, word);
        if (is_empty_briandais(trie)) {
            sp--;
        }
        for(;(trie = stack_of_nodes[sp])->next_member == NULL; sp--){
            word[sp] = '\0';
            if (sp == 0) {
                free(word);
                free(stack_of_nodes);
                return list;
            }
        }
        if ((trie = stack_of_nodes[sp])->next_member != NULL) {
            word[sp] = '\0';
            trie = trie->next_member;
        }
    }
}













