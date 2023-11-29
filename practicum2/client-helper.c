//
// client-helper.c / Practicum 2
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

#include "msgTypes.h"
#include "client-helper.h"

// Define constants for the server IP and port
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9002

/*
 * Prints the help message for the rfs program
 * 
 */
void print_help(){
	printf("rfs. (2023 Nov 28)\n\n");
	printf("Usage: rfs (command)");
	printf(" <file_path> <file_path>\n\n");
	printf("Commands:\n");
	printf("  WRITE         Writes a file from the client's file system to the server.\n");
	printf("  GET           Retrieves a file from the remote file system.\n");
	printf("  RM            Deletes a file or folder in the remote file system.\n");
    printf("  LS            Lists all versioning information about a file.\n");
	printf("  HELP          Print this help message.\n");
}

int connectToServer(const char *server_ip, int server_port){

    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0)
    {
        printf("Unable to create socket\n");
        return -1;
    }
    
    // Set port and IP the same as server-side
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9002);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // Send connection request to server
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Unable to connect to server\n");
        return -1;
    }

    return client_socket;
}

int rfs_write(char* local_file_path, char* remote_file_path){

    printf("local_file_path: %s\n", local_file_path);
    printf("remote_file_path: %s\n", remote_file_path);
    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);


    writeMsg_t message;
    message.msgType = WRITE;
    strcpy(message.filePath, remote_file_path);

    // Open the file for reading
    FILE* file = fopen(local_file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    message.contentLength = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    if (message.contentLength > MAXFILESIZE)
    {
        printf("File too big! Aborting Write\n");
        return -1;
    }

    // Read the file content into the struct
    fread(message.content, 1, message.contentLength, file);

    fclose(file);

    // Copy message struct into buffer
    char buffer[sizeof(writeMsg_t)];
    memcpy(buffer, &message, sizeof(writeMsg_t));

    // Send the serialized struct over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("Send failed");
        return -1;
    }

    // Receive the server's response, a flag to indicate success or failure
    int status;
    if(recv(client_socket, &status, sizeof(int), 0) < 0)
    {
        printf("Error while receiving server's msg\n");
        return -1;
    }

    // Process the status value
    if (status == 1) {
        printf("Command executed successfully\n");
    } else {
        printf("Command execution failed\n");
    }

    close(client_socket);

    return 0;

}