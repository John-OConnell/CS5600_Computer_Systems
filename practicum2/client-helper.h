//
// client-helper.h / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#ifndef CLIENTHELP_H
#define CLIENTHELP_H

#include "msgTypes.h"

void print_help();

int connectToServer(const char* server_ip, int server_port);

int rfs_write(char* local_file_path, char* remote_file_path);

int rfs_get(char* local_file_path, char* remote_file_path, int version_number);

int rfs_remove(char* remote_file_path);

int rfs_ls(char* remote_file_path);

#endif
