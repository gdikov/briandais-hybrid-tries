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


typedef struct ListOfLists* Briandais;

//creates an empty trie, containing only one empty word.
Briandais create_empty_briandais();

//frees all allocated memory by the trie. Complexity of O(n).
void destroy_briandais(Briandais);

/*returns true if the trie is empty. Be careful - false also will be returned if the trie is not initialized!
 */
bool is_empty_briandais(Briandais);

//returns the root value of an non-empty trie and '$' otherwise.
char get_root_value(Briandais);

//sets the root value
void set_root_value(Briandais, char);

//sets next member
void set_next_member(Briandais current, Briandais next);

//sets sub member
void set_sub_member(Briandais current, Briandais sub);

//looks up a word in the trie and returns true if the word is the empty word, or it is really contained in the trie.
bool is_word_contained_briandais(Briandais, char*);

//iserts one word and returns 1 on success, 0 if the word has already been insterted and -1 on failure
Briandais insert_word_briandais(Briandais, char*);

Briandais delete_word_briandais(Briandais, char*);

//returns the total number of words in the trie
int word_count(Briandais);

//lists all the words in a linked list by an alphabetical order
List ordered_list_briandais(Briandais);

//returns the number of pointers to NULL
int null_pointers_count(Briandais);

//returns the height of the trie
int height(Briandais);

//returns the maximum depth of the trie
double mean_depth(Briandais);

//returns the number of words starting with the given as parameter
int prefix_count(Briandais, char*);

Briandais merge_briandais(Briandais, Briandais);


#endif /* defined(__Dictionary__briandais__) */
