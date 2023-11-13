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

/*
 * Creates a cache struct
 * 
 * @return my_cache: new populated cache struct
 * 
 */
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

/*
 * Inserts a message into the cache
 *
 * @param cache: an instance of a cache
 * @param message: the message to be inserted
 * @param item: the item to be inserted
 * 
 * @return: 1 on success
 *          0 on failure
 *         -1 if the cache is NULL
 * 
 */
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
        msg_t* old_msg = dll_pop_back(cache->cache_dll);
        free(old_msg);
        return dll_push_front(cache->cache_dll, message);
    }
}

/*
 * Checks for a message in the cache and returns it if present
 * Updates the cache to reflect the message as most recently used
 *
 * @param cache: an instance of a cache
 * @param msgID: the ID of the message to be returned
 * 
 * @return hit: the requested message
 *              or NULL if the message isn't in the cache
 *              or NULL if the cache is NULL
 * 
 */
msg_t* check_cache(cache_t* cache, int msgID)
{
    if(cache == NULL)
    {
        return NULL;
    }

    int pos = 0;
    node_t* iterator = cache->cache_dll->head;

    while(iterator != NULL)
    {
        msg_t* msg = iterator->data;
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

/*
 * Empties a cache and resets the hit and miss counters
 *
 * @param cache: an instance of a cache
 * 
 * @return: 1 on success
 *         -1 if the cache is NULL
 * 
 */
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

/*
 * Removes a cache and all its elements from memory
 *
 * @param cache: an instance of a cache
 * 
 * @return: program crashes if cache is null
 * 
 */
void free_cache(cache_t* cache)
{
    if (cache == NULL)
    {
        exit(1);
    }

    free_dll(cache->cache_dll);
    free(cache);
}

/*
 * Prints message IDs of all messages in a cache
 *
 * @param cache: an instance of a cache
 * 
 */
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
