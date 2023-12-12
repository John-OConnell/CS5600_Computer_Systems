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
#include <signal.h> 
#include <time.h>
#include <libgen.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/stat.h>

#include "server-helper.h"

// Define constant for directory locations
#define ROOTDIR "rfsys/"
#define VERSDIR "rfsys/vers/"
#define METADIR "rfsys/meta/"

// Initialize mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/*
 * Handles the different message types sent from the client
 * and responds appropriately
 *
 * @param socket: client socket used to send/recieve messages
 * 
 */
void* client_handler(void* socket) {

  int client_socket = *((int*)socket);
  char message_buffer[MAXFILESIZE + 512];
  int status = -1;

  // Receive client's message:
  if (recv(client_socket, message_buffer, sizeof(message_buffer), 0) < 0)
  {
    perror("Error receiving message from client");
    close(client_socket);
    pthread_exit(NULL);
  }

  // Get the message type of the recieved message
  uint32_t messageType;
  memcpy(&messageType, message_buffer, sizeof(uint32_t));
  
  // Handle various message types
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
      status = ls_handler(ls_message, client_socket);
      free(ls_message);
      break;

    case STOP:
      close(client_socket);
      // Get mutex lock to ensure no other threads are accessing files
      pthread_mutex_lock(&mutex);
      // Set close_server flag
      pthread_mutex_lock(&close_server_mutex);
      close_server = 1;
      pthread_mutex_unlock(&close_server_mutex);
      // Release mutex lock and exit
      pthread_mutex_unlock(&mutex);
      pthread_exit(NULL); // Terminate the current thread
      break;

    default:
      status = 0;
      break;
  }

  // Only send status back on write or remove commands
  // other commands involve sending a message back to the client
  if(messageType == WRITE || messageType == REMOVE)
  {
    // Send status message to client
    if (send(client_socket, &status, sizeof(int), 0) < 0)
    {
      perror("Error sending status to client");
    }
    sleep(1);
  }

  // Closing the socket:
  close(client_socket);
  pthread_exit(NULL);
  
}

/*
 * Handles write commands from the client
 *
 * @param client_message: client message struct
 * 
 * @return: 1 on successful write
 *          0 on failed write
 * 
 */
