#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char A[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

void print_arr(char arr[], int size);
int check_key(char arr[], int size);

int main(int argc, string argv[])
{
    if (argc == 2)
    {
        string key = argv[1];
        int key_size = strlen(key);

        for (int i = 0; i < key_size; i++)
        {
            key[i] = tolower(key[i]);
        }

        if (key_size == 26)
        {
            int key_ckeck = check_key(key, key_size);

            if (key_ckeck == 1)
            {
                return 1;
            }

            string plain_text = get_string("plaintext: ");
            int plrain_text_size = strlen(plain_text);

            char cipher_text[plrain_text_size];

            for (int j = 0; j < plrain_text_size; j++)
            {
                if (isalpha(plain_text[j]))
                {
                    int is_lower = islower(plain_text[j]);
                    char chr = tolower(plain_text[j]);

                    for (int k = 0; k < key_size; k++)
                    {
                        if (chr == A[k])
                        {
                            if (is_lower != 0)
                            {
                                cipher_text[j] = key[k];
                            }

                            else
                            {
                                cipher_text[j] = toupper(key[k]);
                            }
                        }
                    }

                }

                else
                {
                    cipher_text[j] = plain_text[j];
                }
            }

            print_arr(cipher_text, plrain_text_size);

        }

        else
        {
             printf("Key must contain 26 characters.\n");
             return 1;
        }
    }

    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}


void print_arr(char arr[], int size)
{
    printf("ciphertext: ");
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
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