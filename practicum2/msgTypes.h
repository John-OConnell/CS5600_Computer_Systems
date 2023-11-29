//
// msgTypes.h / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

// Enum to represent different message types
enum MSGTYPE {
        WRITE
    ,   GET
    ,   REMOVE
};

struct writeMsg {
    int msgType = WRITE;  // Operation code
    char fileName[256];  // File name
    int contentLength;  // Length of content
    char content[8192];  // Actual file content
};