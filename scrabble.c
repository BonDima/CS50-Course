#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

int counter, word1len, word2len, word_number;
int total1, total2;
string word1, word2;
int n = 0;
char wordUP;
int score1, score2;
int letter;

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    word1 = get_string("Player 1: ");
    word2 = get_string("Player 2: ");
    word1len = strlen(word1);
    word2len = strlen(word2);
    //MAKE UPPERS

    while (word1[counter])
    {
        wordUP = word1[counter];
        word1[counter] = toupper(wordUP);
        counter++;
    }
    word_number++;
    counter = 0;

    while (word2[counter])
    {
        wordUP = word2[counter];
        word2[counter] = toupper(wordUP);
        counter++;
    }

    word_number = 0;

    // Score both words
    score1 = compute_score(word1);
    score2 = compute_score(word2);

    // TODO: Print the winner

    if (total1 > total2)
    {
        printf("Player 1 Wins! \n");
    }
    else if (total1 < total2)
    {
        printf("Player 2 Wins! \n");
    }
    else
    {
        printf("Tie! \n");
    }
    return 0;
}




int compute_score(string word)
{
    // TODO: Compute and return score for string
    if (word_number == 0)
    {
        for (counter = 0; counter < word1len; counter++)
        {
            //take the first letter of the word using n (the counter) and turning that letter into an integer to get the ASCII value
            letter = (int) word1[n];
            //convert the letter into upper if its not already
            letter = toupper(letter);
            //check if the letter is between the 1st upper number "A" and last upper number "Z"
            if (letter > 64 && letter < 91)
            {
                letter = letter - 65;
                total1 = total1 + POINTS[letter];
                n++;
            }
            else
            {
                // if not in between then add 1 to counter and move on
                n++;
            }
        }
        word_number = 1;
        n = 0;
        letter = 0;
        printf("TOTAL 1: %i \n", total1);
        return total1;
    }

    else if (word_number == 1)
    {
        for (counter = 0; counter < word2len; counter++)
        {
            //take the first letter of the word using n (the counter) and turning that letter into an integer to get the ASCII value
            letter = (int) word2[n];
            //convert the letter into upper if its not already
            letter = toupper(letter);
            //check if the letter is between the 1st upper number "A" and last upper number "Z"
            if (letter > 64 && letter < 91)
            {
                // -65 from that number in order have same numbers as the list (start from 0) so if its A it will be value 0 and worth 1 point
                letter = letter - 65;
                total2 = total2 + POINTS[letter];
                n++;
            }
            else
            {
                n++;
            }
        }
        printf("TOTAL 2: %i \n", total2);
        return total2;
    }
    else
    {
        return 1;
    }
}
