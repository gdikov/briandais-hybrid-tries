//
//  hybrid.h
//  Dictionary
//
//  Created by dikov on 10/11/14.
//  Copyright (c) 2014 dikov. All rights reserved.
//

#ifndef __Dictionary__hybrid__
#define __Dictionary__hybrid__

#include <stdbool.h>
#include "briandais.h"
#include "list.h"


typedef struct TernaryTrie* Hybrid;

Hybrid insert_word_hybrid(Hybrid, char*);

Hybrid delete_word_hybrid(Hybrid, char*);

bool is_word_contained_hybrid(Hybrid, char*);

int word_count_hybrid(Hybrid);

int null_pointers_count_hybrid(Hybrid);

List ordered_list_hybrid(Hybrid);

int height_hybrid(Hybrid);

double mean_depth_hybrid(Hybrid);

int prefix_count_hybrid(Hybrid, char*);

Hybrid merge_hybrid(Hybrid, Hybrid);

//Briandais hybrid_to_briandais(Hybrid);

#endif /* defined(__Dictionary__hybrid__) */
