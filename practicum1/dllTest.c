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

// Test push front return value
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

// Test push front fail
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

// Test push back empty
int unitTest10()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_back(test_dll, data_0);

    if(67 == check_node_data(test_dll, 0))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push back empty count
int unitTest11()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_back(test_dll, data_0);

    if((1 == test_dll->count) && (1 == dll_size(test_dll)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push back non empty
int unitTest12()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_back(test_dll, data_0);

    if( 7 == check_node_data(test_dll, 0) &&
        17 == check_node_data(test_dll, 1) &&
        27 == check_node_data(test_dll, 2) &&
        37 == check_node_data(test_dll, 3) &&
        67 == check_node_data(test_dll, 4))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push back non empty count
int unitTest13()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;
    dll_push_back(test_dll, data_0);

    if((5 == test_dll->count) && (5 == dll_size(test_dll)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push back return value
int unitTest14()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if((1 == dll_push_back(test_dll, data_0)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test push back fail
int unitTest15()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if((-1 == dll_push_back(test_dll, data_0)))
    {
        result = 1;
    }

    free(data_0);
    return result;
}

// Test pop front one node
int unitTest16()
{
    int result = 0;
    dll_t* test_dll = create_one_node_dll();
    data_t* pop_data = dll_pop_front(test_dll);

    if((7 == pop_data->data))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop front one node count
int unitTest17()
{
    int result = 0;
    dll_t* test_dll = create_one_node_dll();
    data_t* pop_data = dll_pop_front(test_dll);

    if((0 == test_dll->count) && (0 == dll_size(test_dll)))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop front multi node
int unitTest18()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_pop_front(test_dll);
    data_t* data_1 = dll_pop_front(test_dll);
    data_t* data_2 = dll_pop_front(test_dll);
    data_t* data_3 = dll_pop_front(test_dll);

    if( 7 == data_0->data &&
        17 == data_1->data &&
        27 == data_2->data &&
        37 == data_3->data)
    {
        result = 1;
    }

    free(data_0);
    free(data_1);
    free(data_2);
    free(data_3);
    free_dll(test_dll);
    return result;
}

// Test pop front multi node count
int unitTest19()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* pop_data = dll_pop_front(test_dll);

    if((3 == test_dll->count) && (3 == dll_size(test_dll)))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop front empty
int unitTest20()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* pop_data = dll_pop_front(test_dll);

    if(NULL == pop_data)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test pop front fail
int unitTest21()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* pop_data = dll_pop_front(test_dll);

    if(NULL == pop_data)
    {
        result = 1;
    }

    return result;
}

// Test pop back one node
int unitTest22()
{
    int result = 0;
    dll_t* test_dll = create_one_node_dll();
    data_t* pop_data = dll_pop_back(test_dll);

    if((7 == pop_data->data))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop back one node count
int unitTest23()
{
    int result = 0;
    dll_t* test_dll = create_one_node_dll();
    data_t* pop_data = dll_pop_back(test_dll);

    if((0 == test_dll->count) && (0 == dll_size(test_dll)))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop back multi node
int unitTest24()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_pop_back(test_dll);
    data_t* data_1 = dll_pop_back(test_dll);
    data_t* data_2 = dll_pop_back(test_dll);
    data_t* data_3 = dll_pop_back(test_dll);

    if( 37 == data_0->data &&
        27 == data_1->data &&
        17 == data_2->data &&
        7 == data_3->data)
    {
        result = 1;
    }

    free(data_0);
    free(data_1);
    free(data_2);
    free(data_3);
    free_dll(test_dll);
    return result;
}

// Test pop back multi node count
int unitTest25()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* pop_data = dll_pop_back(test_dll);

    if((3 == test_dll->count) && (3 == dll_size(test_dll)))
    {
        result = 1;
    }

    free(pop_data);
    free_dll(test_dll);
    return result;
}

// Test pop back empty
int unitTest26()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* pop_data = dll_pop_back(test_dll);

    if(NULL == pop_data)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test pop back fail
int unitTest27()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* pop_data = dll_pop_back(test_dll);

    if(NULL == pop_data)
    {
        result = 1;
    }

    return result;
}

// Test insert empty
int unitTest28()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    dll_insert(test_dll, 0, data_0);

    if(67 == check_node_data(test_dll, 0))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test insert non-empty front
int unitTest29()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    dll_insert(test_dll, 0, data_0);

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

// Test insert non-empty back
int unitTest30()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    dll_insert(test_dll, 4, data_0);

    if( 7 == check_node_data(test_dll, 0) &&
        17 == check_node_data(test_dll, 1) &&
        27 == check_node_data(test_dll, 2) &&
        37 == check_node_data(test_dll, 3) &&
        67 == check_node_data(test_dll, 4))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test insert non-empty middle
int unitTest31()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    dll_insert(test_dll, 2, data_0);

    if( 7 == check_node_data(test_dll, 0) &&
        17 == check_node_data(test_dll, 1) &&
        67 == check_node_data(test_dll, 2) &&
        27 == check_node_data(test_dll, 3) &&
        37 == check_node_data(test_dll, 4))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test insert return value
int unitTest32()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if( 1 == dll_insert(test_dll, 2, data_0))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test insert count
int unitTest33()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    dll_insert(test_dll, 2, data_0);

    if((5 == test_dll->count) && (5 == dll_size(test_dll)))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test insert fail negative
int unitTest34()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if(0 == dll_insert(test_dll, -1, data_0))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test insert fail out of bounds
int unitTest35()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if(0 == dll_insert(test_dll, 5, data_0))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test insert fail null
int unitTest36()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* data_0 = (data_t*)malloc(sizeof(data_t));

    data_0->data = 67;

    if(-1 == dll_insert(test_dll, 0, data_0))
    {
        result = 1;
    }

    free(data_0);
    return result;
}

// Test get front
int unitTest37()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_get(test_dll, 0);

    if(7 == data_0->data)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test get back
int unitTest38()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_get(test_dll, 3);

    if(37 == data_0->data)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test get middle
int unitTest39()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_get(test_dll, 2);

    if(27 == data_0->data)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test get fail negative pos
int unitTest40()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_get(test_dll, -1);

    if(NULL == data_0)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test get fail out of bounds
int unitTest41()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_get(test_dll, 4);

    if(NULL == data_0)
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test get fail null
int unitTest42()
{
    int result = 0;
    dll_t* test_dll = NULL;
    data_t* data_0 = dll_get(test_dll, 1);

    if(NULL == data_0)
    {
        result = 1;
    }

    return result;
}

// Test remove one node
int unitTest43()
{
    int result = 0;
    dll_t* test_dll = create_one_node_dll();
    data_t* data_0 = dll_remove(test_dll, 0);

    if(7 == data_0->data)
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test remove front
int unitTest44()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_remove(test_dll, 0);

    if( 17 == check_node_data(test_dll, 0) &&
        27 == check_node_data(test_dll, 1) &&
        37 == check_node_data(test_dll, 2))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test remove back
int unitTest45()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_remove(test_dll, 3);

    if( 7 == check_node_data(test_dll, 0) &&
        17 == check_node_data(test_dll, 1) &&
        27 == check_node_data(test_dll, 2))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test remove middle
int unitTest46()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_remove(test_dll, 2);

    if( 7 == check_node_data(test_dll, 0) &&
        17 == check_node_data(test_dll, 1) &&
        37 == check_node_data(test_dll, 2))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test remove count
int unitTest47()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();
    data_t* data_0 = dll_remove(test_dll, 2);

    if((3 == test_dll->count) && (3 == dll_size(test_dll)))
    {
        result = 1;
    }

    free(data_0);
    free_dll(test_dll);
    return result;
}

// Test remove fail negative
int unitTest48()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();

    if(NULL == dll_remove(test_dll, -1))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test remove fail out of bounds
int unitTest49()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();

    if(NULL == dll_remove(test_dll, 4))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test remove fail NULL
int unitTest50()
{
    int result = 0;
    dll_t* test_dll = NULL;

    if(NULL == dll_remove(test_dll, 1))
    {
        result = 1;
    }

    return result;
}

// Test size empty
int unitTest51()
{
    int result = 0;
    dll_t* test_dll = create_empty_dll();

    if(0 == dll_size(test_dll))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test size non empty
int unitTest52()
{
    int result = 0;
    dll_t* test_dll = create_test_dll();

    if(4 == dll_size(test_dll))
    {
        result = 1;
    }

    free_dll(test_dll);
    return result;
}

// Test size fail
int unitTest53()
{
    int result = 0;
    dll_t* test_dll = NULL;

    if(-1 == dll_size(test_dll))
    {
        result = 1;
    }

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
    unitTest10,
    unitTest11,
    unitTest12,
    unitTest13,
    unitTest14,
    unitTest15,
    unitTest16,
    unitTest17,
    unitTest18,
    unitTest19,
    unitTest20,
    unitTest21,
    unitTest22,
    unitTest23,
    unitTest24,
    unitTest25,
    unitTest26,
    unitTest27,
    unitTest28,
    unitTest29,
    unitTest30,
    unitTest31,
    unitTest32,
    unitTest33,
    unitTest34,
    unitTest35,
    unitTest36,
    unitTest37,
    unitTest38,
    unitTest39,
    unitTest40,
    unitTest41,
    unitTest42,
    unitTest43,
    unitTest44,
    unitTest45,
    unitTest46,
    unitTest47,
    unitTest48,
    unitTest49,
    unitTest50,
    unitTest51,
    unitTest52,
    unitTest53,
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