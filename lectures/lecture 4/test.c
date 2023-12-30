#include <stdio.h>

int main(void)
{
    int x = 5;
    int y = 5;
    int z = 6;

    printf("%p\n", &x);
    printf("%p\n", &y);
    printf("%p\n", &z);
}