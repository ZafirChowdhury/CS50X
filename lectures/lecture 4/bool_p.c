#include <stdio.h>
#include <stdbool.h>

int main(void)
{
    bool n = true;
    int *p = &n;
    printf("%p\n", p);
}