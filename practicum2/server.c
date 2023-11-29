//
// server.c / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "server-helper.h"

// Define constants for the server IP and port
#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "10.141.76.133"
#define SERVER_PORT 9002

int main(void)
{
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  char message_buffer[8704];
  int status = -1;
  
  // Create socket:
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(server_socket < 0)
  {
    printf("Error while creating socket\n");
    return -1;
  }
  
  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  
  // Bind to the set port and IP:
  if( bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) <0 )
  {
    printf("Couldn't bind to the port\n");
    return -1;
  }
  
  // Listen for clients:
  if(listen(server_socket, 1) < 0)
  {
    printf("Error while listening\n");
    return -1;
  }
  printf("\nListening for incoming connections.....\n");
  
  while(1){
    memset(message_buffer, '\0', sizeof(message_buffer));

    // Accept an incoming connection:
    socklen_t client_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
    if (client_socket < 0)
    {
      printf("Can't accept client connection\n");
      return -1;
    }

    printf("Client connected at IP: %s and port: %i\n", 
          inet_ntoa(client_addr.sin_addr), 
          ntohs(client_addr.sin_port));
    
    // Receive client's message:
    if (recv(client_socket, message_buffer, sizeof(message_buffer), 0) < 0)
    {
      printf("Can't receive message from client\n");
      close(client_socket);
      return -1;
    }

    // Get the message type of the recieved message
    uint32_t messageType;
    memcpy(&messageType, message_buffer, sizeof(uint32_t));
    
    switch (messageType) {

      case WRITE:
        printf("Handling write message from client\n");
        writeMsg_t* client_message = (writeMsg_t*)malloc(sizeof(writeMsg_t));
        memcpy(client_message, message_buffer, sizeof(writeMsg_t));
        status = write_handler(client_message);
        break;

      default:
        break;
    }

    // Respond to client:
    if (send(client_socket, &status, sizeof(int), 0) < 0)
    {
      printf("Can't status to client\n");
      close(client_socket);
      return -1;
    }
    // Closing the socket:
    close(client_socket);
  }
  close(server_socket);
  
  return 0;
}
