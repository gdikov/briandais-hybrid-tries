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

#define END_OF_WORD '$'
#define MAX_WORD_SIZE 40

/*
 * The data structure - Briandais trie - is represented as a multidimensional list, in other words
 * a list of lists recursively defined. The char letter argument could be easily? replaced
 * by a more generic one, such as void* data.
 */
struct ListOfLists {
    char letter;
    struct ListOfLists* next_member;
    struct ListOfLists* sub_member;
};
/*
 * Some constructors and destructors
 */
struct ListOfLists* create_empty_member(){
    struct ListOfLists* empty_trie = malloc(sizeof(struct ListOfLists));
    empty_trie->letter      = END_OF_WORD;
    empty_trie->next_member = NULL;
    empty_trie->sub_member  = NULL;
    return empty_trie;
}

struct ListOfLists* create_empty_briandais(){
    struct ListOfLists* empty = create_empty_member();
    return empty;
}

struct ListOfLists* create_member(char letter){
    struct ListOfLists* empty_trie = malloc(sizeof(struct ListOfLists));
    empty_trie->letter      = letter;
    empty_trie->next_member = NULL;
    empty_trie->sub_member  = NULL;
    return empty_trie;
}

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

/*
 * Some basic functions, along with the getters and setters
 */
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

//
// by definition the empty word is contained even in any trie. This simplifies the case, when an empty word should be inserted
bool is_word_contained_briandais(struct ListOfLists* trie, char* word){
    if (word[0] == '\0' || word[0] == END_OF_WORD) {
        return true;
    }
    for (int i=0; word[i] != '\0'; i++) {
        //search from beging till the end of the trie-line. If the letter in word is greater the the current trie-line letter, then return false, as the letters are alphabetically ordered
        //reached the end of trie-line and the letter not found
        if (is_empty_briandais(trie)) {
            return false;
        }
        while (!is_empty_briandais(trie)) {
            if (word[i] < trie->letter) {
                return false;
            }
            //letter matched, so continue to search in a deeper trie-line level
            if (word[i] == trie->letter) {
                trie = trie->sub_member;
                break;
            }
            trie = trie->next_member;
        }
    }
    //word exhausted and symbol in trie marks the end
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

//insertion in a non-empty trie - presuming that a trie of type (e,0,0) should be considered as a trie containing the empty word
struct ListOfLists* insert_word_briandais(struct ListOfLists* trie, char* word){
    if (trie == NULL) {
        if (word[0] == '\0') {
            return trie = create_empty_member();
        }
        trie = create_member(*word);
        struct ListOfLists* head = trie;
        for (int i=1; word[i] != '\0'; i++) {
            trie->sub_member = create_member(word[i]);
            trie = trie->sub_member;
        }
        trie->sub_member = create_empty_member();
        return head;
    }
    if (*word == '\0') {
        if (get_root_value(trie) == END_OF_WORD) {
            return trie;
        }
        struct ListOfLists* end = create_empty_member();
        end->next_member = trie;
        return end;
    }
    //trie containing the empty word, so insert a new one and preserve this
    if (is_empty_briandais(trie)) {
        trie->next_member = insert_word_briandais(trie->next_member, word);
        return trie;
    }
    if (*word == trie->letter) {
        trie->sub_member = insert_word_briandais(trie->sub_member, ++word);
        return trie;
    }
    if (*word < trie->letter) {
        struct ListOfLists* new_head = create_member(*word);
        new_head->sub_member = insert_word_briandais(new_head->sub_member, ++word);
        new_head->next_member = trie;
        return new_head;
    }
    struct ListOfLists* head = trie;
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
        previous->next_member = create_member(*word);
        previous->next_member->next_member = trie;
        previous->next_member->sub_member = insert_word_briandais(previous->next_member->sub_member, ++word);
        return head;
    }
}

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
        (stack_of_node_pointers[sp]) = malloc(2*sizeof(struct ListOfLists*)+sizeof(bool));
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
        (stack_of_node_pointers[sp]) = malloc(2*sizeof(struct ListOfLists*)+sizeof(bool));
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
        if ((stack_of_node_pointers[sp])->is_first_in_the_list) {
            //the very first letter should be removed
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

int word_count(struct ListOfLists* trie){
    if (trie == NULL) {
        return 0;
    }
    if (get_root_value(trie) == END_OF_WORD) {
        return 1+(word_count(trie->next_member) + word_count(trie->sub_member));
    }
    return (word_count(trie->next_member) + word_count(trie->sub_member));
}

int null_pointers_count(struct ListOfLists* trie){
    if (trie == NULL) {
        return 1;
    }
    return (null_pointers_count(trie->next_member) + null_pointers_count(trie->sub_member));
}

int height(struct ListOfLists* trie){
    int max_height_next, max_height_sub = 0;
    if (is_empty_briandais(trie)) {
        return max_height_next = max_height_sub = 0;
    }
    if ((max_height_next = height(trie->next_member)) > (max_height_sub = 1 + height(trie->sub_member))) {
        return max_height_next;
    }else{
        return max_height_sub;
    }
}

//TODO
double mean_depth(struct ListOfLists* trie){
    int words_trie = word_count(trie);
    if (is_empty_briandais(trie)) {
        return 0.0;
    }
    int words_next = word_count(trie->next_member);
    int words_sub = word_count(trie->sub_member);
    double coefficient_next = words_next/(double)words_trie;
    double coefficient_sub = words_sub/(double)words_trie;
    
    return coefficient_next*mean_depth(trie->next_member) + coefficient_sub*(1+mean_depth(trie->sub_member));
}

int prefix_count(struct ListOfLists* trie, char* prefix){
    //all words start with the empty word
    if (prefix[0] == '\0' || is_empty_briandais(trie)) {
        return word_count(trie);
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
            return word_count(trie->sub_member);
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
        trie1 = insert_word_briandais(trie1, get_word(words_in_trie2));
        words_in_trie2 = get_next(words_in_trie2);
    }
    return trie1;
}

//very complex algorithm...the idea is to simulate the depth search in the trie and to store the words in a list
List ordered_list_briandais(struct ListOfLists* trie){
    if (is_empty_briandais(trie)) {
        return create_empty_list();
    }
    List list = NULL;
    //kind of a buffer which stores the pointer to the current trie-node and by poping (sp--) the trie-nodes visited before, appear, so that one can branch in the next word
    struct ListOfLists** stack_of_members = malloc(MAX_WORD_SIZE*sizeof(struct ListOfLists*));
    //sp := stack pointer, pointing to the current node; decreasing means going back in history; increases when a new pointer to a node is being added
    int sp = 0;
    //word represents the trace in the trie, and when a END_WORD symbol is reached, it is attached to the list
    char* word = malloc(MAX_WORD_SIZE*sizeof(char));
    while (1) {
        while (get_root_value(trie) != END_OF_WORD) {
            stack_of_members[sp] = trie;
            word[sp] = trie->letter;
            trie = trie->sub_member;
            sp++;
        }
        if (trie->letter == END_OF_WORD && trie->next_member != NULL) {
            stack_of_members[sp] = trie;
        }
        //substitute with "complex_insert_word_list(list, word)" if you want an order in wich the word length matters, i.e. a < z < aa < zz < aaa....
        list = simple_insert_word_list(list, word);
        if (is_empty_briandais(trie)) {
            sp--;
        }
        for(;(trie = stack_of_members[sp])->next_member == NULL; sp--){
            word[sp] = '\0';
            if (sp == 0) {
                return list;
            }
        }
        if ((trie = stack_of_members[sp])->next_member != NULL) {
            word[sp] = '\0';
            trie = trie->next_member;
        }
    }
    return list;
}













