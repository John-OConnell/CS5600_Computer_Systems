//
// randCache.c / Practicum 1
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

int cache_insert(cache_t* cache, msg_t* message)
{
    if(cache == NULL)
    {
        return -1;
    }

    if(cache->cache_dll->count < CACHESIZE)
    {
        return dll_push_front(cache->cache_dll, message);
    }
    else
    {
        int pos = rand() % CACHESIZE;
        msg_t* old_msg = dll_remove(cache->cache_dll, pos);
        free(old_msg);
        return dll_insert(cache->cache_dll, pos, message);
    }
}

msg_t* check_cache(cache_t* cache, int msgID)
{
    if(cache == NULL)
    {
        return NULL;
    }

    node_t* iterator = cache->cache_dll->head;

    while(iterator != NULL)
    {
        msg_t* msg = iterator->data;
        if(msg->id == msgID)
        {
            return msg;
        }
        iterator = iterator->next;
    }
    return NULL;
}

int reset_cache(cache_t* cache)
{
    if(cache == NULL)
    {
        return -1;
    }

    while(cache->cache_dll->count > 0)
    {
        msg_t* msg = dll_pop_front(cache->cache_dll);
        free(msg);
    }

    cache->hits = 0;
    cache->misses = 0;

    return 1;
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
    if(cache == NULL)
    {
        return;
    }

    node_t* iterator = cache->cache_dll->head;

    while(iterator != NULL)
    {
        msg_t* msg = iterator->data;
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