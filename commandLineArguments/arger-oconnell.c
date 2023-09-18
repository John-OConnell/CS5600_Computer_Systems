/*
* arger-oconnell.c / Command Line Arguments
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 12, 2023
*
*/

#include <stdio.h>
#include "arger-oconnell-helper.h"

int main(int argc, char* argv[]) {
	
	if (argc < 3)
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}

	char* option = argv[1];
	int in_len = argc - 2;
	char* input[in_len];	

	if (mystrcmp(option, "-u") == 0)
	{
		to_upper(argc, argv);
		return 0;
	}
	else if (mystrcmp(option, "-l") == 0)
	{
		to_lower(argc, argv);
		return 0;
	}
	else if (mystrcmp(option, "-cap") == 0)
	{
		to_cap(argc, argv);
		return 0;
	}
	else if (mystrcmp(option, "-h") == 0 || mystrcmp(option, "--h") == 0)
	{
		print_help();
		return 0;
	}
	else
	{
		printf("INVALID INPUT - See Below for Help\n\n");
		print_help();
		return -1;
	}
}

