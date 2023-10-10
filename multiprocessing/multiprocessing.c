/*
* multiprocessing.c / Multiprocessing
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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "queue.h"
#include "polybius.h"
#include "multiprocessing-helper.h"

#define BATCH_SIZE 100

int main(int argc, char* argv[]) {
	
	// check for correct input
	if (argc != 2)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help_multi();
		return -1;
	}

	// set necessary file variables
    char* fileName = argv[1];
	FILE* fp;

	// open the file in read mode
	fp = fopen(fileName, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    // create a queue
    queue_t* Q = createQ();

    // set line buffer
    char line[256];

	// read each word from file and add it into the queue
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        line[strcspn(line, "\n")] = '\0'; // remove the newline character
        char* allocatedLine = strdup(line); // allocate memory for the line and copy the content
        if (allocatedLine == NULL)
        {
            perror("Memory allocation failed");
            return -1;
        }
        add2q(Q, allocatedLine);
    }

	// close file
	fclose(fp);    

    // create unique output file names
    time_t current_time;
    char batchFileName[256];
    char outputFileName[256];

    char* word;
    int wordCount = 0;
    int processCount = 0;
    FILE* batchFile = NULL;

    // process each word from the queue in batches of BATCH_SIZE
    while ((word = popQ(Q)) != NULL) 
    {
        // if wordCount == 0, create a batch file to hold BATCH_SIZE words
        if (wordCount == 0) 
        {
            // generate a unique batch file name
            snprintf(batchFileName, sizeof(outputFileName), "batch_%d.txt", processCount);

            // open the batch file for writing
            batchFile = fopen(batchFileName, "w");
            if (!batchFile) 
            {
                perror("Error opening batch file");
                return -1;
            }
        }

        // write the word to the current batch file and free word
        fprintf(batchFile, "%s\n", word);
        free(word);
        wordCount++;

        // if we've reached BATCH_SIZE, invoke the cipher program for the batch
        if (wordCount >= BATCH_SIZE)
        {
            fclose(batchFile);

            // generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // create a subprocess to invoke the cipher function for the batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            }
            // child process
            else if (pid == 0)
            {
                invokeCipher(batchFileName, outputFileName);
                exit(0);
            } 
            // parent process
            else
            {
                // wait for the child process to complete
                int status;
                waitpid(pid, &status, 0);

                // clean up the batch file and update variables
                remove(batchFileName);
                wordCount = 0;
                processCount++;
            }
        }
    }

    // if there are remaining words in the last batch, invoke the cipher function
    if (wordCount > 0) 
    {
            fclose(batchFile);

            // generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // create a subprocess to invoke the cipher function for the last batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            }
            // child process
            else if (pid == 0)
            {
                invokeCipher(batchFileName, outputFileName);
                exit(0);
            }
            // parent process
            else
            {
                // Wait for the child process to complete
                int status;
                waitpid(pid, &status, 0);

                // clean up the batch file and update variables
                remove(batchFileName);
                processCount++;
            }
    }

    // free the queue
    freeQ(Q);

	return 0;
}
