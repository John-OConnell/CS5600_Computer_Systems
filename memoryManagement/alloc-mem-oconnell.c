/*
* alloc-mem-oconnell.c / Memory Management
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

// NOTE: 1MB = 1024KB = 1024Bytes
// This conversion is used throught this prog


// allocating 5MB of memory on the static segment
// allocated when the program laods
// freed when the program exits
// in this case the program exits when main is terminated
char static_mem[5 * 1024 * 1024];

#include <stdio.h>
#include <stdlib.h>

int main() {
		
	// allocating 10BM of memory on the heap
	char* heap_mem = malloc(10 * 1024 * 1024);

	// ensuring heap mem allocated correctly
	if (heap_mem == NULL)
	{
		printf("Memory allocation from heap failed!\n");
		return -1;
	}

	// freeing memory on the heap
	free(heap_mem);


	// allocating 1MB of memory on the stack
	// allocates when function is entered
	// freed when the function in which it was created terminates 
	// in this case it was created in main so is freed 
	// when main terminates
	char stack_mem[1 * 1024 * 1024];

	return 0;
}

