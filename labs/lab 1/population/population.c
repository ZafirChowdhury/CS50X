#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Starting population size: ");
    }
    while (start < 9);

    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("Ending population size: ");
    }
    while (start > end);

    // TODO: Calculate number of years until we reach threshold
    int year = 0;
    while (start < end)
    {
        int temp = start;

        start = start + (temp/3);
        start = start - (temp/4);
        year = year + 1;
    }

    // TODO: Print number of years
    printf("Years: %i\n", year);
}
