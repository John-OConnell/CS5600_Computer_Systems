/*
* cipher.c / Create Cipher
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 26, 2023
*
*/

#include <stdio.h>
#include <string.h>
#include "polybius.h"

// define the polybius square
// only the special characters included in the square are processed
// all other special characters are ignored
char pbSquare[SQUARE_SIZE][SQUARE_SIZE] = {
    {':', ';', '<', '=', '>', '?'},
    {'@', 'A', 'B', 'C', 'D', 'E'},
    {'F', 'G', 'H', 'I', 'J', 'K'},
    {'L', 'M', 'N', 'O', 'P', 'Q'},
    {'R', 'S', 'T', 'U', 'V', 'W'},
    {'X', 'Y', 'Z', '[', '\\', ']'}
};

int main(int argc, char* argv[]) {
	
	// check that correct # of arguments are passed in
	if (argc != 2)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
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
    
    // set line buffer
    char line[256];

    // Read each word from the file and pass it to encode function
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove the newline character
        pbEncode(line, pbSquare);
    }

}
