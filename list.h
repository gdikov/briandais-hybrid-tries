//
//  list.h
//  Dictionary
//
//  Created by dikov on 09/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#ifndef __Dictionary__list__
#define __Dictionary__list__

#include <stdbool.h>

typedef struct ListOfWords* List;

//with self ordering
List complex_insert_word_list(List, char*);

List simple_insert_word_list(List, char*);

List concat_list(List, List);

List create_empty_list();

List create_non_empty_list(char*);

bool is_empty_list(List);

bool is_word_contained_list(List, char*);

char* get_word_list(List);

List get_next_list(List);

List set_next_list(List, List);

List set_word_list(List, char*);

void print_list(List);

#endif /* defined(__Dictionary__list__) */
