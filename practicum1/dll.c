//
// dll.c / Practicum 1
//
// John O'Connell / CS5600 / Northeastern University
// Fall 2023 / Nov 7, 2023
//
//

#include "dll.h"
#include <stdlib.h>

/*
 * Creates a DLL
 * 
 * @return my_dll: pointer to a newly created DLL
 *                 or NULL if memory not allocated
 * 
 */
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

/*
 * Checks if the DLL is empty
 *
 * @param l: an instance of a DLL
 * 
 * @return: 1 if the DLL is empty
 *          0 if the DLL is NOT empty
 *         -1 if the DLL is NULL
 * 
 */
int dll_empty(dll_t* l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->count == 0;
}

/*
 * Push a new item to the front of a DLL
 *
 * @param l: an instance of a DLL
 * @param item: the item to be added to the DLL
 * 
 * @return: 1 on success
 *          0 on failure
 *         -1 if the DLL is NULL
 * 
 */
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

/*
 * Push a new item to the back of a DLL
 *
 * @param l: an instance of a DLL
 * @param item: the item to be added to the DLL
 * 
 * @return: 1 on success
 *          0 on failure
 *         -1 if the DLL is NULL
 * 
 */
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

/*
 * Removes and returns the first item in a DLL
 *
 * @param l: an instance of a DLL
 * 
 * @return data: the item removed from the list
 *               or NULL if the list is empty or NULL
 * 
 */
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

/*
 * Removes and returns the last item in a DLL
 *
 * @param l: an instance of a DLL
 * 
 * @return data: the item removed from the list
 *               or NULL if the list is empty or NULL
 * 
 */
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

/*
 * Inserts a new node before the node at the specified position
 *
 * @param l: an instance of a DLL
 * @param pos: the position to insert the node
 * @param item: the item to be inserted
 * 
 * @return: 1 on success
 *          0 on failure
 *         -1 if the DLL is NULL
 * 
 */
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

/*
 * Returns the item at the specified position (does not remove the item)
 *
 * @param l: an instance of a DLL
 * @param pos: the position to get the item
 * 
 * @return data: the item removed from the list
 *               or NULL if the list is empty or NULL
 *               or NULL if the position is out of bounds
 * 
 */
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

/*
 * Removes and returns the item at the specified position
 *
 * @param l: an instance of a DLL
 * @param pos: the position to remove the item
 * 
 * @return data: the item removed from the list
 *               or NULL if the list is empty or NULL
 *               or NULL if the position is out of bounds
 * 
 */
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

/*
 * Queries the current size of a DLL
 *
 * @param l: an instance of a DLL
 * 
 * @return: the size of the DLL
 *          or -1 if the DLL is NULL
 * 
 */
int dll_size(dll_t* l)
{
    if (l == NULL)
    {
        return -1;
    }

    return l->count;
}

/*
 * Removes a DLL and all its elements from memory
 *
 * @param l: an instance of a DLL
 * 
 * @return: program crashes if DLL is null
 * 
 */
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
