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
	if (argc < 3)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

	// get necessary variables from input
	char* option = argv[1];

	// process input
    // encryption selection
	if (strcmp(option, "-e") == 0)
	{
        pbEncode(argv[2], pbSquare);
        printf("\n");
		return 0;
	}
    // decryption selection
	else if (strcmp(option, "-d") == 0)
	{
        pbDecode(argv[2], pbSquare);
        printf("\n");
		return 0;
	}
    // help selection
	else if (strcmp(option, "-h") == 0 || strcmp(option, "--h") == 0)
	{
		print_help();
		return 0;
	}
    // catch all other incorrect input
	else
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}
}
