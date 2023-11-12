//
// cache.h / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

#define CACHESIZE 3

typedef struct message msg_t;

typedef struct cache
{
    int hits;
    int misses;
    dll_t* cache_dll;
} cache_t;

cache_t* create_cache();

int cache_insert(cache_t* cache, msg_t* message);

msg_t* check_cache(cache_t* cache, int msgID);

int reset_cache(cache_t* cache);

void free_cache(cache_t* cache);

void print_cache(cache_t* cache);

#endif