/*
* unittests.c / Multithreading
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Oct 8, 2023
*
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    printf("-----Test 1: Test Invalid Input-----\n");
    system("./multithread");

    printf("\n-----Test 2: Test Passing File That Doesn't Exist-----\n");
    system("./multithread fake.txt");

    printf("\n-----Test 3: Test Encryption Using test.txt-----\n");
    printf("---Use the output to verify correct encryption---\n");
    system("./multithread test.txt");

}