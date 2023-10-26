//
// message.h / Memory Heirarchy Simulation - Part 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Oct 26, 2023
//
//

#define __USE_XOPEN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MSGDIR "messages/"

unsigned int nextMsgID = 1;

// message struct
typedef struct message{
    unsigned int id;
    time_t time;
    char sender[256];
    char receiver[256];
    char content[512];
    int delivered;
} msg;

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
msg* create_msg(const char* sender, const char* receiver, const char* content){
    
    // dynamically allocate memory for the message
    msg* newMsg = (msg*)malloc(sizeof(msg));
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
 * @return 0 if success, -1 if failure
 * 
 */
int store_msg(const msg* message){

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
 * Retrieves a message from the disk
 *
 * @param msgID: the id of the message to be retrieved
 * 
 * @return retrievedMsg: pointer to the message struct retrievd.
 *                       Returns NULL if message cannot be retrieved.
 * 
 */
msg* retrieve_msg(unsigned int msgID){
    
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
    msg* retrievedMsg = (msg*)malloc(sizeof(msg));
    if (retrievedMsg == NULL) {
        fclose(fp);
        return NULL;
    }
    
    // read message details from the file to message struct
    fscanf(fp, "ID: %u\n", &retrievedMsg->id);
    char timeString[32];
    fscanf(fp, "Time: %31[^\n]\n", timeString);
    struct tm timeInfo;
    strptime(timeString, "%Y-%m-%d %H:%M:%S", &timeInfo);
    retrievedMsg->time = mktime(&timeInfo);
    fscanf(fp, "Sender: %255[^\n]\n", retrievedMsg->sender);
    fscanf(fp, "Receiver: %255[^\n]\n", retrievedMsg->receiver);
    fscanf(fp, "Content: %511[^\n]\n", retrievedMsg->content);

    fclose(fp);

    // indicate message has been delivered and overwrite file
    retrievedMsg->delivered = 1;
    store_msg(retrievedMsg);

    return retrievedMsg;
}
