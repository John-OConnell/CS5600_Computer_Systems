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

/*
 * Prints the help message for the multiprocessing program
 * 
 */
void print_help_multi(){
	printf("multiprocessing. (2023 Oct 8)\n\n");
	printf("Usage: multiprocess <file_name>\n");
}

/*
 * Invokes the cipher program as a subprocess
 *
 * @param inputFileName: file that the function will read from
 * @param outputFileName: file that the function will pipe to
 * 
 */
void invokeCipher(const char* inputFileName, const char* outputFileName) {
    char command[256];
    // pipe output of cipher program to output file
    snprintf(command, sizeof(command), "./cipher %s > %s", inputFileName, outputFileName);
    system(command);
}

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

    // create unique output file names using timestamps
    time_t current_time;
    char batchFileName[256];
    char outputFileName[256];

    int processCount = 0;
    char* word;
    int wordCount = 0;
    FILE* batchFile = NULL;

    // process each word from the queue in batches of BATCH_SIZE
    while ((word = popQ(Q)) != NULL) 
    {
        // if wordCount == 0, create a batch file to hold BATCH_SIZE words
        if (wordCount == 0) 
        {
            // generate a unique batch file name
            current_time = time(NULL);
            snprintf(batchFileName, sizeof(outputFileName), "batch_%d.txt", processCount);

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

            // generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // create a subprocess to invoke the cipher program for the batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            }
            else if (pid == 0) // child process
            {
                invokeCipher(batchFileName, outputFileName);
                // exit(0);
            } 
            else
            {   // parent process
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

    // if there are remaining words in the last batch, invoke the cipher program
    if (wordCount > 0) 
    {
            fclose(batchFile);

            // generate a unique output file for the ciphered batch
            current_time = time(NULL);
            snprintf(outputFileName, sizeof(outputFileName), "output_%d_%ld.txt", processCount, current_time);

            // create a subprocess to invoke the cipher program for the last batch
            pid_t pid = fork();

            if (pid < 0)
            {
                perror("Fork failed");
                return -1;
            } 
            else if (pid == 0) // child process
            {
                invokeCipher(batchFileName, outputFileName);
                exit(0);
            } 
            else
            {   // parent process
                // Wait for the child process to complete
                int status;
                waitpid(pid, &status, 0);

                // clean up the batch file and update variables
                remove(batchFileName);
                processCount++;
            }
    }

    // free the queue
    printf("freeing q\n");
    freeQ(Q);

	return 0;

}
