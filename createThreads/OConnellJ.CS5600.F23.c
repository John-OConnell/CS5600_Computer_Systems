/*
* OConnellJ.CS5600.F23.c / Threads
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 2, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Create global array for threads to share
int SHARED_ARRAY[50] = {0};

// Function for thread X to write to SHARED_ARRAY
void *worker1(void *data)
{
    char *name = (char*)data;

    for (int i = 0; i < 50; i++)
    {
        usleep(50000);
        printf("Hi from thread name = %s\n", name);
        printf("Writing %d to SHARED_ARRAY\n", i);
        // Adding values to SHARED_ARRAY
        SHARED_ARRAY[i] = i;
        printf("----------------------------\n");
    }

    printf("Thread %s done!\n", name);
    return NULL;
}

// Function for thread Y to read from SHARED_ARRAY
void *worker2(void *data)
{
    char *name = (char*)data;

    for (int i = 0; i < 50; i++)
    {
        usleep(50000);
        printf("Hi from thread name = %s\n", name);
        // Reading values from SHARED_ARRAY
        printf("Read %d from SHARED_ARRAY\n", SHARED_ARRAY[i]);
        printf("----------------------------\n");
    }

    printf("Thread %s done!\n", name);
    return NULL;
}


int main(void)
{
    pthread_t th1, th2;
    pthread_create(&th1, NULL, worker1, "X");
    pthread_create(&th2, NULL, worker2, "Y");
    sleep(1);
    sleep(1);
    printf("====> Cancelling Thread Y, ID: %ld!\n", (long)th2);
    pthread_cancel(th2);
    usleep(100000);
    printf("====> Cancelling Thread X, ID: %ld!\n", (long)th1);
    pthread_cancel(th1);
    printf("Exiting from main program\n");

    //pthread_join(th1, NULL); // leftover from implementing code in article
    //pthread_join(th2, NULL); // leftover from implementing code in article

    return 0;
}

/* ANSWER TO TASK 4:
 * No, I do not get consistency when I run the code from task 3. With the way the code is currently written, 
 * one should not expect a guarantee of consistency between threads. When multiple threads attempt to access and 
 * modify the same shared data simultaneously without synchronization, it can lead to memory consistency errors. 
 * This is because the threads are independent and there is no guarantee about the order in which they will be executed. 
 * This phenomenon is what’s known as a “race condition” in multithreading. Race conditions can be dangerous because 
 * attackers can exploit the race behavior by running a parallel process against a “privileged” program in an attempt to 
 * gain access to otherwise protected information. There are several approaches that can be used to detect thread 
 * interface and memory consistency errors in a program. For example, there are different synchronization mechanisms 
 * such as mutexes, semaphores, and monitors that allow threads to coordinate their access to shared data and therefore 
 * prevent thread interference. Another approach is to use transactions to ensure that memory accesses by multiple threads 
 * are atomic and consistent. Transactions are when multiple memory accesses are treated as a single, indivisible operation.
 *
 * Source: https://www.geeksforgeeks.org/c-program-to-show-thread-interface-and-memory-consistency-errors/
*/

