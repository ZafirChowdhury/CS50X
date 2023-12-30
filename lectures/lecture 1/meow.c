#include <stdio.h>
#include <cs50.h>

int main(void)
{

    int times_to_meow = get_int("How many times to meow? ");

    int counter = 0;

    while (counter < times_to_meow)
    {
        printf("Meow\n");
        counter++;
    }
}