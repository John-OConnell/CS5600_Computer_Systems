/*
* multithreading.c / Multithreading
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <pthread.h>
#include "queue.h"
#include "multithreading-helper.h"

#define BATCH_SIZE 100

int main(int argc, char* argv[]) {
    // check for correct input
    if (argc != 2) {
        printf("INVALID INPUT - See Below for Help\n\n");
        print_help_multi();
        return -1;
    }

    // set necessary file variables
    char* fileName = argv[1];
    FILE* fp;

    // open the file in the read mode
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Error opening file");
        return -1;
    }

    // create a queue
    queue_t* Q = createQ();

    // set line buffer
    char line[256];

    // read each word from the file and add it into the queue
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // remove the newline character
        char* allocatedLine = strdup(line); // allocate memory for the line and copy the content
        if (allocatedLine == NULL) {
            perror("Memory allocation failed");
            return -1;
        }
        add2q(Q, allocatedLine);
    }

    // close the file
    fclose(fp);

    // create unique output file names
    time_t current_time;
    char batchFileName[256];
    char outputFileName[256];
    pthread_t threads[BATCH_SIZE];
    int args[BATCH_SIZE];

    char* word;
    int wordCount = 0;
    int batchCount = 0;
    FILE* batchFile = NULL;

    // process each word from the queue in batches of BATCH_SIZE
    while ((word = popQ(Q)) != NULL) 
    {
        // if wordCount == 0, create a batch file to hold BATCH_SIZE words
        if (wordCount == 0) 
        {
            // generate a unique batch file name
            snprintf(batchFileName, sizeof(batchFileName), "batch_%d.txt", batchCount);

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

         // if we've reached BATCH_SIZE, invoke the cipher function for the batch
        if (wordCount >= BATCH_SIZE)
        {
            fclose(batchFile);

            // update args array with correct batch num
            args[batchCount] = batchCount;
            pthread_create(&threads[batchCount], NULL, invokeCipher, &args[batchCount]);
            wordCount = 0;
            batchCount++;
        }
    }

    // if there are remaining words in the last batch, invoke the cipher function
    if (wordCount > 0) 
    {
            fclose(batchFile);

            // update args array with correct batch num
            args[batchCount] = batchCount;
            pthread_create(&threads[batchCount], NULL, invokeCipher, &args[batchCount]);
            batchCount++;
    }


    // wait for all threads to finish
    for (int i = 0; i < batchCount; i++) {
        pthread_join(threads[i], NULL);
    }

    // Free the queue and allocated line memory
    // while (!(qsize(Q)==0)) {
    //     free(popQ(Q));
    // }
    freeQ(Q);

    return 0;
}
