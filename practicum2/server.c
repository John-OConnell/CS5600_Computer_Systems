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
#include <signal.h> 
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "server-helper.h"

// Define constants for the server IP and port
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 9002

// Global variables to account for STOP command
volatile sig_atomic_t close_server = 0;
pthread_mutex_t close_server_mutex = PTHREAD_MUTEX_INITIALIZER;

// Make server socket global to allow for close
int server_socket;

/*
 * Signal handler to break the server loop
 */
void signal_handler(int signo) {
  if (signo == SIGINT) {
    printf("\nServer Closing!\n");
    close(server_socket);
    exit(0);
  }
}

/*
 * Monitor thread to listen for STOP command
 */
void* monitor_thread(void* arg) {
    while (1) {
        pthread_mutex_lock(&close_server_mutex);
        if (close_server) {
            pthread_mutex_unlock(&close_server_mutex);
            printf("\nServer Closing!\n");
            close(server_socket);
            exit(0);
        }
        pthread_mutex_unlock(&close_server_mutex);
        // Add a sleep to avoid busy-waiting
        usleep(100000);  // Sleep for 100 milliseconds
    }
    return NULL;
}

int main(void)
{
  // Set up signal handler
  signal(SIGINT, signal_handler);

  // Networking initialization
  int client_socket;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_size = sizeof(client_addr);
  pthread_t tid, monitor_tid;
  
  // Create socket:
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if(server_socket < 0)
  {
    perror("Error while creating socket\n");
    return -1;
  }
  
  // Set port and IP:
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(SERVER_PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  
  // Bind to the set port and IP:
  if( bind(server_socket, (struct sockaddr*) &server_addr, sizeof(server_addr)) <0 )
  {
    perror("Server couldn't bind to the port\n");
    return -1;
  }
  
  // Listen for clients
  if(listen(server_socket, 5) < 0)
  {
    perror("Error while listening for clients\n");
    return -1;
  }

  printf("\nListening for incoming connections.....\n");

  // Create a thread to monitor the close_server flag
  if (pthread_create(&monitor_tid, NULL, monitor_thread, NULL) != 0) {
      perror("Monitoring thread creation failed");
      return -1;
  }

  while(1){
    
    // Accept an incoming connection
    client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &client_size);
    if (client_socket < 0)
    {
      perror("Error accepting client connection\n");
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
