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
#include <pthread.h>

#include "server-helper.h"

// Define constants for the server IP and port
#define SERVER_IP "127.0.0.1"
//#define SERVER_IP "10.141.76.133"
#define SERVER_PORT 9002

int main(void)
{
  int server_socket, client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_size = sizeof(client_addr);
  pthread_t tid;
  
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
  if(listen(server_socket, 5) < 0)
  {
    printf("Error while listening\n");
    return -1;
  }
  printf("\nListening for incoming connections.....\n");
  
  while(1){
    
    // Accept an incoming connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
    if (client_socket < 0)
    {
      printf("Can't accept client connection\n");
      return -1;
    }

    printf("Client connected at IP: %s and port: %i\n", 
          inet_ntoa(client_addr.sin_addr), 
          ntohs(client_addr.sin_port));
    
    // Create a new thread to handle the client
    if (pthread_create(&tid, NULL, client_handler, (void*)&client_socket) != 0)
    {
            perror("Thread creation failed");
            close(client_socket);
    }
  }

  close(server_socket);

  return 0;

}
