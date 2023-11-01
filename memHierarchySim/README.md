## Overview and Instructions to Run

- The message.h file contains the message struct definition and function headers
- The message.c file contains the implementation of the required functions
- The test.c file contains the unit tests used to test propery implementation

In order to build the code simply run 'make'. The output executable is called 'test', so to run the executable simply run './test'. Alternatively, you can type 'make && ./test' to build and run the program in one step. Any messages created will be saved to the messages directory. Running 'make clean' will remove the executable as well as all messages stored in the message directory. 

The message struct contains a unique identifier, time sent, the sender (right now that is just some text), a receiver (again, for now, just some text), content (text), and a flag indicating whether the message was delivered. You will notice in the tests that a message that has been retrieved has its delivered indicator set to 1.

The unit tests test creating a message, storing a message, retrieving a message, attempting to retrieve a message that doesn't exist, and creating, storing, and retrieving multiple messages at once.