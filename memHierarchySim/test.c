#include <stdio.h>
#include <stdlib.h>
#include "message.h"


// Test creating a message
int unitTest0(int status){
    
    int result;
    // create message
    msg* myMsg = create_msg("Test Sender", "Test Receiver", "Hello World!");
    if(myMsg == NULL)
    {
        result = 0;
    }
    else if(myMsg->id != 1)
    {
        result = 0;
    }
    else if(strcmp("Test Sender", myMsg->sender) != 0)
    {
        result = 0;
    }
    else if(strcmp("Test Receiver", myMsg->receiver) != 0)
    {
        result = 0;
    }
    else if(strcmp("Hello World!", myMsg->content) != 0)
    {
        result = 0;
    }
    else
    {
        result = 1;
    }

    free(myMsg);
    return result;
}

// Test storing message
int unitTest1(int status){
    
    int result;
    // create and store message
    msg* myMsg = create_msg("Test Sender", "Test Receiver", "Hello World!");
    store_msg(myMsg);

    unsigned int targetID = myMsg->id;

    // initialize file name based on input id
    char fileName[256];
    snprintf(fileName, sizeof(fileName), "messages/%d.txt", targetID);

    // attempt to open file
    FILE* fp = fopen(fileName, "r");
    if(fp == NULL)
    {
        return 0;
    }

    char sender[256];
    char receiver[256];
    char content[512];
    int delivered;

    // read message details from the file
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "Sender: %255[^\n]\n", sender);
    fscanf(fp, "Receiver: %255[^\n]\n", receiver);
    fscanf(fp, "Content: %511[^\n]\n", content);

    fclose(fp);

    if(strcmp("Test Sender", sender) != 0)
    {
        result = 0;
    }
    else if(strcmp("Test Receiver", receiver) != 0)
    {
        result = 0;
    }
    else if(strcmp("Hello World!", content) != 0)
    {
        result = 0;
    }
    else
    {
        result = 1;
    }

    free(myMsg);
    return result;
}

// Test full process of creating, storing, and retrieving
int unitTest2(int status){
    
    // create and store message
    msg* myMsg = create_msg("Test Sender", "Test Reciever", "Hello World!");
    store_msg(myMsg);

    // retrieve message by its identifier
    unsigned int targetID = myMsg->id;
    msg* retrievedMsg = retrieve_msg(targetID);

    if (retrievedMsg != NULL) 
    {
        // Print or process the retrieved message

        char time[32];
        strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&retrievedMsg->time));
        printf("Information of Recieved Message:\n");
        printf("\tID: %u\n", retrievedMsg->id);
        printf("\tTime: %s\n", time);
        printf("\tSender: %s\n", retrievedMsg->sender);
        printf("\tReceiver: %s\n", retrievedMsg->receiver);
        printf("\tContent: %s\n", retrievedMsg->content);
        printf("\tDelivered: %d\n", retrievedMsg->delivered);
    }
    else 
    {
        printf("HERE\n");
        free(myMsg);
        return 0;
    }
    // Free memory for messages when done
    free(myMsg);
    free(retrievedMsg);
    
    return 1;
}

// // Test string with leading and trailing spaces
// int unitTest3(int status){
    
//     char testStr[] = " hello world ";

//     return(3 == countVowels(testStr));
// }

// // Test input with special characters
// int unitTest4(int status){
    
//     char testStr[] = "!hello! --World--";

//     return(3 == countVowels(testStr));
// }


// list of unit tests 
int (*unitTests[])(int)={
    unitTest0,
    unitTest1,
    unitTest2,
    // unitTest3,
    // unitTest4,
    NULL
};

// ====================================================
// ================== Program Entry ===================
// ====================================================
int main(){

    int testsPassed = 0;
    int counter = 0;

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

    return 0;
}
