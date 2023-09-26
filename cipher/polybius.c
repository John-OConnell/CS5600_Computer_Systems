/*
* polybius.c / Create Cipher
*
* John O'Connell / CS5600 / Northeastern University
* Fall 2023 / Sep 26, 2023
*
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "polybius.h"

/*
 * Prints the help message for the cipher program
 * 
 */
void print_help(){
	printf("cipher. (2023 Sep 26)\n\n");
	printf("Usage: cipher (arguments)");
	printf(" <your_text_here>\n\n");
	printf("Arguments:\n");
	printf("  -e            Ecodes a plain text string.\n");
	printf("  -d            Decodes a cipher text string.\n");
	printf("  -h  or  --h   Print this help message.\n");
}

/*
 * Converts a plain text string into cipher text using an input polybius square
 *
 * @param plaintext: the plain text string
 * @param table: the polybius table used for encoding
 * 
 */
void pbEncode(const char *plaintext, char table[SQUARE_SIZE][SQUARE_SIZE])
{
    // get length of input string
    int len = strlen(plaintext);

    for (int i = 0; i < len; i++)
    {
        char ch = toupper(plaintext[i]);

        // check if character is in polybius table
        if (ch >= 58 && ch <= 90)
        {
            for (int j = 0; j < SQUARE_SIZE; j++)
            {
                for (int k = 0; k < SQUARE_SIZE; k++)
                {
                    if (ch == table[j][k])
                    {
                        printf("%d%d", j+1, k+1);
                    }
                }
            }
        }
        // leave characters not in polybius table as is
        else
        {
            printf("%c", ch);
        }
    }
    return;
}

/*
 * Converts a cipher text string into plain text using an input polybius square
 *
 * @param ciphertext: the cipher text string
 * @param table: the polybius table used for decoding
 * 
 */
void pbDecode(const char *ciphertext, char table[SQUARE_SIZE][SQUARE_SIZE])
{
    // get length of input string
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i++)
    {
        char row = ciphertext[i];
        char col = ciphertext[i+1];

        // check if characters are digits
        if (isdigit(row) &&  isdigit(col))
        {
            int row_n = row - '1';
            int col_n = col - '1';

            // check if row and column nums fall within table bounds
            if (row_n >= 0 && row_n < SQUARE_SIZE && col_n >= 0 && col_n < SQUARE_SIZE)
            {
                printf("%c", table[row_n][col_n]);
                i++;
            }
            else
            {
                // print err if out of bounds of table
                printf("err");
            }
        }
        else
        {
            // leave all other non digit characters as is
            printf("%c", ciphertext[i]);
        }
    }
    return;
}
