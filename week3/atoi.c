#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert(string input, int n);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input, 0));
}

int convert(string input, int n)
{
    // TODO
    int length = strlen(input);

    // Base case
    if (length == 0)
    {
        return n;
    }

    // Make new string without first char
    char new_input[length - 1];
    for (int i = 0; i < length - 1; i++)
    {
        new_input[i] = input[i + 1];
    }

    // Sum value to n
    n += (input[0] - '0') * pow(10, length - 1);

    return convert(new_input, n);
}
