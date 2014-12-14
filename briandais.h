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

Briandais create_empty_briandais();

void destroy_briandais(Briandais);

bool is_empty_briandais(Briandais);

char get_root_value(Briandais);

void set_root_value(Briandais, char);

Briandais get_next_member(Briandais);

Briandais get_sub_member(Briandais);

bool is_word_contained_briandais(Briandais, char*);

Briandais insert_word_briandais(Briandais, char*);

Briandais delete_word_briandais(Briandais, char*);

int word_count_briandais(Briandais);

int null_pointers_count_briandais(Briandais);

List ordered_list_briandais(Briandais);

int height_briandais(Briandais);

double mean_depth_briandais(Briandais);

int prefix_count_briandais(Briandais, char*);

Briandais merge_briandais(Briandais, Briandais);

//Hybrid briandais_to_hybrid(Briandais);


#endif /* defined(__Dictionary__briandais__) */
