// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool isupper = false;
    bool islower = false;
    bool isnumber = false;
    bool issymbol = false;

    int length = strlen(password);

    for (int i = 0; i < length; i++)
    {
        if isupper(password[i])
        {
            isupper = true;
        }
        else if islower(password[i])
        {
            islower = true;
        }
        else if isdigit(password[i])
        {
            isnumber = true;
        }
        else
        {
            issymbol = true;
        }
    }
    return isupper && islower && isnumber && issymbol;
}

