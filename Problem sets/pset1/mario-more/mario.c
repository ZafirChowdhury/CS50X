#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int hight;
    do
    {
        hight = get_int("Hight: ");
    }
    while (hight < 1 || hight > 8);

    for (int i = 0; i < hight; i++)
    {
        for (int j = 0; j < hight - i - 1; j++)
        {
            printf(" ");
        }

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }

    printf("\n");

    }
}