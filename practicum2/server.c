//
// server.c / Practicum 2
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

int main(void)
{
  int server_socket, client_socket;
  socklen_t client_size;
  struct sockaddr_in server_addr, client_addr;
  char client_message[256];
  char server_message[256];
  
  // Create socket:
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  
  if(server_socket < 0){
    printf("Error while creating socket\n");
    return -1;
  }
  printf("Socket created successfully\n");
  
  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9002);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  // Bind to the set port and IP:
  if( bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) <0 ){
    printf("Couldn't bind to the port\n");
    return -1;
  }
  printf("Done with binding\n");
  
  // Listen for clients:
  if(listen(server_socket, 1) < 0){
    printf("Error while listening\n");
    return -1;
  }
  printf("\nListening for incoming connections.....\n");
  
  while(1){

    // Clean buffers:
    memset(server_message, '\0', sizeof(server_message));
    memset(client_message, '\0', sizeof(client_message));

    // Accept an incoming connection:
    client_size = sizeof(client_addr);
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
    
    if (client_socket < 0){
      printf("Can't accept\n");
      return -1;
    }

    printf("Client connected at IP: %s and port: %i\n", 
          inet_ntoa(client_addr.sin_addr), 
          ntohs(client_addr.sin_port));
    
    // Receive client's message:
    if (recv(client_socket, client_message, sizeof(client_message), 0) < 0){
      printf("Couldn't receive\n");
      return -1;
    }
    printf("Msg from client: %s\n", client_message);
    
    // Respond to client:
    strcpy(server_message, "This is the server's response message.");
    
    if (send(client_socket, server_message, strlen(server_message), 0) < 0){
      printf("Can't send\n");
      return -1;
    }
    // Closing the socket:
    close(client_socket);
  }
  close(server_socket);
  
  return 0;
}
