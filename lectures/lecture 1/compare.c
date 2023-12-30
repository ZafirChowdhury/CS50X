#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int x = get_int("X: ");
    int y = get_int("Y: ");

    if (x < y)
    {
        printf("%i is less then %i\n", x, y);
    }

    else if (x > y)
    {
        printf("%i is greater then %i\n", x, y);
    }

    else
    {
        printf("%i and %i are  equal\n", x, y);
    }
}
