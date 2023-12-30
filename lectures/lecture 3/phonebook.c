#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int number_of_people_in_phoenbook = 2;

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[number_of_people_in_phoenbook];

    people[0].name = "Polti";
    people[0].number = "016969";

    people[1].name = "Zafir";
    people[1].number = "69420";

    string name = get_string("Name: ");
    for (int i = 0; i < number_of_people_in_phoenbook; i++)
    {
        if (strcmp(people[i].name, name) == 0)
        {
            printf("Number: %s\n", people[i].number);
            return 0;
        }
    }

    printf("Not found\n");
    return 1;
}