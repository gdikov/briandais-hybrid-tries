//
//  briandais.h
//  Dictionary
//
//  Created by dikov on 06/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#ifndef __Dictionary__briandais__
#define __Dictionary__briandais__

#include <stdbool.h>
#include "list.h"
#include "hybrid.h"


typedef struct ListOfLists* Briandais;

//creates an empty trie, containing only one empty word.
Briandais create_empty_briandais();

//frees all allocated memory by the trie. Complexity of O(n).
void destroy_briandais(Briandais);

//returns true if the trie is empty or not initialized
bool is_empty_briandais(Briandais);

//returns the root value of an non-empty trie and '$' otherwise.
char get_root_value(Briandais);

//sets the root value
void set_root_value(Briandais, char);

//it will also return true if the word is the empty word!
bool is_word_contained_briandais(Briandais, char*);

Briandais insert_word_briandais(Briandais, char*);

Briandais delete_word_briandais(Briandais, char*);

//returns the total number of words in the trie
int word_count(Briandais);

//returns the number of pointers to NULL
int null_pointers_count(Briandais);

//lists all the words in an alphabetically ordered list
List ordered_list_briandais(Briandais);

//returns the maximum height (depth) of the trie
int height(Briandais);

//returns the mean height (depth) of the trie
double mean_depth(Briandais);

int prefix_count(Briandais, char*);

Briandais merge_briandais(Briandais, Briandais);

Hybrid briandais_to_hybrid(Briandais);


#endif /* defined(__Dictionary__briandais__) */
