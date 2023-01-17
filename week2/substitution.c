#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool check_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    bool valid = check_key(argv[1]);

    if (!valid)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string plaintext = get_string("plaintext:  ");
    printf("ciphertext: ");

    char curr_char;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]))
        {
            curr_char = toupper(argv[1][toupper(plaintext[i]) - 65]);
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


bool check_key(string key)
{
    int length = strlen(key);

    if (length != 26)
    {
        return false;
    }

    for (int i = 0; i < length; i++)
    {
        if (!isalpha(key[i]))
        {
            return false;
        }
        key[i] = toupper(key[i]);
        for (int j = i + 1; j < length; j++)
        {
            if (key[i] == toupper(key[j]))
            {
                return false;
            }
        }
    }
    return true;
}
