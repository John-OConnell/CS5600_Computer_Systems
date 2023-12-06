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
Running "make" in the project directory will build all executables. The server can be started by running "./server", while the commands to\
intereact with the remote file system are all run through the "./rfs" executable. Running "./rfs HELP" will display the help menu with options\
on the different commands that can be run. The server and client IP address and ports can be configured as global variables in the server.c\
and client-helper.c files, respectively. A unit test shell script is provided, which can be run with "./unitTest.sh". It's important to note\
that you must start the server before running the shell script, or the execution will fail. Running "make clean" will remove all executalbes,\
and running "make rfsysclean" will remove any new files added to the remote file system. 
