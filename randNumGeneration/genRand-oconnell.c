/*
* OConnellJ.CS5600.LearnC.c / Random Number Generation
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

	if (argc < 3)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

	int numRand = atoi(argv[1]);
	char* fileName = argv[2];
	FILE* fp;
	bool append = false;
	int seed;

	if (argc > 3)
	{
		char* option = argv[3];
		if (mystrcmp(option, "-a") == 0)
		{
			printf("here\n");
			append = true;
		}
	}

	if (append)
	{
		printf("here2\n");
		fp = fopen(fileName, "a");
	}
	else
	{
		printf("here3\n");
		fp = fopen(fileName, "w");
	}

	setSeed(&seed, 1);

	for (int i = 0; i < numRand; i++)
	{
		int num = genRand(1, 10, &seed);
		fprintf(fp,"%d\n", num);
	}

	fclose(fp);

	return 0;
}
