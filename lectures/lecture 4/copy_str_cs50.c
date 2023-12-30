#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *s = get_string("S: ");

    int len = strlen(s);

    char *t = malloc(len+1);

    for (int i =0; i < len+1; i++)
    {
        t[i] = s[i];
    }

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("S: %s\n", s);
    printf("T: %s\n", t);
}