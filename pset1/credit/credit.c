#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    long cc_number = get_long("Number: ");
    int counter = 0;
    int sum = 0;
    long number = cc_number;

    for (; number > 0; number /= 10)
    {
        int digit = number % 10;
        counter++;

        if (counter % 2 == 0)
        {
            sum += ((digit * 2) / 10) + ((digit * 2) % 10);
        }
        else
        {
            sum += digit;
        }
    }

    bool valid = sum % 10 == 0;
    int first_two_digits = cc_number / pow(10, counter - 2);

    if (valid && (counter == 13 || counter == 16) && first_two_digits / 10 == 4)
    {
        printf("VISA\n");
    }
    else if (valid && counter == 16  && first_two_digits >= 51 && first_two_digits <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (valid && counter == 15 && (first_two_digits == 34 || first_two_digits == 37))
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
