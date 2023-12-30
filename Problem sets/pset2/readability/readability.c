#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    int letter_count = count_letters(text);
    int word_count = count_words(text);
    int sentence_count = count_sentences(text);

    float L = ((float)letter_count / (float)word_count) * 100;
    float S = ((float)sentence_count / (float)word_count) * 100;

    float float_index = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(float_index);

    if (index > 16)
    {
        printf("Grade 16+\n");
    }

    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade %i\n", index);
    }
}


int count_letters(string text)
{
    int size = strlen(text);
    int letter_count = 0;

    for (int i = 0; i < size; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') ||(text[i] >= 'A' && text[i] <= 'Z'))
        {
            letter_count++;
        }
    }

    return letter_count;
}


int count_words(string text)
{
    int word_count = 1;
    int size = strlen(text);
    for (int i = 0; i < size; i++)
    {
        if (text[i] == 32)
        {
            word_count++;
        }
    }

    return word_count;
}


int count_sentences(string text)
{
    int size = strlen(text);
    int sentence_count = 0;

    for (int i = 0; i < size; i++)
    {
        if (text[i] == 46 || text[i] == 63 || text[i] == 33)
        {
            sentence_count++;
        }
    }

    return sentence_count;
}