//
// cacheEvalLoc.c / Practicum 1
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
#include "genRandWord.h"

#define NUM_MSGS 50

/*
 * Creates a message struct with random variables
 * 
 * @return newMsg: new populated message struct
 * 
 */
msg_t* create_rand_msg()
{
    // initialize necessary message variables
    char* sender = genRandWord();
    char* receiver = genRandWord();
    char* word;
    char* message = (char*)calloc(MSGSIZE, sizeof(char));

    // populating the message with random words
    for(int i = 0; i < 5; i++)
    {
        word = genRandWord();
        strcat(message, word);
        strcat(message, " ");
        free(word);
    }

    word = genRandWord();
    strcat(message, word);
    free(word);
    
    // creating the message to be returned
    msg_t* newMsg = create_msg(sender, receiver, message);

    free(sender);
    free(receiver);
    free(message);

    return newMsg;
}

int main(){
    // seed random num generator and create cache
    srand(time(NULL));
    cache_t* evalCache = create_cache();

    // loop to create messages
    for(int i = 0; i < NUM_MSGS; i++)
    {
        msg_t* newMsg = create_rand_msg();
        store_msg(newMsg);
        free(newMsg);
    }

    // loop to access messages
    for(int i = 0; i < 1000; i++)
    {
        if(i < 250)
        {
            if(i % 4 == 0)
            {
                int msgId = (rand() % 5) + 1;
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
            else
            {
                int msgId = (rand() % NUM_MSGS) + 1;
                //printf("all: %d\n", msgId);
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
        }
        else if(i >= 250 && i < 500)
        {
            if(i % 4 == 0)
            {
                int msgId = (rand() % 5) + 6;
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
            else
            {
                int msgId = (rand() % NUM_MSGS) + 1;
                //printf("all: %d\n", msgId);
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
        }
        else if(i >= 500 && i < 750)
        {
            if(i % 4 == 0)
            {
                int msgId = (rand() % 5) + 11;
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
            else
            {
                int msgId = (rand() % NUM_MSGS) + 1;
                //printf("all: %d\n", msgId);
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
        }
        else
        {
            if(i % 4 == 0)
            {
                int msgId = (rand() % 5) + 16;
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
            else
            {
                int msgId = (rand() % NUM_MSGS) + 1;
                //printf("all: %d\n", msgId);
                msg_t* testMsg = retrieve_msg(evalCache, msgId);
            }
        }
    }

    // calculating cache hit ratio
    float hit_ratio = evalCache->hits / 1000.0f;

    // print results
    printf("Number of Cache Hits Per 1000 Random Message Accesses with Temporal Locality: %d\n\n", evalCache->hits);
    printf("Number of Cache Misses Per 1000 Random Message Accesses with Temporal Locality: %d\n\n", evalCache->misses);
    printf("Cache Hit Ratio: %.3f\n\n", hit_ratio);

    free_cache(evalCache);
    return 0;
}
