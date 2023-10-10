/*
* genRandWord-helper.c / Random Number Generation
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genRandWord-helper.h"

#define MAX_WORD_LENGTH 10;

/*
 * Prints the help message for the arger-oconnell program
 * 
 */
void print_help(){
	printf("genRandWords. (2023 Sep 12)\n\n");
	printf("Usage: genRandWord (<num-of-rand-words> ");
	printf("<file>) [arguments]\n");
	printf("Arguments:\n");
	printf("  -a            Appends words to file if file already\n");
	printf("		exists, if this argument is not included\n");
        printf("		file will be overwritten.\n");
}


/*
 * Generates a random word
 * 
 * @return word: a random word generated using rand() function
 * 
 */
char* genRandWord(){
    
    int length = (rand() % 10 + 1);

    char* word = (char*)malloc((length + 1) * sizeof(char));
    if(word == NULL)
    {
        return NULL;
    }
    
    for(int i = 0; i < length; i++)
    {
        char letter = (char) 97 + (rand() % 26);
        word[i] = letter;
    }

    word[length] = '\0';
    
	return word;

}

