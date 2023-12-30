#include <stdio.h>

int main(void)
{
    char *a = "HI!";
    printf("%p\n", a); //%p will print the adress
    printf("%p\n", &a[0]);
    printf("%p\n", &a[1]);
    printf("%p\n", &a[2]);
    printf("%p\n", &a[3]);
}