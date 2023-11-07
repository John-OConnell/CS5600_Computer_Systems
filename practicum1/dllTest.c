//
// dllTest.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll.h"

// Dummy struct to use for testing
typedef struct dummyData
{
    int data;
} data_t;

// Creates an empty dll for testing.
static dll_t *create_empty_dll()
{
    dll_t *empty_dll = (dll_t *)malloc(sizeof(dll_t));
    empty_dll->head = NULL;
    empty_dll->tail = NULL;
    empty_dll->count = 0;

    return empty_dll;
}

// Creates a dll with only one node for testing.
static dll_t *create_one_node_dll()
{
    dll_t* empty_dll = (dll_t*)malloc(sizeof(dll_t));
    node_t* node_0 = (node_t*)malloc(sizeof(node_t));
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 7;

    node_0->data = data_0;
    node_0->previous = NULL;
    node_0->next = NULL;

    empty_dll->head = node_0;
    empty_dll->tail = node_0;
    empty_dll->count = 1;

    return empty_dll;
}

// Creates a dll with four nodes for testing.
static dll_t *create_test_dll()
{
    dll_t *test_dll = (dll_t *)malloc(sizeof(dll_t));
    node_t *node_0 = (node_t *)malloc(sizeof(node_t));
    node_t *node_1 = (node_t *)malloc(sizeof(node_t));
    node_t *node_2 = (node_t *)malloc(sizeof(node_t));
    node_t *node_3 = (node_t *)malloc(sizeof(node_t));
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));
    data_t* data_1 = (data_t*)malloc(sizeof(data_t));
    data_t* data_2 = (data_t*)malloc(sizeof(data_t));
    data_t* data_3 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 7;
    data_1->data = 17;
    data_2->data = 27;
    data_3->data = 37;

    node_0->data = data_0;
    node_0->previous = NULL;
    node_0->next = node_1;
    node_1->data = data_1;
    node_1->previous = node_0;
    node_1->next = node_2;
    node_2->data = data_2;
    node_2->previous = node_1;
    node_2->next = node_3;
    node_3->data = data_3;
    node_3->previous = node_2;
    node_3->next = NULL;

    test_dll->head = node_0;
    test_dll->tail = node_3;
    test_dll->count = 4;

    return test_dll;
}

// Checks the node in the given dll.
static int check_node_data(dll_t *l, int pos)
{
    if ((l == NULL) || (pos < 0) || (pos >= l->count))
    {
        return -1;
    }

    node_t *iterator = l->head;

    for (int i = 0; i < pos; i++)
    {
        iterator = iterator->next;
    }

    data_t* temp = iterator->data;

    int val = temp->data;

    return val;
}

// Test creating dll
int unitTest0(int status){
    
    dll_t* test_dll = create_dll();
    if(test_dll == NULL)
    {
        return 0;
    }

    free_dll(test_dll);

    return 1;
}

// Test dll_empty true
int unitTest1()
{
    int result = 0;
    dll_t *test_dll = create_empty_dll();
    if(1 == dll_empty(test_dll))
    {
        result = 1;
    }
    free_dll(test_dll);

    return result;
}

// Test dll_empty false
int unitTest2()
{
    int result = 0;
    dll_t *test_dll = create_test_dll();
    if(0 == dll_empty(test_dll))
    {
        result = 1;
    }
    free_dll(test_dll);

    return result;
}

// Test dll_empty fail
int unitTest3()
{
    int result = 0;
    dll_t* test_dll = NULL;
    if(-1 == dll_empty(test_dll))
    {
        result = 1;
    }

    return result;
}

// Test push front empty
int unitTest4()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_front(test_dll, data_0);

    if(67 == check_node_data(test_dll, 0))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push front empty count
int unitTest5()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_front(test_dll, data_0);

    if((1 == test_dll->count) && (1 == dll_size(test_dll)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push front non empty
int unitTest6()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_front(test_dll, data_0);

    if( 67 == check_node_data(test_dll, 0) &&
        7 == check_node_data(test_dll, 1) &&
        17 == check_node_data(test_dll, 2) &&
        27 == check_node_data(test_dll, 3) &&
        37 == check_node_data(test_dll, 4))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push front non empty count
int unitTest7()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_front(test_dll, data_0);

    if((5 == test_dll->count) && (5 == dll_size(test_dll)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push front empty return value
int unitTest8()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if((1 == dll_push_front(test_dll, data_0)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push front empty count
int unitTest9()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if((-1 == dll_push_front(test_dll, data_0)))
    {
        result = 1;
    }

    free(data_0);
    return result;
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