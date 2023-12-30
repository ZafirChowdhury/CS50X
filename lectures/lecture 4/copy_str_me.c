#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    char *x = "hi!";

    int len = strlen(x);

    //Copy
    char x_copy[len];

    for (int i = 0; i < len; i++)
    {
        x_copy[i] = x[i];
    }
    x_copy[len] = '\0';

    x_copy[0] = toupper(x_copy[0]);

    printf("%s\n", x);
    printf("%s\n", x_copy);
}