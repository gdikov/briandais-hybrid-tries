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

List create_empty_list();

bool is_empty_list(List);

char* get_word(List);

List get_next(List);

#endif /* defined(__Dictionary__list__) */
