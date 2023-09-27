/*
* queue.h / Process Queue
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 27, 2023
*
*/

typedef struct process {
	int identifier;
	char* name;
	long runtime;
	int priority;
}process_t;

typedef struct node {
    void* data;
    struct node* next_p;
    struct node* prev_p;
}node_t;

typedef struct queue_s {
    int count;
    node_t* head_p;
    node_t* tail_p;
}queue_t;

queue_t* createQ();

process_t* createProc(int id, char* name, long runtime, int priority);

int add2q(queue_t* queue, void* element);

void* popQ(queue_t* queue);

process_t* rmProcess(queue_t* queue);

int qsize(queue_t* queue);

void freeQ(queue_t* queue);

void printProcessQ(queue_t* queue);
