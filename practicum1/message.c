//
// message.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#define _XOPEN_SOURCE 700
#define __USE_XOPEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "message.h"
#include "cache.h"

unsigned int nextMsgID = 1;

/*
 * Creates a message struct
 *
 * @param sender: sender of the message
 * @param receiver: desired reciever of the message
 * @param content: content of the message
 * 
 * @return newMsg: new populated message struct
 * 
 */
msg_t* create_msg(const char* sender, const char* receiver, const char* content){
    
    // dynamically allocate memory for the message
    msg_t* newMsg = (msg_t*)malloc(sizeof(msg_t));
    if(newMsg == NULL)
    {
        return NULL;
    }

    // populate all message fields
    newMsg->id = nextMsgID++;
    newMsg->time = time(NULL);
    strncpy(newMsg->sender, sender, sizeof(newMsg->sender));
    strncpy(newMsg->receiver, receiver, sizeof(newMsg->receiver));
    strncpy(newMsg->content, content, sizeof(newMsg->content));
    newMsg->delivered = 0;

    return newMsg;
}

/*
 * Stores a message to the disk
 *
 * @param message: instance of the message struct
 * 
 * @return 1 if success, -1 if failure
 * 
 */
int store_msg(const msg_t* message){

    // create file name based on message id
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "%s%d.txt", MSGDIR, message->id);

    // open file for writing
    FILE* fp = fopen(fileName, "w");
    if(fp == NULL)
    {
        return -1;
    }

    // convert from time_t to human readable time
    char time[32];
    strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&message->time));

    // populate file
    fprintf(fp, "ID: %u\n", message->id);
    fprintf(fp, "Time: %s\n", time);
    fprintf(fp, "Sender: %s\n", message->sender);
    fprintf(fp, "Receiver: %s\n", message->receiver);
    fprintf(fp, "Content: %s\n", message->content);
    fprintf(fp, "Delivered: %d\n", message->delivered);

    fclose(fp);

    return 0;
}

/*
 * Retrieves a message
 * If messages is in the cache, retrieves from cache
 * If not, retrieves from disk and updates cache
 *
 * @param msgID: the id of the message to be retrieved
 * 
 * @return retrievedMsg: pointer to the message struct retrievd.
 *                       Returns NULL if message cannot be retrieved.
 * 
 */
msg_t* retrieve_msg(cache_t* cache, unsigned int msgID){
    
    msg_t* retrievedMsg = NULL;
    retrievedMsg = check_cache(cache, msgID);
    if(retrievedMsg != NULL)
    {
        cache->hits++;
        return retrievedMsg;
    }
    
    // initialize file name based on input id
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "%s%d.txt", MSGDIR, msgID);

    // attempt to open file
    FILE* fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        return NULL;
    }

    // create new message struct to store file contents
    retrievedMsg = (msg_t*)malloc(sizeof(msg_t));
    if (retrievedMsg == NULL) {
        fclose(fp);
        return NULL;
    }
    
    // read message details from the file to message struct
    fscanf(fp, "ID: %u\n", &retrievedMsg->id);
    char timeString[32];
    fscanf(fp, "Time: %31[^\n]\n", timeString);
    struct tm timeInfo;
    // zero out the tm struct to prevent valgrind issues
    memset(&timeInfo, 0, sizeof(struct tm));
    strptime(timeString, "%Y-%m-%d %H:%M:%S", &timeInfo);
    retrievedMsg->time = mktime(&timeInfo);
    fscanf(fp, "Sender: %255[^\n]\n", retrievedMsg->sender);
    fscanf(fp, "Receiver: %255[^\n]\n", retrievedMsg->receiver);
    fscanf(fp, "Content: %1023[^\n]\n", retrievedMsg->content);
    fscanf(fp, "Delivered: %d\n", &retrievedMsg->delivered);

    fclose(fp);
    if(retrievedMsg->delivered == 0)
    {
        // indicate message has been delivered and overwrite file
        retrievedMsg->delivered = 1;
        store_msg(retrievedMsg);
    }

    cache->misses++;
    cache_insert(cache, retrievedMsg);

    return retrievedMsg;
}
