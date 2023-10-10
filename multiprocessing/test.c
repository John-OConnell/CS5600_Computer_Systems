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

        char* allocatedLine = strdup(line); // Allocate memory for the line and copy the content
        if (allocatedLine == NULL)
        {
            perror("Memory allocation failed");
            return -1;
        }
        add2q(Q, allocatedLine);
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
        printf("%s\n", word);
        free(word);
    //    // Create a batch file to hold BATCH_SIZE words
    //     if (wordCount == 0) 
    //     {
    //         // Generate a unique batch file name
    //         current_time = time(NULL);
    //         snprintf(outputFileName, sizeof(outputFileName), "batch_%d.txt", processCount);
    //         printf("Made it inside!\n");
    //         // Open the batch file for writing
    //         batchFile = fopen(outputFileName, "w");
    //         if (!batchFile) 
    //         {
    //             perror("Error opening batch file");
    //             return -1;
    //         }
    //     }
    //     if (!batchFile) 
    //     {
    //         printf("something went wrong\n");
    //     }

    //     // Write the word to the current batch file
    //     //fprintf(batchFile, "%s\n", word);
    //     wordCount++;
    }

    fclose(batchFile);

    // free the queue
    freeQ(Q);

	return 0;

}
