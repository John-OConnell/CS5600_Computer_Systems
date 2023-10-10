/*
* multiprocessing-helper.c / Multiprocessing
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "multiprocessing-helper.h"

/*
 * Prints the help message for the multiprocessing program
 * 
 */
void print_help_multi(){
	printf("multiprocessing. (2023 Oct 8)\n\n");
	printf("Usage: multiprocess <file_name>\n");
}

/*
 * Invokes the cipher program used to pipe encoded output to a file
 *
 * @param inputFileName: file that the function will read from
 * @param outputFileName: file that the function will pipe to
 * 
 */
void invokeCipher(const char* inputFileName, const char* outputFileName) {
    char command[256];
    // pipe output of cipher program to output file
    snprintf(command, sizeof(command), "./cipher %s > output/%s", inputFileName, outputFileName);
    system(command);
}