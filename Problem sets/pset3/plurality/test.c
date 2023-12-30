#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    int votes;
}
candidate;

int main(void)
{
    
}

int vote(string name)
{
    for (int i = 0; i < MAX; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return 0;
        }
    }
    return 1;
}