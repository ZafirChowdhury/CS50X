#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int times_to_meow = get_int("How many times to meow? ");

    for (int i = 0; i < times_to_meow; i++)
    {
        printf("Meow\n");
    }
}