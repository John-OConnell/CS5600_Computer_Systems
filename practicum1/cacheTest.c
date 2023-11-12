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
        free(word);
    }

    word = genRandWord();
    strcat(message, word);
    free(word);
    
    msg_t* newMsg = create_msg(sender, receiver, message);

    free(sender);
    free(receiver);
    free(message);

    return newMsg;
}

// Test create_cache
int unitTest0()
{
    int result = 0;

    cache_t* myCache = create_cache();

    if( myCache != NULL &&
        myCache->hits == 0 &&
        myCache->misses == 0 &&
        myCache->cache_dll != NULL)
    {
        result = 1;
    }

    free_cache(myCache);

    return result;
}

// Test check_cache, insert into empty cache
int unitTest1()
{
    int result = 0;
    msg_t* testMsg = create_rand_msg();

    if(cache_insert(testCache, testMsg) == 1)
    {
        result = 1;
    }

    reset_cache(testCache);

    return result;
}

// Test check_cache, insert into non-empty cache
int unitTest2()
{
    int result = 0;
    msg_t* testMsg1 = create_rand_msg();
    msg_t* testMsg2 = create_rand_msg();
    cache_insert(testCache, testMsg1);

    if(cache_insert(testCache, testMsg2) == 1)
    {
        result = 1;
    }

    reset_cache(testCache);
    
    return result;
}

// Test check_cache, insert into full cache
int unitTest3()
{
    int result = 0;
    msg_t* testMsg1 = create_rand_msg();
    msg_t* testMsg2 = create_rand_msg();
    msg_t* testMsg3 = create_rand_msg();
    msg_t* testMsg4 = create_rand_msg();
    cache_insert(testCache, testMsg1);
    cache_insert(testCache, testMsg2);
    cache_insert(testCache, testMsg3);
    
    if(cache_insert(testCache, testMsg4) == 1)
    {
        result = 1;
    }

    reset_cache(testCache);
    
    return result;
}

// Test check_cache with null cache
int unitTest4()
{
    int result = 0;

    cache_t* nullCache = NULL;
    msg_t* testMsg = create_rand_msg();

    if(cache_insert(nullCache, testMsg) == -1)
    {
        result = 1;
    }

    free(testMsg);

    return result;
}

// Test check_cache with message present
int unitTest5()
{
    int result = 0;
    msg_t* testMsg = create_rand_msg();
    cache_insert(testCache, testMsg);

    msg_t* retrievedMsg = check_cache(testCache, testMsg->id);
    if(retrievedMsg->id == testMsg->id)
    {
        result = 1;
    }

    reset_cache(testCache);

    return result;
}

// Test check_cache without message present
int unitTest6()
{
    int result = 0;
    msg_t* retrievedMsg = check_cache(testCache, 1);

    if(retrievedMsg == NULL)
    {
        result = 1;
    }

    return result;
}

// Test check cache null cache
int unitTest7()
{
    int result = 0;

    cache_t* nullCache = NULL;

    if(check_cache(nullCache, 1) == NULL)
    {
        result = 1;
    }

    return result;
}

// Test reset cache
int unitTest8()
{
    int result = 0;
    testCache->hits = 5;
    testCache->misses = 5;
    msg_t* testMsg1 = create_rand_msg();
    msg_t* testMsg2 = create_rand_msg();
    msg_t* testMsg3 = create_rand_msg();
    cache_insert(testCache, testMsg1);
    cache_insert(testCache, testMsg2);
    cache_insert(testCache, testMsg3);

    reset_cache(testCache);

    if( testCache->cache_dll->count == 0 &&
        testCache->hits == 0 &&
        testCache->misses == 0)
    {
        result = 1;
    }

    return result;
}
// Test reset cache null cache
int unitTest9()
{
    int result = 0;

    cache_t* nullCache = NULL;

    if(reset_cache(nullCache) == -1)
    {
        result = 1;
    }

    return result;
}

// test adding one message to cache
int unitTest10()
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

    reset_cache(testCache);

    return 1;

}

// test adding two messages to cache
int unitTest11()
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

    reset_cache(testCache);

    return 1;
}

// test adding three messages to cache
int unitTest12()
{

    msg_t* testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 2);
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

    reset_cache(testCache);

    return 1;

}

// test replacement strategy when retrieving message already in cache
int unitTest13()
{

    msg_t* testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 2);
    if(testMsg->id != 2)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    reset_cache(testCache);

    return 1;

}

// test replacement strategy when retrieving one message not in cache
int unitTest14()
{

    msg_t* testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 2);
    if(testMsg->id != 2)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 6);
    if(testMsg->id != 6)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    reset_cache(testCache);

    return 1;

}

// test replacement strategy when retrieving two messages not in cache
int unitTest15()
{

    msg_t* testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 2);
    if(testMsg->id != 2)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 6);
    if(testMsg->id != 6)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 5);
    if(testMsg->id != 5)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    reset_cache(testCache);

    return 1;

}

// test replacement strategy when retrieving three messages not in cache
int unitTest16()
{

    msg_t* testMsg = retrieve_msg(testCache, 3);
    if(testMsg->id != 3)
    {
        return 0;
    }
    
    testMsg = retrieve_msg(testCache, 2);
    if(testMsg->id != 2)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 1);
    if(testMsg->id != 1)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 6);
    if(testMsg->id != 6)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 5);
    if(testMsg->id != 5)
    {
        return 0;
    }

    testMsg = retrieve_msg(testCache, 4);
    if(testMsg->id != 4)
    {
        return 0;
    }

    printf("Cache hits: %d\n", testCache->hits);
    printf("Cache misses: %d\n", testCache->misses);
    printf("Cache: ");
    print_cache(testCache);

    reset_cache(testCache);

    return 1;

}



// list of unit tests 
int (*unitTests[])(int)={
    unitTest0,
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
    unitTest5,
    unitTest6,
    unitTest7,
    unitTest8,
    unitTest9,
    unitTest10,
    unitTest11,
    unitTest12,
    unitTest13,
    unitTest14,
    unitTest15,
    unitTest16,
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

    free_cache(testCache);

    return 0;
}