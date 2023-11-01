//
// message.h / Memory Heirarchy Simulation - Part 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Oct 26, 2023
//
//

#include <time.h>
#define MSGDIR "messages/"
#define MSGSIZE 1024

// message struct
typedef struct message{
    unsigned int id;
    time_t time;
    char sender[256];
    char receiver[256];
    char content[MSGSIZE];
    int delivered;
}msg;

msg* create_msg(const char* sender, const char* receiver, const char* content);

int store_msg(const msg* message);

msg* retrieve_msg(unsigned int msgID);
