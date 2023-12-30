#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string first = get_string("What's your first name? ");
    string second = get_string("What's your second name? ");

    printf("Hello, %s %s  \n", first, second);
}
