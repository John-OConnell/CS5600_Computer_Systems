//
// lruCache.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "message.h"

cache_t* create_cache()
{
    cache_t* my_cache = (cache_t*)malloc(sizeof(cache_t));
    
    if (my_cache == NULL)
    {
        return NULL;
    }

    my_cache->hits = 0;
    my_cache->misses = 0;
    my_cache->cache_dll = create_dll();

    return my_cache;
}

msg_t* check_cache(cache_t* cache, int msgID)
{
    int pos = 0;
    msg_t* msg;
    node_t* iterator = cache->cache_dll->head;

    while(iterator != NULL)
    {
        msg = iterator->data;
        if(msg->id == msgID)
        {
            msg_t* hit = dll_remove(cache->cache_dll, pos);
            dll_push_front(cache->cache_dll, hit);
            return hit;
        }
        iterator = iterator->next;
        pos++;
    }
    return NULL;
}

int cache_insert(cache_t* cache, msg_t* message)
{
    if(cache->cache_dll->count < CACHESIZE)
    {
        return dll_push_front(cache->cache_dll, message);
    }
    else
    {
        msg_t* old_msg = dll_pop_back(cache->cache_dll);
        free(old_msg);
        return dll_push_front(cache->cache_dll, message);
    }
}

void free_cache(cache_t* cache)
{
    if (cache == NULL)
    {
        exit(1);
    }

    free_dll(cache->cache_dll);
    free(cache);
}

void print_cache(cache_t* cache)
{
    msg_t* msg;
    node_t* iterator = cache->cache_dll->head;

    while(iterator != NULL)
    {
        msg = iterator->data;
        if(iterator->next == NULL)
        {
            printf("%d\n", msg->id);
        }
        else
        {
            printf("%d --> ", msg->id);
        }
        iterator = iterator->next;
    }
}