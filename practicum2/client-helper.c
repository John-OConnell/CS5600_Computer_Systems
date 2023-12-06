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
#include <sys/stat.h>

#include "client-helper.h"

// Define constants for the server IP and port
#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "10.141.76.133"
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

/*
 * Creates a client socket and connects it to the server
 *
 * @param server_ip: the IP address of the server
 * @param server_port: the port number of the server
 * 
 * @return client_socket: the client socket number
 *
 * 
 */
int connectToServer(const char *server_ip, int server_port){

    // Create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(client_socket < 0)
    {
        perror("Unable to create socket\n");
        return -1;
    }
    
    // Set port and IP the same as server-side
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    
    // Send connection request to server
    if(connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Unable to connect to server\n");
        return -1;
    }

    // Return socket
    return client_socket;
}

/*
 * Writes a file to the remote server
 *
 * @param local_file_path: the file path on the local machine
 * @param remote_file_path: the file path on the remote server
 * 
 * @return: 0 on success
 *         -1 on failure
 * 
 */
int rfs_write(char* local_file_path, char* remote_file_path){

    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);

    // Create message to send to server
    writeMsg_t message;

    message.msgType = WRITE;
    strcpy(message.filePath, remote_file_path);

    // Open the file for reading
    FILE* file = fopen(local_file_path, "r");
    if (file == NULL) {
        perror("Error opening file");
        close(client_socket);
        return -1;
    }

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    message.contentLength = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);
    if (message.contentLength > MAXFILESIZE)
    {
        perror("File too big! Aborting Write\n");
        close(client_socket);
        return -1;
    }

    // Read the file content into the struct
    fread(message.content, 1, message.contentLength, file);

    // Close the file
    fclose(file);

    // Copy message struct into buffer
    char buffer[sizeof(writeMsg_t)];
    memcpy(buffer, &message, sizeof(writeMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("Write message send failed");
        close(client_socket);
        return -1;
    }

    // Receive the server's response, a flag to indicate success or failure
    int status;
    if(recv(client_socket, &status, sizeof(int), 0) < 0)
    {
        perror("Error while receiving server's message\n");
        close(client_socket);
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

/*
 * Retrieves a file from the remote server
 *
 * @param local_file_path: the file path on the local machine
 * @param remote_file_path: the file path on the remote server
 * 
 * @return: 0 on success
 *         -1 on failure
 * 
 */
int rfs_get(char* local_file_path, char* remote_file_path, int versionNumber){

    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);

    // Empty struct to receive a future message from the server
    getRetMsg_t server_message;

    // Create message to send to server
    getMsg_t message;
    message.msgType = GET;
    strcpy(message.filePath, remote_file_path);
    message.versionNumber = versionNumber;

    // Copy message struct into buffer
    char buffer[sizeof(getMsg_t)];
    memcpy(buffer, &message, sizeof(getMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("Get message send failed\n");
        return -1;
    }

    // Receive server's message
    if (recv(client_socket, &server_message, sizeof(server_message), 0) < 0)
    {
      perror("Can't receive message from server\n");
      close(client_socket);
      return -1;
    }

    if (server_message.msgType != GETRET)
    {
        perror("Incorrect/invalid message type received from server\n");
        close(client_socket);
        return -1;
    }
    else if (!server_message.fileFound)
    {
        perror("File doesn't exist on the server!\n");
    }
    else
    {
        // Open the file for reading
        FILE *file = fopen(local_file_path, "w");
        if (file == NULL)
        {
            perror("Error opening file");
            return -1;
        }

        // Read the message content into the file
        size_t bytes_written = fwrite(server_message.content, 1, server_message.contentLength, file);
        if (bytes_written != server_message.contentLength)
        {
            perror("Error writing to file");
            return -1;
        }

        fclose(file);
    }

    close(client_socket);

    return 0;
}

/*
 * Removes a file from the remote server
 *
 * @param remote_file_path: the file path on the remote server
 * 
 * @return: 0 on success
 *         -1 on failure
 * 
 */
int rfs_remove(char* remote_file_path){

    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);

    // Create message to send to server
    removeMsg_t message;
    message.msgType = REMOVE;
    strcpy(message.filePath, remote_file_path);

    // Copy message struct into buffer
    char buffer[sizeof(removeMsg_t)];
    memcpy(buffer, &message, sizeof(removeMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("Remove message send failed\n");
        return -1;
    }

    // Receive the server's status message
    int status;
    if(recv(client_socket, &status, sizeof(int), 0) < 0)
    {
        perror("Error while receiving server's message\n");
        close(client_socket);
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

/*
 * Gets all versioning information for a file
 *
 * @param remote_file_path: the file path on the remote server
 * 
 * @return: 0 on success
 *         -1 on failure
 * 
 */
int rfs_ls(char* remote_file_path){

    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);

    // Create message to send to server
    lsMsg_t message;
    message.msgType = LS;
    strcpy(message.filePath, remote_file_path);

    // Copy message struct into buffer
    char buffer[sizeof(lsMsg_t)];
    memcpy(buffer, &message, sizeof(lsMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("LS message send failed\n");
        return -1;
    }

    printf("File: %s\n", remote_file_path);
    
    metadata_t receivedMetadata;

    // Receive metadata from server
    while (recv(client_socket, &receivedMetadata, sizeof(metadata_t), 0) > 0)
    {
        // Check for the end of the stream
        if (receivedMetadata.versionNumber == -1 && strcmp(receivedMetadata.timestamp, "") == 0)
        {
            break;  // End of stream reached
        }

        // Print metadata
        printf("\tVersion Number: %d, Timestamp: %s\n", receivedMetadata.versionNumber, receivedMetadata.timestamp);
    }

    close(client_socket);

    return 0;
}

/*
 * Stops the server
 * 
 * @return: 0 on success
 *         -1 on failure
 * 
 */
int rfs_stop(){

    int client_socket = connectToServer(SERVER_IP, SERVER_PORT);

    // Create message to send to server
    stopMsg_t message;
    message.msgType = STOP;

    // Copy message struct into buffer
    char buffer[sizeof(stopMsg_t)];
    memcpy(buffer, &message, sizeof(stopMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        perror("Stop command send failed\n");
        return -1;
    }

    close(client_socket);

    return 0;
}
