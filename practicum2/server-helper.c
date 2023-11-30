//
// server-helper.c / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "server-helper.h"

// Define constant for rfs directory location
#define ROOTDIR "rfsys/"

int write_handler(writeMsg_t* client_message){

    int msgType;  // Operation code
    char filePath[256];  // File name
    size_t contentLength;  // Length of content
    char content[MAXFILESIZE];  // Actual file content

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    FILE *file = fopen(rfsFilePath, "w");
    if (file == NULL)
    {
        printf("Error opening file");
        return -1;
    }

    size_t bytes_written = fwrite(client_message->content, 1, client_message->contentLength, file);
    if (bytes_written != client_message->contentLength)
    {
        printf("Error writing to file");
        return -1;
    }

    fclose(file);

    return 1;
}

int get_handler(getMsg_t* client_message, int client_socket){

    getRetMsg_t message;
    message.msgType = GETRET;

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    // Open the file for reading
    FILE* file = fopen(rfsFilePath, "r");
    // If the file can't be found on the server, update the message flag
    // and send the message
    if (file == NULL)
    {
        message.fileFound = 0;
        if (send(client_socket, &message, sizeof(getRetMsg_t), 0) < 0)
        {
            printf("File retrieval message failed to send to client\n");
        }
        return 0;
    }

    // Update file found flag
    message.fileFound = 1;

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    message.contentLength = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file content into the struct
    fread(message.content, 1, message.contentLength, file);

    fclose(file);

    // Copy message struct into buffer
    char buffer[sizeof(getRetMsg_t)];
    memcpy(buffer, &message, sizeof(getRetMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        printf("File retrieval message failed to send to client\n");
        return 0;
    }

    return 1;

}