#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");

    // Get size
    int size = 0;
    long copy_number = number;
    while (copy_number > 0)
    {
        copy_number = copy_number / 10;
        size++;
    }

    // Make a arr then insert the numbers in them
    // The arr will be reversed
    int numbers[size];
    int last_digit;
    for (int i = 0; number > 0; i++)
    {
        last_digit = number % 10;
        numbers[i] = last_digit;
        number = number / 10;
    }

    int sum_odd_2x = 0;
    int sum_even = 0;
    for (int x = 0; x < size; x++)
    {
        if ((x % 2) != 0)
        {
            int digit_sum = 0;
            int digit = (numbers[x] * 2);
            while (digit > 0)
            {
                digit_sum = digit_sum + (digit % 10);
                digit = digit / 10;
            }

            sum_odd_2x = sum_odd_2x + digit_sum;
        }

        else
        {
            sum_even = sum_even + numbers[x];
        }
    }

    int check_sum = sum_odd_2x + sum_even;
    if ((check_sum % 10) == 0)
    {
        // American Express
        if (size == 15)
        {
            int first_digit = numbers[size-1];
            int second_digit = numbers[size-2];

            if (first_digit == 3 && (second_digit == 4 || second_digit == 7))
            {
                printf("AMEX\n");
                return 0;
            }

            else
            {

                 printf("INVALID\n");
                 return 0;
            }
        }

        // Visa
        else if ((size == 13 || size == 16) && (numbers[size-1] == 4))
        {
            printf("VISA\n");
            return 0;
        }

        // MasterCard
        else if (size == 16 && (numbers[size-1] == 5))
        {
            int second_number = numbers[size-2];
            if (second_number > 0 && second_number < 6)
            {
                 printf("MASTERCARD\n");
                 return 0;
            }
        }

        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    else
    {
        printf("INVALID\n");
        return 0;
    }

    printf("INVALID\n");
    return 0;
}