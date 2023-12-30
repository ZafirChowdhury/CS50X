#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long x = get_long("X: ");
    long y = get_long("Y: ");

    long sum = x + y;

    printf("Sum: %li\n", sum);
}