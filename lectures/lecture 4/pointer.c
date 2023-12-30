#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    printf("%c%c%c\n", *s, *(s+1), *(s+2)); //*(s+n) 
}