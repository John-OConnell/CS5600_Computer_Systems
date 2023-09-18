/*
* OConnellJ.CS5600.LearnC.c / Memory Management
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

dynBlock* allocDynBlock(int size){

	dynBlock* d = (dynBlock*)malloc(sizeof(dynBlock) + sizeof(int) * size);
	d->size = size;

	return d;
}

void storeMem2Blk(dynBlock* d, int* arr){
	
	for (int i = 0; i < d->size; i++)
	{
		d->block[i] = arr[i];
	}
	return;
}

int countLines(FILE* file){
	if(file==NULL)
	{
		printf("File does not exist!");
		return -1;
	}

	int lineCount = 0;
	char ch;

	while((ch=fgetc(file))!=EOF) 
	{
		if(ch=='\n')
		{
			lineCount++;
		}
	}

	return lineCount;
}

int countWords(char* line){
	int count = 0;
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (line[i] == ' ' || line[i+1] == '\0')
            count++;
	}

	return count;
}

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

void freeBlocks(dynBlock* blocks[], int size){
	
	for (int i = 0; i < size; i++)
	{
		free(blocks[i]);
	}
}

int main(){

	FILE* fp = fopen("blocks.data", "r");

	int lineCount = countLines(fp);

	rewind(fp);
	
	dynBlock* lines[lineCount];

	char line[256];

	int i = 0;
	
	while (fgets(line, sizeof(line), fp))
	{ 
		//printf("%s", line);
		line[strcspn(line, "\n")] = 0;
		int count = countWords(line);
		//printf("%d\n", count);

		dynBlock* newBlock = allocDynBlock(count);
		
		int arr[count];
		char* num = strtok(line, " ");
		int j = 0;
		while( num != NULL)
		{
			//printf("%s\n", num);
			arr[j] = atoi(num);
			num = strtok(NULL, " ");
			j++;
		}
		
		storeMem2Blk(newBlock, arr);
		lines[i] = newBlock;
		i++;
	}

	printBlocks(lines, lineCount);
	freeBlocks(lines, lineCount);

	fclose(fp);


	//int arr[4] = {1, 2, 3, 4};
	//dynBlock* myBlock = allocDynBlock(4);
	//storeMem2Blk(myBlock, arr);
	//for (int i = 0; i < myBlock->size; i++)
	//{
	//	printf("%d", myBlock->block[i]);
	//}
	//printf("\n");

	return 0;
}

