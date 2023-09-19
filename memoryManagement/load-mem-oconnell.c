/*
* load-mem-oconnell.c / Memory Management
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dynamicBlock{

	int size;
	int block[];

}dynBlock;

/*
 * Allocates a dynBlock struct with an integer array of input size
 * 
 * @param size: the size of the integer array inside of the dynBlock struct
 *
 * @return d: a pointer to the newly created dynBlock struct
 *
 */
dynBlock* allocDynBlock(int size){

	dynBlock* d = (dynBlock*)malloc(sizeof(dynBlock) + sizeof(int) * size);
	d->size = size;

	return d;
}

/*
 * Copies an integer array into a dynBlock struct
 *
 * @param d: a pointer to the dynBlock struct
 * @param arr: the array to be stored in the dynBlock struct
 * 
 */
void storeMem2Blk(dynBlock* d, int* arr){
	
	for (int i = 0; i < d->size; i++)
	{
		d->block[i] = arr[i];
	}
	return;
}

/*
 * Counts the number of lines in a file
 *
 * @param file: a pointer to the file
 *
 * @return lineCount: the number of lines in the file
 * 
 */
int countLines(FILE* file){
	if(file==NULL)
	{
		printf("File does not exist!");
		return -1;
	}

	int lineCount = 0;
	int ch;

	while((ch=fgetc(file))!=EOF) 
	{
		if((char)ch=='\n')
		{
			lineCount++;
		}
	}

	// move pointer back to start of file
	rewind(file);

	return lineCount;
}

/*
 * Counts the number of words in a string
 * 
 * @param line: the input string
 *
 * @return count: the number of words in the string
 * 
 */
int countWords(char* line){
	int count = 0;
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == ' ' || line[i+1] == '\0')
            count++;
	}

	return count;
}

/*
 * Prints the integer arrays stored in each dynBlock from an
 * input array of dynBlocks
 *
 * @param blocks: an array of dynBlock structs
 * @param size: the size of the blocks array
 * 
 */
void printBlocks(dynBlock* blocks[], int size){

	for (int i = 0; i < size; i++)
	{
		printf("Line %d contains %d numbers:\n", i+1, blocks[i]->size);
		for (int j = 0; j < blocks[i]->size; j++)
		{
			printf("%d ", blocks[i]->block[j]);
		}
		printf("\n");
	}

}

/*
 * Frees all dynBlocks structs in an array of dynBlocks
 *
 * @param blocks: an array of dynBlock structs
 * @param size: the size of the blocks array
 * 
 */
void freeBlocks(dynBlock* blocks[], int size){
	
	for (int i = 0; i < size; i++)
	{
		free(blocks[i]);
	}
}

int main(){

	// open file
	FILE* fp = fopen("blocks.data", "r");

	// test for file not existing
        if (fp == NULL)
	{	
              printf("Error! Could not open file\n");
              return -1;
	}
	
	// initializing necessary variables	
	int lineCount = countLines(fp);
	dynBlock* lines[lineCount];
	char line[256];
	int i = 0;
	
	// loop through file to process
	while (fgets(line, sizeof(line), fp))
	{ 
		// remove newline character and get word count
		line[strcspn(line, "\n")] = 0;
		int count = countWords(line);

		// initialize dynBlock struct
		dynBlock* newBlock = allocDynBlock(count);
		
		int arr[count];
		char* num = strtok(line, " ");
		int j = 0;

		// loop through each line adding numbers to temp array
		while( num != NULL)
		{
			int temp = atoi(num);
			if (temp == 0)
			{
			fputs("Invalid number detected!\n", stderr);
			}
			arr[j] = temp;
			num = strtok(NULL, " ");
			j++;
		}
		
		// store temp array into dynBlock integer array
		storeMem2Blk(newBlock, arr);

		lines[i] = newBlock;
		i++;
	}

	// print the integer array stored in all dynBlocks
	printBlocks(lines, lineCount);

	// free all dynBlock structs created
	freeBlocks(lines, lineCount);
	
	// close the file
	fclose(fp);

	return 0;
}

