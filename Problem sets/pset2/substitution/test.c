#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char A[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

int check_key(char arr[], int size);

int main(void)
{
    string key = get_string("Key: ");
    int size = strlen(key);

    int c = check_key(key, size);

    if (c == 0)
    {
        printf("Segs\n");
    }

    else
    {
        printf("No Segs\n");
    }
}

int check_key(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (isalnum(arr[i]) == 0)
        {
            return 1;
        }
    }

    int count[26];

    for (int z = 0; z < 26; z++)
    {
        count[z] = 0;
    }

    for (int j = 0; j < size; j++)
    {
        count[arr[j] - 'a']+= 1;
    }

    for (int k = 0; k < size; k++)
    {
        if (count[k] > 1)
        {
            return 1;
        }
    }

    return 0;
}