#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    int length = strlen(argv[1]);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    int key = atoi(argv[1]);
    key = key % 26;

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");
    char curr_char;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            curr_char = ((toupper(plaintext[i]) - 65) + key) % 26 + 65;

            if (islower(plaintext[i]))
            {
                curr_char += 32;
            }
        }
        else
        {
            curr_char = plaintext[i];
        }
        printf("%c", curr_char);
    }
    printf("\n");
}
