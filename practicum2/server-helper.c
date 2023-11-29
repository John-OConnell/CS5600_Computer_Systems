//
// server-helper.c / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#include <stdio.h>
#include <string.h>
#include "server-helper.h"

// Define constant for rfs directory location
#define ROOTDIR "rfsys/"

int write_handler(writeMsg_t* client_message){

    int msgType;  // Operation code
    char filePath[256];  // File name
    size_t contentLength;  // Length of content
    char content[MAXFILESIZE];  // Actual file content

    printf("msgType: %d\n", client_message->msgType);
    printf("File path: %s\n", client_message->filePath);
    printf("content length: %zu\n", client_message->contentLength);
    printf("File contents: %s\n", client_message->content);

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    FILE *file = fopen(rfsFilePath, "w"); // "wb" for binary write mode
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