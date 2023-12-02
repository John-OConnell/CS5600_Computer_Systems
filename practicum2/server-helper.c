//
// server-helper.c / Practicum 2
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 28, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#include "server-helper.h"

// Define constant for directory locations
#define ROOTDIR "rfsys/"
#define VERSDIR "rfsys/vers/"
#define METADIR "rfsys/meta/"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void* client_handler(void* arg) {

  int client_socket = *((int*)arg);
  char message_buffer[MAXFILESIZE + 512];
  int status = -1;

  // Receive client's message:
  if (recv(client_socket, message_buffer, sizeof(message_buffer), 0) < 0)
  {
    printf("Can't receive message from client\n");
    close(client_socket);
    pthread_exit(NULL);
  }

  // Get the message type of the recieved message
  uint32_t messageType;
  memcpy(&messageType, message_buffer, sizeof(uint32_t));
  
  switch (messageType) {

    case WRITE:
      printf("Handling write message from client\n");
      writeMsg_t* write_message = (writeMsg_t*)malloc(sizeof(writeMsg_t));
      memcpy(write_message, message_buffer, sizeof(writeMsg_t));
      status = write_handler(write_message);
      free(write_message);
      break;

    case GET:
      printf("Handling get message from client\n");
      getMsg_t* get_message = (getMsg_t*)malloc(sizeof(getMsg_t));
      memcpy(get_message, message_buffer, sizeof(getMsg_t));
      status = get_handler(get_message, client_socket);
      printf("STATUS BACK FROM GET HANDLER: %d\n", status);
      free(get_message);
      break;

    case REMOVE:
      printf("Handling remove message from client\n");
      removeMsg_t* rm_message = (removeMsg_t*)malloc(sizeof(removeMsg_t));
      memcpy(rm_message, message_buffer, sizeof(getMsg_t));
      status = remove_handler(rm_message);
      free(rm_message);
      break;

    case LS:
      printf("Handling ls message from client\n");
      lsMsg_t* ls_message = (lsMsg_t*)malloc(sizeof(lsMsg_t));
      memcpy(ls_message, message_buffer, sizeof(lsMsg_t));
      status = ls_handler(ls_message);
      free(ls_message);
      break;

    default:
      status = 0;
      break;
  }

  // Send status message to client
  if (send(client_socket, &status, sizeof(int), 0) < 0)
  {
    printf("Can't send status to client\n");
  }
  // Closing the socket:
  close(client_socket);
  pthread_exit(NULL);
  
}

