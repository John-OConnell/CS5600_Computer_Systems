//
// dll.h / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#ifndef MYDLL_H
#define MYDLL_H

// Create a node data structure to store data within the DLL.
typedef struct node
{
    void* data;
    struct node* next;
    struct node* previous;
} node_t;

// Create a DLL data structure
// Our DLL holds a pointer to the first node in our DLL called head,
// and a pointer to the last node in our DLL called tail.
typedef struct DLL
{
    int count;    // count keeps track of how many items are in the DLL.
    node_t* head; // head points to the first node in our DLL.
    node_t* tail; // tail points to the last node in our DLL.
} dll_t;

dll_t* create_dll();

int dll_empty(dll_t* l);

int dll_push_front(dll_t* l, void* item);

int dll_push_back(dll_t* l, void* item);

void* dll_pop_front(dll_t* l);

void* dll_pop_back(dll_t* l);

int dll_insert(dll_t* l, int pos, void* item);

void* dll_get(dll_t* l, int pos);

void* dll_remove(dll_t* l, int pos);

int dll_size(dll_t* l);

void free_dll(dll_t* l);

#endif