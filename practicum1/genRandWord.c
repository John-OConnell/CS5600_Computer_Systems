//
// genRandWord.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "genRandWord.h"

#define MAX_WORD_LENGTH 10;

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
