/*
* genRand-oconnell.c / Random Number Generation
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "genRand-helper.h"

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
	int seed;

	// check for append argument
	if (argc == 4)
	{
		char* option = argv[3];
		if (mystrcmp(option, "-a") == 0)
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

	// set seed to number passed in
	setSeed(&seed, numRand);

	// write to file passed in
	for (int i = 0; i < numRand; i++)
	{
		int num = genRand(1, 100, &seed);
		fprintf(fp,"%d\n", num);
	}

	// close file
	fclose(fp);

	return 0;

}

