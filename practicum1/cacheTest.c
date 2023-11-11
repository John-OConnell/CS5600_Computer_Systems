//
// cacheTest.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h"
#include "message.h"
#include "genRandWord.h"

cache_t* testCache;

msg_t* create_rand_msg()
{
    char* sender = genRandWord();
    char* receiver = genRandWord();
    char* word;
    char* message = (char*)calloc(MSGSIZE, sizeof(char));

    for(int i = 0; i < 5; i++)
    {
        word = genRandWord();
        strcat(message, word);
        strcat(message, " ");
    }

    word = genRandWord();
    strcat(message, word);
    
    msg_t* newMsg = create_msg(sender, receiver, message);

    return newMsg;
}

// test adding one message to cache
int unitTest0()
{

    msg_t* testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    return 1;

}

// test adding two messages to cache
int unitTest1()
{
    
    msg_t* testMsg = retrieve_msg(testCache, 2);
    if(testMsg->id != 2)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    return 1;

}

// test adding three messages to cache
int unitTest2()
{

    retrieve_msg(testCache, 3);
    retrieve_msg(testCache, 2);
    retrieve_msg(testCache, 1);

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    return 1;

}

// list of unit tests 
int (*unitTests[])(int)={
    unitTest0,
    // unitTest1,
    // unitTest2,
    // unitTest3,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

    srand(time(NULL));
    int testsPassed = 0;
    int counter = 0;

    testCache = create_cache();

    for(int i = 0; i < 6; i++)
    {
        msg_t* newMsg = create_rand_msg();
        store_msg(newMsg);
        free(newMsg);
    }

    while(unitTests[counter]!=NULL)
    {
	    printf("========unitTest %d========\n",counter);
        if(1==unitTests[counter](1))
        {
		    printf("Test Passed\n");
		    testsPassed++;
	    }
        else
        {
		    printf("Test Failed\n");
	    }
        counter++;
    }

    printf("%d of %d tests passed\n",testsPassed,counter);

    free(testCache);

    return 0;
}