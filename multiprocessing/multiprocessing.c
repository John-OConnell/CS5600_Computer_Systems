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

#define BATCH_SIZE 100

// Function to invoke the cipher program as a subprocess
void invokeCipher(const char* inputFileName, const char* outputFileName) {
    char command[256];
    snprintf(command, sizeof(command), "./cipher %s > %s", inputFileName, outputFileName);
    system(command);
}


int main(int argc, char* argv[]) {
	
	// check for correct input
	if (argc != 2)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		// print_help();
		return -1;
	}

	// set necessary file variables
    char* fileName = argv[1];
	FILE* fp;


	// open the file in the correct mode
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
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        add2q(Q, line);
    }

	// close file
	fclose(fp);    

    // Create unique output file names based on timestamps
    time_t current_time;
    char outputFileName[256];

    int processCount = 0;
    char* word;
    int wordCount = 0;
    FILE* batchFile = NULL;

    // Process each word from the queue in batches of BATCH_SIZE
    while ((word = popQ(Q)) != NULL) 
    {
        // Create a batch file to hold BATCH_SIZE words
        if (wordCount == 0) 
        {
            // Generate a unique batch file name
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "batch_%d.txt", processCount);

            // Open the batch file for writing
            FILE* batchFile = fopen(outputFileName, "w");
            if (!batchFile) 
            {
                perror("Error opening batch file");
                return -1;
            }
        }

        // Write the word to the current batch file
        printf("here");
        printf("%s", word);
        fprintf(batchFile, "%s\n", word);
        printf("here\n");
        wordCount++;

        // If we've reached BATCH_SIZE, invoke the cipher program for the batch
        if (wordCount >= BATCH_SIZE)
        {
            fclose(batchFile);

            // Generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // Create a subprocess to invoke the cipher program for the batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            }
            else if (pid == 0) // Child process
            {
                char command[256];
                snprintf(command, sizeof(command), "invokeCipher(batch_%d.txt, outputFileName)", processCount);
                system(command);
                // invokeCipher(outputFileName, "batch.txt");
                exit(0);
            } 
            else
            {   
                // Parent process
                // Wait for the child process to complete
                int status;
                waitpid(pid, &status, 0);

                // Clean up the batch file
                remove("batch.txt");
                wordCount = 0;
                processCount++;
            }
        }
    }

    // If there are remaining words in the last batch, invoke the cipher program
    if (wordCount > 0) 
    {
            fclose(batchFile);

            // Generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // Create a subprocess to invoke the cipher program for the last batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            } 
            else if (pid == 0) 
            { // Child process
            invokeCipher(outputFileName, "batch.txt");
            exit(0);
            } 
            else
            { // Parent process
            // Wait for the child process to complete
            int status;
            waitpid(pid, &status, 0);

            // Clean up the batch file
            remove("batch.txt");
            processCount++;
            }
    }

    // free the queue
    freeQ(Q);

	return 0;

}
