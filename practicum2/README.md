## Overview

This is my implementation of *Practicum II - Server Based Versioning File System* for CS5600 F23. \
A description of this assignment is as follows:

*Most programs require persistent storage of data either in a file or in a database. Most operating systems provide a file system to\ 
allow writing and reading of bytes from a storage device. However, those files are written to a local storage device making sharing and\
versioning are difficult. So, some programs use a remote file system with versioning.*

*In this practicum you will implement a server-based versioning file storage system that allows any program to open a TCP connection through\
a socket (a kind of file in Unix), request file services from a server (reading a file, writing to a file, creating a folder, get information\
about a file or folder, and deleting a file or folder).*

## File Breakdown
- server.c            - program entrance point for the server
- server-helper.h     - function headers for server helper functions used to process client messages
- server-helper.c     - implementation of the server helper functions
- client.c            - program entrance point for the client
- client-helper.h     - function headers for client helper functions used connect and send messages to the server
- client-helper.c     - implementation of the client helper functions
- msgTypes.h          - message struct definitions
- rfsys/              - the root directory of the remote file system
- Makefile            - makefile used to build project executables

## Instructions to Run

