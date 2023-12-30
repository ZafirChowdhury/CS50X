#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char user_input = get_char("Do you agree to our terms and agreement (y/n)? ");

    if (user_input == 'y' || user_input == 'Y')
    {
        printf("Agreed.\n");
    }

    else if(user_input == 'n' || user_input == 'N')
    {
        printf("Disagreed.\n");
    }

    else
    {
        printf("Invalid input.\n");
    }
}
