#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "queue.h"
#include "polybius.h"

#define BATCH_SIZE 100

char pbSquare[SQUARE_SIZE][SQUARE_SIZE] = {
    {':', ';', '<', '=', '>', '?'},
    {'@', 'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'J', 'K'},
    {'L', 'M', 'N', 'O', 'P', 'Q'},
    {'R', 'S', 'T', 'U', 'V', 'W'},
    {'X', 'Y', 'Z', '[', '\\', ']'}
};

// Function to invoke the cipher program as a thread
void* invokeCipher(void* data) {
    printf("cipher invoked\n");
    printf("%s\n", (char*) data);
    char* inputFileName = (char*)data;
    printf("%s\n", inputFileName);
    char outputFileName[256];

    // Generate a unique output file for the ciphered batch
    time_t current_time = time(NULL);
    snprintf(outputFileName, sizeof(outputFileName), "output_%ld.txt", current_time);

    FILE* fp;
    FILE* fp2;

	// open the file in the correct mode
	fp = fopen(inputFileName, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    fp2 = fopen(outputFileName, "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    char line[256];

    // Read each word from the file and add it into the queue
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        char* word = pbEncode(line, pbSquare);
        fprintf(fp2, "%s", word);
        fprintf(fp2, "\n");
        free(word);
    }

    fclose(fp);

    fclose(fp2);

    return NULL;
}

int main(int argc, char* argv[]) {
    // Check for correct input
    if (argc != 2) {
        printf("INVALID INPUT - See Below for Help\n\n");
        // print_help();
        return -1;
    }

    // Set necessary file variables
    char* fileName = argv[1];
    FILE* fp;

    // Open the file in the correct mode
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // Create a queue
    queue_t* Q = createQ();

    // Set line buffer
    char line[256];

    // Read each word from the file and add it into the queue
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        char* allocatedLine = strdup(line); // Allocate memory for the line and copy the content
        if (allocatedLine == NULL) {
            perror("Memory allocation failed");
            return -1;
        }
        add2q(Q, allocatedLine);
    }

    printf("Queue size: %d\n", qsize(Q));

    // Close the file
    fclose(fp);

    // create unique output file names using timestamps
    time_t current_time;
    char batchFileName[256];
    char outputFileName[256];
    pthread_t threads[BATCH_SIZE];

    int batchCount = 0;
    char* word;
    int wordCount = 0;
    FILE* batchFile = NULL;

    while ((word = popQ(Q)) != NULL) 
    {
        // if wordCount == 0, create a batch file to hold BATCH_SIZE words
        if (wordCount == 0) 
        {
            // generate a unique batch file name
            current_time = time(NULL);
            snprintf(batchFileName, sizeof(outputFileName), "batch_%d.txt", batchCount);

            // open the batch file for writing
            batchFile = fopen(batchFileName, "w");
            if (!batchFile) 
            {
                perror("Error opening batch file");
                return -1;
            }
        }

        // write the word to the current batch file
        fprintf(batchFile, "%s\n", word);
        free(word);
        wordCount++;

         // if we've reached BATCH_SIZE, invoke the cipher program for the batch
        if (wordCount >= BATCH_SIZE)
        {
            fclose(batchFile);

            pthread_create(&threads[batchCount], NULL, invokeCipher, batchFileName);
            batchCount++;
        }
    }

    // if there are remaining words in the last batch, invoke the cipher program
    if (wordCount > 0) 
    {
            fclose(batchFile);
            printf("here\n");
            printf("%s\n", batchFileName);
            pthread_create(&threads[batchCount], NULL, invokeCipher, batchFileName);
            batchCount++;
    }


    // Wait for all threads to finish
    for (int i = 0; i < batchCount; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free the queue and allocated line memory
    while (!(qsize(Q)==0)) {
        free(popQ(Q));
    }
    freeQ(Q);

    return 0;
}
