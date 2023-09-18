/*
* arger-oconnell-helper.c / Command Line Arguments
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 12, 2023
*
*/

#include <stdio.h>
#include "arger-oconnell-helper.h"

void print_help(){
	printf("arger-oconnell. (2023 Sep 12)\n\n");
	printf("Usage: arger-oconnell (arguments)");
	printf(" <your_text_here>\n\n");
	printf("Arguments:\n");
	printf("  -u            Display text in all uppercase.\n");
	printf("  -l            Display text in all lowercase.\n");
	printf("  -cap          Display text with first letter of each word"); 
	printf(" capitalized.\n");
	printf("  -h  or  --h   Print this help message.\n");
}

int mystrcmp(const char* str1, const char* str2){

	const unsigned char *l1 = (const unsigned char *) str1;
	const unsigned char *l2 = (const unsigned char *) str2;
	unsigned  char p1, p2;

	do
	{
		p1 = (const char) *l1++;
		p2 = (const char) *l2++;
		if ( p1 == '\0')
		{
			return p1 - p2;
		}
	} while (p1 == p2);
	return p1 - p2;
}

void to_upper(int argc, char* argv[]){

	for (int i = 2; i < argc; i++)
	{	
		int j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] >= 97 && argv[i][j] <= 122)
			{
				argv[i][j] -= 32;
			}	
			j++;
		}
		if (i < argc - 1)
		{
			printf("%s ", argv[i]);
		}
		else
		{
			printf("%s\n", argv[i]);
		}
	}	
	return;
}

void to_lower(int argc, char* argv[]){

	for (int i = 2; i < argc; i++)
	{	
		int j = 0;
		while (argv[i][j] != '\0')
		{
			if (argv[i][j] >= 65 && argv[i][j] <= 90)
			{
				argv[i][j] += 32;
			}	
			j++;
		}
		if (i < argc - 1)
		{
			printf("%s ", argv[i]);
		}
		else
		{
			printf("%s\n", argv[i]);
		}
	}	
	return;
}

void to_cap(int argc, char* argv[]){

	for (int i = 2; i < argc; i++)
	{	
		int j = 0;
		while (argv[i][j] != '\0')
		{
			if (j == 0 && argv[i][j] >= 97 && argv[i][j] <= 122)
			{
				argv[i][j] -= 32;
			}
			else if (j != 0 && argv[i][j] >= 65 && argv[i][j] <= 90)
			{
				argv[i][j] += 32;
			}	
			j++;
		}
		if (i < argc - 1)
		{
			printf("%s ", argv[i]);
		}
		else
		{
			printf("%s\n", argv[i]);
		}
	}	
	return;
}
