/*
* queue.c / Process Queue
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 27, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t* createQ() {
    queue_t* queue = (queue_t*)malloc(sizeof(queue_t));

    if (queue == NULL)
    {
        return NULL;
    }

    queue->head_p = NULL;
    queue->tail_p = NULL;
    queue->count = 0;

    return queue;
}

process_t* createProc(int id, char* name, long runtime, int priority) {
    process_t* proc = (process_t*)malloc(sizeof(process_t));

    if (proc == NULL)
    {
        return NULL;
    }

    proc->identifier = id;
    proc->name = name;
    proc->runtime = runtime;
    proc->priority = priority;

    return proc;
}

// add a new element to the end of the queue
// Returns 1 on success
// Returns 0 on failure (i.e. new element is NULL)
// Returns -1 if queue is NULL.
int add2q(queue_t* queue, void* element) {
    if (queue == NULL)
    {
        return -1;
    }
    if (element == NULL)
    {
        return 0;
    }
    
    node_t* node = (node_t*)malloc(sizeof(node_t));;

    node->data = element;

    node->next_p = NULL;

    if (queue->count == 0)
    {
        queue->head_p = node;
        queue->tail_p = node;
        node->prev_p = NULL;
    }
    else
    {
        queue->tail_p->next_p = node;
        node->prev_p = queue->tail_p;
        queue->tail_p = node;
    }

    queue->count++;

    return 1;
}

void* popQ(queue_t* queue) {
    if (queue == NULL)
    {
        return NULL;
    }

    if (queue->count == 0)
    {
        return NULL;
    }

    void* data = queue->head_p->data;
    node_t* temp = queue->head_p;

    if (queue->count == 1)
    {
        queue->head_p = NULL;
        queue->tail_p = NULL;
    }
    else
    {
        queue->head_p = queue->head_p->next_p;
        queue->head_p->prev_p = NULL;
    }
    
    queue->count--;

    free(temp);

    return data;
}

process_t* rmProcess(queue_t* queue) {
    if (queue == NULL)
    {
        return NULL;
    }

    if (queue->count == 0)
    {
        return NULL;
    }

    node_t* tempNode = queue->head_p;
    process_t* tempProc = (process_t*) tempNode->data;

    if (queue->count == 1)
    {
        queue->head_p = NULL;
        queue->tail_p = NULL;
    }
    else
    {
        node_t* iteratorNode = tempNode->next_p;
        process_t* iteratorProc = iteratorNode->data;

        while (iteratorNode != NULL)
        {
            if (iteratorProc->priority < tempProc->priority)
            {
                tempNode = iteratorNode;
                tempProc = iteratorProc;
            }
            iteratorNode = iteratorNode->next_p;
            if (iteratorNode != NULL)
            {
                iteratorProc = iteratorNode->data;
            }
        }

        // process is at front of queue
        if (tempNode->prev_p == NULL)
        {
            queue->head_p = queue->head_p->next_p;
            queue->head_p->prev_p = NULL;
        }
        // process is at back of queue
        else if (tempNode->next_p == NULL)
        {
            queue->tail_p = queue->tail_p->prev_p;
            queue->tail_p->next_p = NULL;
        }
        // process is somewhere in middle of queue
        else
        {
            tempNode->next_p->prev_p = tempNode->prev_p;
            tempNode->prev_p->next_p = tempNode->next_p;
            tempNode->next_p = NULL;
            tempNode->prev_p = NULL;
        }
    }

    queue->count--;
    free(tempNode);
    return tempProc;
}

// Queue Size
// Queries the current size of a queue
// Returns -1 if the queue is NULL.
int qsize(queue_t* queue) {
    if (queue == NULL)
    {
        return -1;
    }
    else
    {
        return queue->count;
    }
}

void freeQ(queue_t* queue) {
    if (queue == NULL)
    {
        exit(1);
    }

    if(queue->count != 0)
    {
        node_t* iteratorNode = queue->head_p;
        void* iteratorData = iteratorNode->data;

        while(iteratorNode != NULL)
        {
            node_t* tempNode = iteratorNode;
            void* tempData = iteratorData;

            iteratorNode = iteratorNode->next_p;
            if (iteratorNode != NULL)
            {
                iteratorData = iteratorNode->data;
            }

            free(tempData);
            free(tempNode);
        }
    }

    free(queue);
    return;

}

void printProcessQ(queue_t* queue) {
    if (queue == NULL)
    {
        printf("ERROR: Queue is NULL\n");
        return;
    }
    else if (queue->count == 0)
    {
        printf("Queue is empty!\n");
        return;
    }
    else
    {
        node_t* tempNode = queue->head_p;
        process_t* tempProc = (process_t*) tempNode->data;
        while(tempNode->next_p != NULL)
        {
            printf("||ID: %d , Priority: %d|| -> ", (int)tempProc->identifier, (int)tempProc->priority);

            tempNode = tempNode->next_p;
            tempProc = (process_t*) tempNode->data;
        }

        printf("||ID: %d , Priority: %d||\n", (int)tempProc->identifier, (int)tempProc->priority);
    }
}
