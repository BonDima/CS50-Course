// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;
int word_counter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //has a word to recieve a value
    int index = hash(word);
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        //next variable stored in the table
        cursor = cursor -> next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //create a long that will store a sum of first 3 ascii values of a word
    long sum_of_word = 0;
    //for loop that will stop after 3 letters 0,1,2
    for (int counter = 0; counter < strlen(word); counter++)
    {
        //add to the sum the lowered version of a letters ascii value
        sum_of_word += tolower(word[counter]);
    }
    return sum_of_word % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open the dictionary file
    FILE *file = fopen(dictionary, "r");
    //check if it has been opened successfully
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }

    char nextword[LENGTH + 1];
    //loop will run while fscanf is not End Of File
    while (fscanf(file, "%s", nextword) != EOF)
    {
        //assign a new node that will store that word and then copy it to another location
        node *temp = malloc(sizeof(node));
        //check if its empty
        if (temp == NULL)
        {
            return false;
        }

        strcpy(temp -> word, nextword);
        //decide which index ill use to insert the word to
        int index = hash(nextword);
        temp -> next = table[index];
        table[index] = temp;
        word_counter += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //i was saving that in the load function
    return word_counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *temp = table[i] -> next;
            free(table[i]);
            temp = table[i] = temp;
        }
    }
    return true;
}
