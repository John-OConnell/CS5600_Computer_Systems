//
// msgTypes.h / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#ifndef MSGTYPES_H
#define MSGTYPES_H

#define MAXFILESIZE 102400 //8192

// Enum to represent different message types
enum MSGTYPE {
        WRITE
    ,   GET
    ,   GETRET
    ,   REMOVE
    ,   LS
};

typedef struct writeMsg {
    int msgType;  // Operation code
    char filePath[256];  // File name
    size_t contentLength;  // Length of content
    char content[MAXFILESIZE];  // Actual file content
} writeMsg_t;

typedef struct getMsg {
    int msgType;  // Operation code
    char filePath[256];  // File name
} getMsg_t;

typedef struct getRetMsg {
    int msgType;  // Operation code
    int fileFound; // Flag representing if file was found on server
    size_t contentLength;  // Length of content
    char content[MAXFILESIZE];  // Actual file content
} getRetMsg_t;

typedef struct removeMsg {
    int msgType;  // Operation code
    char filePath[256];  // File name
} removeMsg_t;

#endif
