//
// message.h / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>

#define MSGDIR "messages/"
#define MSGSIZE 1024
#define CONTENTSIZE (MSGSIZE-(sizeof(int)*2)-sizeof(time_t))/2
#define NAMESIZE (CONTENTSIZE/2)-4

typedef struct cache cache_t;

// message struct
typedef struct message{
    unsigned int id;
    time_t time;
    char sender[NAMESIZE];
    char receiver[NAMESIZE];
    char content[CONTENTSIZE];
    int delivered;
}msg_t;

msg_t* create_msg(const char* sender, const char* receiver, const char* content);

int store_msg(const msg_t* message);

msg_t* retrieve_msg(cache_t* cache, unsigned int msgID);

#endif