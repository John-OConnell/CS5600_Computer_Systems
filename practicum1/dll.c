//
// dll.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include "dll.h"
#include <stdlib.h>

// Creates a DLL
// Returns a pointer to a newly created DLL.
// Returns NULL if we could not allocate memory.
dll_t* create_dll()
{
    dll_t* my_dll = (dll_t*)malloc(sizeof(dll_t));

    if (my_dll == NULL)
    {
        return NULL;
    }

    my_dll->head = NULL;
    my_dll->tail = NULL;
    my_dll->count = 0;

    return my_dll;
}

// DLL Empty
// Check if the DLL is empty
// Returns 1 if true (The DLL is completely empty)
// Returns 0 if false (the DLL has at least one element enqueued)
// Returns -1 if the dll is NULL.
int dll_empty(dll_t* l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->count == 0;
}

// push a new item to the front of the DLL (before the first node in the list).
// Returns 1 on success
// Returns 0 on failure (i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
int dll_push_front(dll_t* l, void* item)
{
    if (l == NULL)
    {
        return -1;
    }

    node_t* new_node = (node_t*)malloc(sizeof(node_t));

    if (new_node == NULL)
    {
        return 0;
    }

    new_node->data = item;
    new_node->previous = NULL;

    if (l->head == NULL)
    {
        l->head = new_node;
        l->tail = new_node;
        new_node->next = NULL;
    }
    else
    {
        l->head->previous = new_node;
        new_node->next = l->head;
        l->head = new_node;
    }

    l->count++;

    return 1;
}

// push a new item to the end of the DLL (after the last node in the list).
// Returns 1 on success
// Returns 0 on failure (i.e. we couldn't allocate memory for the new node)
// Returns -1 if DLL is NULL.
int dll_push_back(dll_t* l, void* item)
{
    if (l == NULL)
    {
        return -1;
    }

    node_t* new_node = (node_t*)malloc(sizeof(node_t));

    if (new_node == NULL)
    {
        return 0;
    }

    new_node->data = item;
    new_node->next = NULL;

    if (l->tail == NULL)
    {
        l->head = new_node;
        l->tail = new_node;
        new_node->previous = NULL;
    }
    else
    {
        l->tail->next = new_node;
        new_node->previous = l->tail;
        l->tail = new_node;
    }

    l->count++;

    return 1;
}

// Returns the first item in the DLL and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_front(dll_t* l)
{
    if (l == NULL)
    {
        return NULL;
    }

    if (l->count == 0)
    {
        return NULL;
    }

    void* data = l->head->data;
    node_t* node_popped = l->head;

    if (l->count == 1)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        l->head = l->head->next;
        l->head->previous = NULL;
    }

    l->count--;

    free(node_popped);

    return data;
}

// Returns the last item in the DLL, and also removes it from the list.
// Returns 0 on failure, i.e. there is noting to pop from the list.
// Returns a -1 if the DLL is NULL.
// Assume no negative numbers in the list or the number zero.
void* dll_pop_back(dll_t* l)
{
    if (l == NULL)
    {
        return NULL;
    }

    if (l->count == 0)
    {
        return NULL;
    }

    void* data = l->tail->data;
    node_t* node_popped = l->tail;

    if (l->count == 1)
    {
        l->head = NULL;
        l->tail = NULL;
    }
    else
    {
        l->tail = l->tail->previous;
        l->tail->next = NULL;
    }

    l->count--;

    free(node_popped);

    return data;
}

// Inserts a new node before the node at the specified position.
// Returns 1 on success
// Returns 0 on failure:
//  * we couldn't allocate memory for the new node
//  * we tried to insert at a negative location.
//  * we tried to insert past the size of the list
//   (inserting at the size should be equivalent as calling push_back).
// Returns -1 if the list is NULL
int dll_insert(dll_t* l, int pos, void* item)
{
    if (l == NULL)
    {
        return -1;
    }

    if ((pos < 0) || (pos > l->count))
    {
        return 0;
    }

    if (pos == 0)
    {
        return dll_push_front(l, item);
    }

    if (pos == l->count)
    {
        return dll_push_back(l, item);
    }

    node_t* newNode = (node_t*)malloc(sizeof(node_t));

    if (newNode == NULL)
    {
        return 0;
    }

    node_t* iterator = l->head;
    for (int i = 0; i < pos; i++)
    {
        iterator = iterator->next;
    }

    newNode->data = item;
    newNode->next = iterator;
    newNode->previous = iterator->previous;
    newNode->previous->next = newNode;
    iterator->previous = newNode;

    l->count++;

    return 1;
}

// Returns the item at position pos starting at 0 (0 being the first item)
//  (does not remove the item)
// Returns 0 on failure:
//  * we tried to get at a negative location.
//  * we tried to get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_get(dll_t* l, int pos)
{
    if (l == NULL)
    {
        return NULL;
    }

    if ((pos < 0) || (pos >= l->count))
    {
        return NULL;
    }

    node_t* iterator = l->head;
    for (int i = 0; i < pos; i++)
    {
        iterator = iterator->next;
    }

    return iterator->data;
}

// Removes the item at position pos starting at 0 (0 being the first item)
// Returns 0 on failure:
//  * we tried to remove at a negative location.
//  * we tried to remove get past the size of the list
// Returns -1 if the list is NULL
// Assume no negative numbers in the list or the number zero.
void* dll_remove(dll_t* l, int pos)
{
    if (l == NULL)
    {
        return NULL;
    }

    if ((pos < 0) || (pos >= l->count))
    {
        return NULL;
    }

    if (pos == 0)
    {
        return dll_pop_front(l);
    }

    if (pos == l->count - 1)
    {
        return dll_pop_back(l);
    }

    node_t* iterator = l->head;
    for (int i = 0; i < pos; i++)
    {
        iterator = iterator->next;
    }

    void* data = iterator->data;

    iterator->previous->next = iterator->next;
    iterator->next->previous = iterator->previous;
    free(iterator);

    l->count--;

    return data;
}

// DLL Size
// Queries the current size of a DLL
// Returns -1 if the DLL is NULL.
int dll_size(dll_t* l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->count;
}

// Free DLL
// Removes a DLL and all of its elements from memory.
// This should be called before the program terminates.
void free_dll(dll_t* l)
{
    if (l == NULL)
    {
        exit(1);
    }

    node_t* iterator = l->head;

    while (iterator != NULL)
    {
        node_t* temp = iterator;
        void* item = temp->data;
        iterator = iterator->next;
        free(temp);
        free(item);
    }

    free(l);
}
