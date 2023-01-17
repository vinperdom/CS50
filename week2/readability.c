#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    int L = 0;
    int S = 0;
    int W = 1;
    int length = strlen(text);
    for (int i = 0; i < length; i++)
    {
        if (text[i] == ' ')
        {
            W++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            S++;
        }
        else if (isalpha(text[i]))
        {
            L++;
        }
    }

    float l = L * 100 / (float) W;
    float s = S * 100 / (float) W;

    int grade = round(0.0588 * l - 0.296 * s - 15.8);
    if (grade < 1)
    {
        printf("Before Grade 1\n");

    }
    else if (grade > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}
