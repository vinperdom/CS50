// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>
#include <string.h>


string replace(string s);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Give me an argument!\n");
        return 1;
    }

    string s = replace(argv[1]);
    printf("%s\n", s);
}

string replace(string s)
{
    int length = strlen(s);

    string output_string = s;

    for (int i = 0; i < length; i++)
    {
        switch (s[i])
        {
            case 'a':
                output_string[i] = '6';
                break;
            case 'e':
                output_string[i] = '3';
                break;
            case 'i':
                output_string[i] = '1';
                break;
            case 'o':
                output_string[i] = '0';
                break;
        }
    }
    return output_string;
}

