/*
* genRand-helper.h / Random Number Generation
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 16, 2023
*
*/

void print_help();

int mystrcmp(const char* str1, const char* str2);

void setSeed(int* seed, int value);

int genRand(int min, int max, int* seed);
