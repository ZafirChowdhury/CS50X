#include <stdio.h>
#include <cs50.h>

int main(void)
{
    float x = get_float("X: ");
    float y = get_float("Y: ");

    float div = x / y;

    printf("Div: %f\n", div);
}