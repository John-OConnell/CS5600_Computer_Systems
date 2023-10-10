/*
* polybius.h / Create Cipher
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 26, 2023
*
*/

#define SQUARE_SIZE 6

void print_help();

char* pbEncode(const char *plaintext, char table[SQUARE_SIZE][SQUARE_SIZE]);

void pbDecode(const char *ciphertext, char table[SQUARE_SIZE][SQUARE_SIZE]);
