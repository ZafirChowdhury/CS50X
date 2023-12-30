#include <stdio.h>
#include <cs50.h>

void draw(int hight);

int main(void)
{
    int hight = get_int("Hight: ");
    draw(hight);
}


void draw(int hight)
{
    if (hight < 1)
    {
        return;
    }

    draw(hight - 1);

    for (int i = 0; i < hight; i++)
    {
        printf("#");
    }
    printf("\n");
    return;
}