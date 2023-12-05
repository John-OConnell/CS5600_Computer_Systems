//
// server-helper.h / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#ifndef SERVERHELP_H
#define SERVERHELP_H

#include "msgTypes.h"

extern volatile sig_atomic_t close_server;
extern pthread_mutex_t close_server_mutex;

void* client_handler(void* s_socket);

int write_handler(writeMsg_t* client_message);

int get_handler(getMsg_t* client_message, int client_socket);

int remove_handler(removeMsg_t* client_message);

int ls_handler(lsMsg_t* client_message, int client_socket);

int write_metadata(const char *origFilePath, const metadata_t *metadata);

int send_metadata(const char *origFilePath, int client_socket);

#endif
