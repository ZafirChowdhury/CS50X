https://github.com/ZafirChowdhury

int get_hight(void);

int main(void)
{

int hight = get_hight();

    for (int i = 1; i < (hight+1); i++)
    {

        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        printf("\n");

    }
}


int get_hight(void)
{
    int hight;

    do
    {
        hight = get_int("Hight of the piramid: ");
    }
    while (hight < 1);

    return hight;
}