int write_handler(writeMsg_t* client_message){

  int status = 0;
  // Prepend ROOTDIR to the beginning of the filePath in client_message
  char rfsFilePath[256 + sizeof(ROOTDIR)];
  strcpy(rfsFilePath, ROOTDIR);
  strcat(rfsFilePath, client_message->filePath);

  // Lock the mutex before accessing the shared resource (file)
  pthread_mutex_lock(&mutex);

  int prevVersion = 0;
  int currVersion = 0;

  // Check if file already exists
  if (access(rfsFilePath, F_OK) == 0)
  {
    // Create a new variable to execute the rename function on
    char rfsFilePathNEW[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePathNEW, rfsFilePath);

    // Determine the previous version number
    //prevVersion = 0;

    // Generate a versioned file name
    char versFilePath[256 + sizeof(VERSDIR) + 5]; // Assuming a version number <= 99999
    sprintf(versFilePath, "%sv%d_%s", VERSDIR, prevVersion, client_message->filePath);

    // Check if the versioned file already exists and increment version if necessary
    while (access(versFilePath, F_OK) == 0)
    {
      prevVersion++;
      sprintf(versFilePath, "%sv%d_%s", VERSDIR, prevVersion, client_message->filePath);
    }

    rename(rfsFilePathNEW, versFilePath);

    // Current version for updating metadata
  currVersion = ++prevVersion;
  }

  FILE *file = fopen(rfsFilePath, "w");
  if (file == NULL)
  {
      printf("Error opening file");
      // Unlock the mutex before returning on error
      pthread_mutex_unlock(&mutex);
      return -1;
  }

  size_t bytes_written = fwrite(client_message->content, 1, client_message->contentLength, file);
  if (bytes_written != client_message->contentLength)
  {
      printf("Error writing to file");
      // Close the file before returning on error
      fclose(file);
      // Unlock the mutex before returning on error
      pthread_mutex_unlock(&mutex);
      return -1;
  }

  fclose(file);

  // Create metadata struct for updating metadata file
  metadata_t metadata;
  // Get the current time
  time_t t = time(NULL);
  struct tm *tm_info = localtime(&t);

  // Format the timestamp as "YYYY-MM-DD HH:MM:SS" (adjust as needed)
  strftime(metadata.timestamp, sizeof(metadata.timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

  // Set the version number
  metadata.versionNumber = currVersion;

  if(write_metadata(client_message->filePath, &metadata) == 0)
  {
    status = 1;
  }

  // Release the lock after closing the file
  pthread_mutex_unlock(&mutex);

  return status;
}

int get_handler(getMsg_t* client_message, int client_socket){

    getRetMsg_t message;
    message.msgType = GETRET;

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    // Lock the mutex before accessing the shared resource (file)
    pthread_mutex_lock(&mutex);
    // Open the file for reading
    FILE* file = fopen(rfsFilePath, "r");
    // If the file can't be found on the server, update the message flag
    // and send the message
    if (file == NULL)
    {   

        message.fileFound = 0;
        if (send(client_socket, &message, sizeof(getRetMsg_t), 0) < 0)
        {
            printf("File retrieval message failed to send to client\n");
        }
        // Unlock the mutex before returning on error
        pthread_mutex_unlock(&mutex);
        return 0;
    }

    // Update file found flag
    message.fileFound = 1;

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    message.contentLength = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file content into the struct
    fread(message.content, 1, message.contentLength, file);

    fclose(file);

    // Release the lock after closing the file
    pthread_mutex_unlock(&mutex);

    // Copy message struct into buffer
    char buffer[sizeof(getRetMsg_t)];
    memcpy(buffer, &message, sizeof(getRetMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
        printf("File retrieval message failed to send to client\n");
        return 0;
    }

    return 1;

}

int remove_handler(removeMsg_t* client_message){

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    // Lock the mutex before accessing the shared resource (file)
    pthread_mutex_lock(&mutex);

    // Attempt to delete the file
    if (remove(rfsFilePath) == 0) {
        pthread_mutex_unlock(&mutex);
        return 1;
    }
    // Release the lock after the file has been removed
    pthread_mutex_unlock(&mutex);
    return 0;
    
}

int ls_handler(lsMsg_t* client_message)
{
  int status = 0;
  // Prepend ROOTDIR to the beginning of the filePath in client_message
  char rfsFilePath[256 + sizeof(ROOTDIR)];
  strcpy(rfsFilePath, ROOTDIR);
  strcat(rfsFilePath, client_message->filePath);

  // Lock the mutex before accessing the shared resource (file)
  pthread_mutex_lock(&mutex);

  // Attempt to delete the file
  if (access(rfsFilePath, F_OK) != 0) {
      pthread_mutex_unlock(&mutex);
      return 0;
  }
  // Call function to read the metadata
  if (read_metadata(client_message->filePath) == 0)
  {
    status = 1;
  }
  // Release the lock after the metadata has been read
  pthread_mutex_unlock(&mutex);
  return status;
}

int write_metadata(const char *origFilePath, const metadata_t *metadata) {
    char metadataFilePath[256 + sizeof(METADIR) + 12];
    sprintf(metadataFilePath, "%smetadata_%s", METADIR, origFilePath);

    FILE *metadataFile = fopen(metadataFilePath, "a");  // Open in append mode
    if (metadataFile == NULL) {
        printf("Error opening metadata file");
        return -1 ;
    }

    fprintf(metadataFile, "%d %s\n", metadata->versionNumber, metadata->timestamp);
    fclose(metadataFile);
    return 0;
}

int read_metadata(const char *origFilePath) {
    char metadataFilePath[256 + sizeof(METADIR) + 12];
    sprintf(metadataFilePath, "%smetadata_%s", METADIR, origFilePath);

    FILE *metadataFile = fopen(metadataFilePath, "r");
    if (metadataFile == NULL) {
        printf("Error opening metadata file");
        return -1;
    }
    printf("File Name: %s\n", origFilePath);
    metadata_t metadata;
    while (fscanf(metadataFile, "%d %s", &metadata.versionNumber, metadata.timestamp) != EOF) {
        printf("\tVersion Number: %d, Timestamp: %s\n", metadata.versionNumber, metadata.timestamp);
    }
    fclose(metadataFile);
    return 0;
}