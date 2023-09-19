/*
* genRand-helper.c / Random Number Generation
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>
#include "genRand-helper.h"

/*
 * Prints the help message for the arger-oconnell program
 * 
 */
void print_help(){
	printf("genRand. (2023 Sep 12)\n\n");
	printf("Usage: genRand (<num-of-rand-ints> ");
	printf("<file>) [arguments]\n");
	printf("Arguments:\n");
	printf("  -a            Appends numbers to file if file already\n");
	printf("		exists, if this argument is not included\n");
        printf("		file will be overwritten.\n");
}

/*
 * Compares two strings
 *
 * @param str1: the first string to be compared
 * @param str2: the second string to be compared
 *
 * @return returns less than, equal to, or greater than 0
 * 	   if str1 is lexographically less than, greater
 * 	   than, or equal to str2
 * 
 */
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

/*
 * Assigns a seed value to be used in genRand
 *
 * @param seed: pointer to the seed to be used in genRand
 * @param value: value to assign to the seed
 * 
 */
void setSeed(int* seed, int value){
	if(!seed)
	{
		printf("Invalid seed pointer!");
		return;
	}

	*seed = value;
	return;
}

/*
 * Generates a random number within a given range
 * Uses the Linear Congruential Generator (LCG) algorithm
 *
 * @param min: minimum value for random number range
 * @param max: maximum value for random number range
 * @param seed: pointer to seed value to start the random number generator
 * 
 * @return rand: a pseudo random number generated using LCG
 * 
 */
int genRand(int min, int max, int* seed){


	unsigned long long a = 214013;
	unsigned long long c = 2531011;
	unsigned long long m = (1ULL << 31) - 1;
	
	int rand = (((*seed) * a + c) & m) >> 16;
	setSeed(seed, rand);

	rand = (rand % max) + min;

	return rand;

}

