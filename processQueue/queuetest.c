/*
* queuetest.h / Process Queue
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 27, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int unittest1() {
    printf("-- Running Unit Test 1: Test createQ() --\n");

    queue_t* testQ = createQ();

    if (testQ != NULL && testQ->head_p == NULL 
            && testQ->tail_p == NULL && testQ->count == 0)
    {
        free(testQ);
        return 1;
    }

    free(testQ);
    return 0;
}

int unittest2() {
    printf("-- Running Unit Test 2: Test createProc() --\n");

    process_t* testProc = createProc(1, "test process", 10000000000, 1);

    if (testProc != NULL && testProc->identifier == 1 && strcmp(testProc->name, "test process") == 0
            && testProc->runtime == 10000000000 && testProc->priority == 1)
    {
        free(testProc);
        return 1;
    }

    free(testProc);
    return 0;
}

int unittest3() {
    printf("-- Running Unit Test 3: Test add2q() --\n");

    process_t* testProc1 = createProc(1, "test1", 10, 1);
    process_t* testProc2 = createProc(2, "test2", 10, 2);
    process_t* testProc3 = createProc(3, "test3", 10, 3);
    process_t* testProc4 = createProc(4, "test4", 10, 4);
    process_t* testProc5 = createProc(5, "test5", 10, 5);

    queue_t* testQ = createQ();

    if(add2q(testQ, testProc1) != 1)
    {
        return 0;
    }
    printf("Expected: ||ID: 1 , Priority: 1||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    if(add2q(testQ, testProc2) != 1)
    {
        return 0;
    }
    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 2 , Priority: 2||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    if(add2q(testQ, testProc3) != 1)
    {
        return 0;
    }
    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 2 , Priority: 2|| -> ||ID: 3 , Priority: 3||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    if(add2q(testQ, testProc4) != 1)
    {
        return 0;
    }
    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 2 , Priority: 2|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    if(add2q(testQ, testProc5) != 1)
    {
        return 0;
    }
    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 2 , Priority: 2|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    freeQ(testQ);
    return 1;
}

int unittest4() {
    printf("-- Running Unit Test 4: Test popQ() --\n");

    process_t* testProc1 = createProc(1, "test1", 10, 1);
    process_t* testProc2 = createProc(2, "test2", 10, 2);
    process_t* testProc3 = createProc(3, "test3", 10, 3);
    process_t* testProc4 = createProc(4, "test4", 10, 4);
    process_t* testProc5 = createProc(5, "test5", 10, 5);

    queue_t* testQ = createQ();

    add2q(testQ, testProc1);
    add2q(testQ, testProc2);
    add2q(testQ, testProc3);
    add2q(testQ, testProc4);
    add2q(testQ, testProc5);

    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 2 , Priority: 2|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    process_t* pop = (process_t*) popQ(testQ);
    if(pop == NULL)
    {
        return 0;
    }
    free(pop);

    printf("Expected: ||ID: 2 , Priority: 2|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    pop = (process_t*) popQ(testQ);
    if(pop == NULL)
    {
        return 0;
    }
    free(pop);

    printf("Expected: ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    pop = (process_t*) popQ(testQ);
    if(pop == NULL)
    {
        return 0;
    }
    free(pop);

    printf("Expected: ||ID: 4 , Priority: 4|| -> ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    pop = (process_t*) popQ(testQ);
    if(pop == NULL)
    {
        return 0;
    }
    free(pop);

    printf("Expected: ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    pop = (process_t*) popQ(testQ);
    if(pop == NULL)
    {
        return 0;
    }
    free(pop);

    printf("Expected: Queue is empty!\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    freeQ(testQ);
    return 1;
}

int unittest5() {
    printf("-- Running Unit Test 5: Test rmProcess() --\n");

    process_t* testProc1 = createProc(1, "test1", 10, 1);
    process_t* testProc2 = createProc(5, "test2", 10, 5);
    process_t* testProc3 = createProc(3, "test3", 10, 3);
    process_t* testProc4 = createProc(4, "test4", 10, 4);
    process_t* testProc5 = createProc(2, "test5", 10, 2);

    queue_t* testQ = createQ();

    add2q(testQ, testProc1);
    add2q(testQ, testProc2);
    add2q(testQ, testProc3);
    add2q(testQ, testProc4);
    add2q(testQ, testProc5);

    printf("Expected: ||ID: 1 , Priority: 1|| -> ||ID: 5 , Priority: 5|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 2 , Priority: 2||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    process_t* rm = rmProcess(testQ);
    if(rm == NULL)
    {
        return 0;
    }
    free(rm);

    printf("Expected: ||ID: 5 , Priority: 5|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4|| -> ||ID: 2 , Priority: 2||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    rm = rmProcess(testQ);
    if(rm == NULL)
    {
        return 0;
    }
    free(rm);

    printf("Expected: ||ID: 5 , Priority: 5|| -> ||ID: 3 , Priority: 3|| -> ||ID: 4 , Priority: 4||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    rm = rmProcess(testQ);
    if(rm == NULL)
    {
        return 0;
    }
    free(rm);

    printf("Expected: ||ID: 5 , Priority: 5|| -> ||ID: 4 , Priority: 4||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    rm = rmProcess(testQ);
    if(rm == NULL)
    {
        return 0;
    }
    free(rm);

    printf("Expected: ||ID: 5 , Priority: 5||\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    rm = rmProcess(testQ);
    if(rm == NULL)
    {
        return 0;
    }
    free(rm);

    printf("Expected: Queue is empty!\n");
    printf("Actual:   ");
    printProcessQ(testQ);

    freeQ(testQ);
    return 1;
}

int unittest6() {
    printf("-- Running Unit Test 6: Test qsize() --\n");

    process_t* testProc1 = createProc(1, "test1", 10, 1);
    process_t* testProc2 = createProc(2, "test2", 10, 2);
    process_t* testProc3 = createProc(3, "test3", 10, 3);
    process_t* testProc4 = createProc(4, "test4", 10, 4);
    process_t* testProc5 = createProc(5, "test5", 10, 5);

    queue_t* testQ = createQ();

    if(qsize(testQ) != 0)
    {
        return 0;
    }

    add2q(testQ, testProc1);
    if(qsize(testQ) != 1)
    {
        return 0;
    }

    add2q(testQ, testProc2);
    if(qsize(testQ) != 2)
    {
        return 0;
    }

    add2q(testQ, testProc3);
    if(qsize(testQ) != 3)
    {
        return 0;
    }

    add2q(testQ, testProc4);
    if(qsize(testQ) != 4)
    {
        return 0;
    }

    add2q(testQ, testProc5);
    if(qsize(testQ) != 5)
    {
        return 0;
    }

    process_t* pop = (process_t*) popQ(testQ);
    if(qsize(testQ) != 4)
    {
        return 0;
    }
    free(pop);

    pop = (process_t*) popQ(testQ);
    if(qsize(testQ) != 3)
    {
        return 0;
    }
    free(pop);

    pop = (process_t*) popQ(testQ);
    if(qsize(testQ) != 2)
    {
        return 0;
    }
    free(pop);

    pop = (process_t*) popQ(testQ);
    if(qsize(testQ) != 1)
    {
        return 0;
    }
    free(pop);

    pop = (process_t*) popQ(testQ);
    if(qsize(testQ) != 0)
    {
        return 0;
    }
    free(pop);

    return 1;
}

void runUnitTests() {
    int numPassed = 0;

    numPassed += unittest1();
    numPassed += unittest2();
    numPassed += unittest3();
    numPassed += unittest4();
    numPassed += unittest5();
    numPassed += unittest6();

    printf("*** %d / 6 UNIT TESTS PASSED ***\n", numPassed);

    return;
}

int main() {

    runUnitTests();
    return 0;
}
