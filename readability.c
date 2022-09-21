#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h> //added maths for the round() function

//Some identifying
int length;
int counter = 0;
int count;

int words;
int sentences;
int letters;

// Put the functions before the main
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Text: ");
    length = strlen(text);

    // We use float for these 3 instead of int so that we are able to properly perform maths for L and S, otherswise numbers will be rounded and wrong
    float ans_letters = count_letters(text);
    float ans_words = count_words(text);
    ans_words++;
    float ans_sentences = count_sentences(text);

    // Use float, simple maths to calculate L (avg num of letters per 100 words) and S (avg num of sentences per 100 words)
    float L = (ans_letters / ans_words * 100);
    float S = (ans_sentences / ans_words * 100);;

    float index = (0.0588 * L) - (0.296 * S) - 15.8;
    // use int so we store it as a pretty value with no .0000
    int indexx = round(index);

    // if statements to add after grade 16 and below grade 1
    if (indexx < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (indexx > 16 || indexx == 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", indexx);
    }
}


int count_letters(string text)
{
    // while counter is smaller then length loop goes
    while (counter < length)
    {
        // if value in text[counter] is aplhabetic add 1 to count
        if (isalpha(text[counter]))
        {
            count++;
            // I add 1 to counter at all times as you can see in else, so that I can use length in while statement.
            counter++;
        }
        else
        {
            counter++;
        }
    }
    return count;
}

//everything else is quite literally the same so...
int count_words(string text)
{
    count = 0;
    counter = 0;
    while (counter < length)
    {
        if (isspace(text[counter]))
        {
            count++;
            counter++;
        }
        counter++;
    }
    return count++;
}

int count_sentences(string text)
{
    count = 0;
    counter = 0;
    while (counter < length)
    {
        if ((int) text[counter] == 46 || (int) text[counter] == 33 || (int) text[counter] == 63)
        {
            count++;
            counter++;
        }
        counter++;
    }
    return count++;
}




