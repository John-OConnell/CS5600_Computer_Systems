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
    char content[1024];
    int delivered;

    // read message details from the file
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "%*[^\n]\n");
    fscanf(fp, "Sender: %255[^\n]\n", sender);
    fscanf(fp, "Receiver: %255[^\n]\n", receiver);
    fscanf(fp, "Content: %1023[^\n]\n", content);

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

// Test attempting to retrieve message that doesn't exist
int unitTest3(int status){
    
    // retrieve message by its identifier
    unsigned int targetID = 24;
    msg* retrievedMsg = retrieve_msg(targetID);

    return(retrievedMsg == NULL);
}

// Test storing and retrieving multiple messages
int unitTest4(int status){

    // create and store messages
    msg* myMsg1 = create_msg("Test Sender 1", "Test Reciever 1", "Hello World!");
    msg* myMsg2 = create_msg("Test Sender 2", "Test Reciever 2", "This is a test.");
    store_msg(myMsg1);
    store_msg(myMsg2);

    // retrieve message by its identifier
    unsigned int targetID1 = myMsg1->id;
    msg* retrievedMsg1 = retrieve_msg(targetID1);
    unsigned int targetID2 = myMsg2->id;
    msg* retrievedMsg2 = retrieve_msg(targetID2);

    if (retrievedMsg1 != NULL && retrievedMsg2 != NULL) 
    {
        // Print or process the retrieved message

        char time[32];
        strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&retrievedMsg1->time));
        printf("Information of First Recieved Message:\n");
        printf("\tID: %u\n", retrievedMsg1->id);
        printf("\tTime: %s\n", time);
        printf("\tSender: %s\n", retrievedMsg1->sender);
        printf("\tReceiver: %s\n", retrievedMsg1->receiver);
        printf("\tContent: %s\n", retrievedMsg1->content);
        printf("\tDelivered: %d\n", retrievedMsg1->delivered);

        strftime(time, sizeof(time), "%Y-%m-%d %H:%M:%S", localtime(&retrievedMsg2->time));
        printf("Information of Second Recieved Message:\n");
        printf("\tID: %u\n", retrievedMsg2->id);
        printf("\tTime: %s\n", time);
        printf("\tSender: %s\n", retrievedMsg2->sender);
        printf("\tReceiver: %s\n", retrievedMsg2->receiver);
        printf("\tContent: %s\n", retrievedMsg2->content);
        printf("\tDelivered: %d\n", retrievedMsg2->delivered);
    }
    else 
    {
        free(myMsg1);
        free(myMsg2);
        return 0;
    }
    // Free memory for messages when done
    free(myMsg1);
    free(myMsg2);
    free(retrievedMsg1);
    free(retrievedMsg2);
    
    return 1;
}

// list of unit tests 
int (*unitTests[])(int)={
    unitTest0,
    unitTest1,
    unitTest2,
    unitTest3,
    unitTest4,
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
