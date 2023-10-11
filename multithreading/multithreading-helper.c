/*
* multithreading-helper.c / Multithreading
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "polybius.h"
#include "multithreading-helper.h"

char pbSquare[SQUARE_SIZE][SQUARE_SIZE] = {
    {':', ';', '<', '=', '>', '?'},
    {'@', 'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'J', 'K'},
    {'L', 'M', 'N', 'O', 'P', 'Q'},
    {'R', 'S', 'T', 'U', 'V', 'W'},
    {'X', 'Y', 'Z', '[', '\\', ']'}
};

/*
 * Prints the help message for the multiprocessing program
 * 
 */
void print_help_multi(){
	printf("multithreading. (2023 Oct 8)\n\n");
	printf("Usage: multithread <file_name>\n");
}

/*
 * Invokes the cipher program used to write encoded output to a file
 *
 * @param data: file that the function will read from
 * 
 */
void* invokeCipher(void* data) {
    // convert data to int
    int batchCount = *(int*)data;
    
    char batchFileName[256];
    char outputFileName[256];
    snprintf(batchFileName, sizeof(batchFileName), "batch_%d.txt", batchCount);

    // Generate a unique output file for the ciphered batch
    time_t current_time = time(NULL);
    snprintf(outputFileName, sizeof(outputFileName), "output/output_%d_%ld.txt", batchCount, current_time);

    FILE* fp;
    // open the input file in read mode
	fp = fopen(batchFileName, "r");
    if (fp == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    FILE* fp2;
    // open the output file in write mode
    fp2 = fopen(outputFileName, "w");
    if (fp == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    char line[256];

    // Read each word from input file, encode it and write it to output file
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        char* word = pbEncode(line, pbSquare);
        fprintf(fp2, "%s", word);
        fprintf(fp2, "\n");
        free(word);
    }

    fclose(fp);
    fclose(fp2);
    remove(batchFileName);

    return NULL;
}