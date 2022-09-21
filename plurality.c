#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;
int voter_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int counter = 0; counter < candidate_count; counter++)
    {
        if (strcmp(name, candidates[counter].name) == 0)
        {
            candidates[counter].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int counter;
    bool sort = false;
    int temp = 0;
    string temp1;
    counter = 0;
    int highest_vote = candidates[0].votes;

    for (counter = 1; counter < candidate_count; counter++)
    {
        if (candidates[counter].votes > highest_vote)
        {
            highest_vote = candidates[counter].votes;
        }
    }

    for (counter = 0; counter < candidate_count; counter++)
    {
        if (candidates[counter].votes == highest_vote)
        {
            printf("%s\n", candidates[counter].name);
        }
    }
    return;
}

// VERY SAD but unfortunately the cs50 has issues with bubble sort
//bubblesort to sort the values in the order of highest -> lowest
/*while (!sort)
{
sort = true;
//voter_count cuz we want to run it for each voter
for (counter = 1; counter < voter_count; counter++)
{
    if (candidates[counter - 1].votes < candidates[counter].votes)
    {
        temp = candidates[counter].votes;
        temp1 = candidates[counter].name;

        candidates[counter].votes = candidates[counter - 1].votes;
        candidates[counter].name = candidates[counter - 1].name;

        candidates[counter - 1].votes = temp;
        candidates[counter - 1].name = temp1;

        sort = false;
    }
}
}*/