int write_handler(writeMsg_t* client_message){

  int status = 0;
  int prevVersion = 0;
  int currVersion = 0;

  // Extract the directory part of the path
  char directoryPath[256];
  strcpy(directoryPath, client_message->filePath);
  char* lastSlash = strrchr(directoryPath, '/');
  if (lastSlash != NULL)
  {
      *lastSlash = '\0';  // Remove the file name
  }

  // Get the file name
  char *fileName = basename(client_message->filePath);

  // Get rfs directory path
  char rfsDirPath[256 + sizeof(ROOTDIR)];
  strcpy(rfsDirPath, ROOTDIR);
  strcat(rfsDirPath, directoryPath);

  // Prepend ROOTDIR to the beginning of the filePath in client_message
  char rfsFilePath[256 + sizeof(ROOTDIR)];
  strcpy(rfsFilePath, ROOTDIR);
  strcat(rfsFilePath, client_message->filePath);

  // Lock the mutex before accessing the file
  pthread_mutex_lock(&mutex);

  // If a path was provided instead of just a file name
  if(strcmp(fileName, directoryPath) != 0 )
  {
    // Check if the directory exists, and if not, create it
    struct stat st = {0};
    if (stat(rfsDirPath, &st) == -1) {
        if (mkdir(rfsDirPath, 0700) == -1) {
            perror("mkdir failed");
            pthread_mutex_unlock(&mutex);
            return -1;  // Failed to create the directory
        }
    }
  }

  // Check if file already exists
  if (access(rfsFilePath, F_OK) == 0)
  {
    // Create a new variable to execute the rename function on
    char rfsFilePathTemp[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePathTemp, rfsFilePath);

    // Generate a versioned file name
    char versFilePath[256 + sizeof(VERSDIR) + 5]; // Assuming a version number <= 99999

    // If a path was provided instead of just a file name
    if(strcmp(fileName, directoryPath) != 0 )
    {
      // Generate a versioned file directory
      char versDirPath[256 + sizeof(VERSDIR)]; // Assuming a version number <= 99999
      sprintf(versDirPath, "%s%s", VERSDIR, directoryPath);

      // Check if the directory exists, and if not, create it
      struct stat st = {0};
      if (stat(versDirPath, &st) == -1)
      {
          if (mkdir(versDirPath, 0700) == -1)
          {
              perror("mkdir failed");
              pthread_mutex_unlock(&mutex);
              return -1;  // Failed to create the directory
          }
      }
      sprintf(versFilePath, "%s%s/v%d_%s", VERSDIR, directoryPath, prevVersion, fileName);
      // Check if the versioned file already exists and increment version if necessary
      while (access(versFilePath, F_OK) == 0)
      {
        prevVersion++;
        sprintf(versFilePath, "%s%s/v%d_%s", VERSDIR, directoryPath, prevVersion, fileName);
      }
    }
    // Otherwise it was just a file name that was provided
    else
    {
      sprintf(versFilePath, "%sv%d_%s", VERSDIR, prevVersion, fileName);
      // Check if the versioned file already exists and increment version if necessary
      while (access(versFilePath, F_OK) == 0)
      {
        prevVersion++;
        sprintf(versFilePath, "%sv%d_%s", VERSDIR, prevVersion, fileName);
      }
    }
    // Move the current file into the vers directory with new versioned name
    rename(rfsFilePathTemp, versFilePath);
    // Current version used for updating metadata
    currVersion = ++prevVersion;
  }

  FILE *file = fopen(rfsFilePath, "w");
  if (file == NULL)
  {
      perror("Error opening file to write to");
      // Unlock the mutex before returning on error
      pthread_mutex_unlock(&mutex);
      return -1;
  }

  size_t bytes_written = fwrite(client_message->content, 1, client_message->contentLength, file);
  if (bytes_written != client_message->contentLength)
  {
      perror("Error writing to file");
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

  // Format the timestamp as "YYYY-MM-DD HH:MM:SS"
  strftime(metadata.timestamp, sizeof(metadata.timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

  // Set the version number
  metadata.versionNumber = currVersion;

  if(write_metadata(client_message->filePath, &metadata) == 0)
  {
    status = 1;
  }

  // Unlock the mutex after closing the file
  pthread_mutex_unlock(&mutex);
  return status;
}

/*
 * Handles get commands from the client
 *
 * @param client_message: client message struct
 * @param client_socket: client network socket
 * 
 * @return: 1 on successful get
 *          0 on failed get
 * 
 */
int get_handler(getMsg_t* client_message, int client_socket){

    // Initialize new message to be sent to client
    getRetMsg_t message;
    message.msgType = GETRET;

    // Extract the directory part of the path
    char directoryPath[256];
    strcpy(directoryPath, client_message->filePath);
    char* lastSlash = strrchr(directoryPath, '/');
    if (lastSlash != NULL)
    {
        *lastSlash = '\0';  // Remove the file name
    }

    // Get the file name
    char *fileName = basename(client_message->filePath);

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    // Lock the mutex before accessing the file
    pthread_mutex_lock(&mutex);

    // Construct the versioned file name based on the requested version
    char versFilePath[256 + sizeof(VERSDIR) + 12]; // Adjust buffer size accordingly
    if (client_message->versionNumber >= 0) 
    {
        // If a path was provided instead of just a file name
      if(strcmp(fileName, directoryPath) != 0 )
      {
        sprintf(versFilePath, "%s%s/v%d_%s", VERSDIR, directoryPath, client_message->versionNumber, fileName);
      }
      // Otherwise it was just a file name that was provided
      else
      {
        sprintf(versFilePath, "%sv%d_%s", VERSDIR, client_message->versionNumber, fileName);
      }
    } else 
    {
        // Otherwise, use the default file path
        strcpy(versFilePath, rfsFilePath);
    }

    // Open the file for reading
    FILE* file = fopen(versFilePath, "r");
    // If the file can't be found on the server, update the fileFound flag
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

    // Update fileFound flag
    message.fileFound = 1;

    // Get the size of the file
    fseek(file, 0, SEEK_END);
    message.contentLength = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    // Read the file content into the struct
    fread(message.content, 1, message.contentLength, file);

    fclose(file);

    // Unlock the mutex after closing the file
    pthread_mutex_unlock(&mutex);

    // Copy message struct into buffer
    char buffer[sizeof(getRetMsg_t)];
    memcpy(buffer, &message, sizeof(getRetMsg_t));

    // Send the message buffer over the network
    if (send(client_socket, buffer, sizeof(getRetMsg_t), 0) < 0) {
        perror("File retrieval message failed to send to client");
        return 0;
    }

    return 1;
}

/*
 * Handles remove commands from the client
 *
 * @param client_message: client message struct
 * 
 * @return: 1 on successful removal
 *          0 on failed removal
 * 
 */
int remove_handler(removeMsg_t* client_message){
    // Get the directory part of the original file path
    char directoryPath[256];
    strncpy(directoryPath, client_message->filePath, sizeof(directoryPath));
    char *lastSlash = strrchr(directoryPath, '/');
    if (lastSlash != NULL) {
        *lastSlash = '\0';  // Remove the file name
    }

    // Get the file name
    char *fileName = basename(client_message->filePath);

    // Prepend ROOTDIR to the beginning of the filePath in client_message
    char rfsFilePath[256 + sizeof(ROOTDIR)];
    strcpy(rfsFilePath, ROOTDIR);
    strcat(rfsFilePath, client_message->filePath);

    // Lock the mutex before accessing the file
    pthread_mutex_lock(&mutex);

    // Attempt to delete the file
    if (remove(rfsFilePath) == 1) {
        pthread_mutex_unlock(&mutex);
        return 0;
    }
    
    char metadataFilePath[256 + sizeof(METADIR) + 12];
    // If a path was provided instead of just a file name
    if(strcmp(fileName, directoryPath) != 0 )
    {
      // Remove metadata file
      sprintf(metadataFilePath, "%s%s/metadata_%s", METADIR, directoryPath, fileName);
    }
    // Otherwise it was just a file name that was provided
    else
    {
      sprintf(metadataFilePath, "%smetadata_%s", METADIR, fileName);
    }

    remove(metadataFilePath);

    // Remove versioned files
    int version = 0;
    char versFilePath[256 + sizeof(VERSDIR) + 12];
    // If a path was provided instead of just a file name
    if(strcmp(fileName, directoryPath) != 0 )
    {
      sprintf(versFilePath, "%s%s/v%d_%s", VERSDIR, directoryPath, version, fileName);

      while (access(versFilePath, F_OK) == 0) {
          remove(versFilePath);
          version++;
          sprintf(versFilePath, "%s%s/v%d_%s", VERSDIR, directoryPath, version, fileName);
      }
    }
    // Otherwise it was just a file name that was provided
    else
    {
      sprintf(versFilePath, "%sv%d_%s", VERSDIR, version, fileName);

      while (access(versFilePath, F_OK) == 0) {
          remove(versFilePath);
          version++;
          sprintf(versFilePath, "%sv%d_%s", VERSDIR, version, fileName);
      }
    }

    //  Unlock the mutex after the file has been removed
    pthread_mutex_unlock(&mutex);
    return 1;
    
}

/*
 * Handles ls commands from the client
 *
 * @param client_message: client message struct
 * @param client_socket: client network socket
 * 
 * @return: 1 on successful ls
 *          0 on failed ls
 * 
 */
int ls_handler(lsMsg_t* client_message, int client_socket) {
  int status = 0;

  // Prepend ROOTDIR to the beginning of the filePath in client_message
  char rfsFilePath[256 + sizeof(ROOTDIR)];
  strcpy(rfsFilePath, ROOTDIR);
  strcat(rfsFilePath, client_message->filePath);

  // Lock the mutex before accessing file
  pthread_mutex_lock(&mutex);

  // Check if file exists
  if (access(rfsFilePath, F_OK) != 0) {
      // Define special metadata struct for the end of the stream
      metadata_t endOfStreamMetadata = { "", -1 };

      // Send the end of stream marker
      char endOfStreamBuffer[sizeof(metadata_t)];
      memcpy(endOfStreamBuffer, &endOfStreamMetadata, sizeof(metadata_t));
      if (send(client_socket, endOfStreamBuffer, sizeof(endOfStreamBuffer), 0) < 0)
      {
          perror("Error sending end of stream marker to client");
          return -1;
      }
      // Unlock the mutex before returning
      pthread_mutex_unlock(&mutex);
      return 0;
  }
  // Call function to read the metadata
  if (send_metadata(client_message->filePath, client_socket) == 0)
  {
    status = 1;
  }
  // Unlock the mutex after the metadata has been read
  pthread_mutex_unlock(&mutex);
  return status;
}

/*
 * Write metadata information to appropriate metadata file
 *
 * @param origFilePath: file path to message
 * @param metadata: struct containing metadata
 * 
 * @return: 0 on successful write
 *
 */
int write_metadata(char *origFilePath, const metadata_t *metadata) {
  // Get the directory part of the original file path
  char directoryPath[256];
  strncpy(directoryPath, origFilePath, sizeof(directoryPath));
  char *lastSlash = strrchr(directoryPath, '/');
  if (lastSlash != NULL) {
      *lastSlash = '\0';  // Remove the file name
  }

  // Get the file name
  char *fileName = basename(origFilePath);

  // Get the necessary path in the metadata directory
  char metadataFilePath[256 + sizeof(METADIR) + 12];

  // If a path was provided instead of just a file name
  if(strcmp(fileName, directoryPath) != 0 )
  {
    // Prepend METADIR to the beginning of the directory path
    char metadataDirPath[256 + sizeof(METADIR)];
    strcpy(metadataDirPath, METADIR);
    strcat(metadataDirPath, directoryPath);

    // Check if the directory exists, and if not, create it
    struct stat st = {0};
    if (stat(metadataDirPath, &st) == -1) {
        if (mkdir(metadataDirPath, 0700) == -1) {
            perror("mkdir failed");
            pthread_mutex_unlock(&mutex);
            return -1;  // Failed to create the directory
        }
    }
    // Construct metadata file path
    sprintf(metadataFilePath, "%s/metadata_%s", metadataDirPath, fileName);
  }
  // Otherwise it was just a file name that was provided
  else
  {
    // Construct metadata file path
    sprintf(metadataFilePath, "%smetadata_%s", METADIR, fileName);
  }

  // Write to metadata file
  FILE *metadataFile = fopen(metadataFilePath, "a");  // Open in append mode
  if (metadataFile == NULL) {
      perror("Error opening metadata file");
      return -1 ;
  }
  fprintf(metadataFile, "%d %s\n", metadata->versionNumber, metadata->timestamp);
  fclose(metadataFile);

  return 0;
}

/*
 * Send metadata to a client
 *
 * @param origFilePath: file path to message
 * @param client_socket: client network socket
 * 
 * @return: 0 on successful send
 *          -1 on failed send
 * 
 */
int send_metadata(char *origFilePath, int client_socket) {
  // Get the directory part of the original file path
  char directoryPath[256];
  strncpy(directoryPath, origFilePath, sizeof(directoryPath));
  char *lastSlash = strrchr(directoryPath, '/');
  if (lastSlash != NULL)
  {
      *lastSlash = '\0';  // Remove the file name
  }

  // Get the file name
  char *fileName = basename(origFilePath);

  // Get the necessary path in the metadata directory
  char metadataFilePath[256 + sizeof(METADIR) + 12];

  // If a path was provided instead of just a file name
  if(strcmp(fileName, directoryPath) != 0 )
  {
    // Prepend METADIR to the beginning of the directory path
    char metadataDirPath[256 + sizeof(METADIR)];
    strcpy(metadataDirPath, METADIR);
    strcat(metadataDirPath, directoryPath);

    // Check if the directory exists, and if not, create it
    struct stat st = {0};
    if (stat(metadataDirPath, &st) == -1) {
        if (mkdir(metadataDirPath, 0700) == -1) {
            perror("mkdir failed");
            pthread_mutex_unlock(&mutex);
            return -1;  // Failed to create the directory
        }
    }
    // Construct metadata file path
    sprintf(metadataFilePath, "%s/metadata_%s", metadataDirPath, fileName);
    }
    // Otherwise it was just a file name that was provided
    else
    {
      // Construct metadata file path
      sprintf(metadataFilePath, "%smetadata_%s", METADIR, fileName);
    }

    // Open metadata file
    FILE *metadataFile = fopen(metadataFilePath, "r");
    if (metadataFile == NULL) {
        perror("Error opening metadata file");
        return -1;
    }

    // Read from metadata file, sending a new message for each line
    metadata_t metadata;
    while (fscanf(metadataFile, "%d %[^\n]", &metadata.versionNumber, metadata.timestamp) != EOF)
    {
        // Create a buffer to hold metadata and send it to the client
        char buffer[sizeof(metadata_t)];
        memcpy(buffer, &metadata, sizeof(metadata_t));

        if (send(client_socket, buffer, sizeof(buffer), 0) < 0) {
            perror("Error sending metadata to client");
            fclose(metadataFile);
            return -1;
        }
    }

    // Define a special metadata struct for the end of the stream
    metadata_t endOfStreamMetadata = { "", -1 };

    // Send the end of stream marker
    char endOfStreamBuffer[sizeof(metadata_t)];
    memcpy(endOfStreamBuffer, &endOfStreamMetadata, sizeof(metadata_t));
    if (send(client_socket, endOfStreamBuffer, sizeof(endOfStreamBuffer), 0) < 0)
    {
        perror("Error sending end of stream marker to client");
        return -1;
    }

    fclose(metadataFile);
    return 0;
}
