/*
* genRandWord-oconnell.c / Random Word Generation
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
#include "genRandWord-helper.h"

int main(int argc, char* argv[]) {
	
	// check for correct input
	if (argc < 3 || argc > 4)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

	// set necessary variables
	int numRand = atoi(argv[1]);
	char* fileName = argv[2];
	FILE* fp;
	bool append = false;
    
    // seed the random number generator  
    srand(time(NULL));

	// check for append argument
	if (argc == 4)
	{
		char* option = argv[3];
		if (strcmp(option, "-a") == 0)
		{
			append = true;
		}
		else
		{
			printf("INVALID INPUT - See Below for Help\n\n");
			print_help();
			return -1;
		}
	}

	// open the file in the correct mode
	if (append)
	{
		fp = fopen(fileName, "a");
	}
	else
	{
		fp = fopen(fileName, "w");
	}

	// write to file passed in
	for (int i = 0; i < numRand; i++)
	{
		// char word[] = genRandWord();
		// fprintf(fp,"%s\n", word);
        fprintf(fp,"%s\n", genRandWord());
	}

	// close file
	fclose(fp);

	return 0;

}

