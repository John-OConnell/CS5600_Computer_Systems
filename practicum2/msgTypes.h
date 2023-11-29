//
// msgTypes.h / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#ifndef MSGTYPES_H
#define MSGTYPES_H

#define MAXFILESIZE 8192

// Enum to represent different message types
enum MSGTYPE {
        WRITE
    ,   GET
    ,   REMOVE
    ,   LS
};

typedef struct writeMsg {
    int msgType;  // Operation code
    char filePath[256];  // File name
    size_t contentLength;  // Length of content
    char content[MAXFILESIZE];  // Actual file content
} writeMsg_t;

#endif