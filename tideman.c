#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //compare input name and vote input name and if they are the same
        if (strcmp(name, candidates[i]) == 0)
        {
            // rank is 0,1,2 order and i is whatever number we input, that number is stored in ranks[as RANK number 0,1,2 in the order of input]
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // while i is smaller than candidate count, for loop will run
    for (int i = 0; i < candidate_count; i++)
    {
        //while j is smaller then candidate count, for loop will run
        //this allows to see that i has more votes then j becayuse j = i++(that somehow bugged the code so i + 1) which is in a loop
        //because its in a loop and is being constantly updated we can see that i value is better then all the values that were added in the j for loop
        for (int j = i + 1; j < candidate_count; j++)
        {
            //we increment so that
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //for the for loops its the same idea as before in record_preferences
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            //but here we need to add comparison to identify which should be the winner and which shoul dbe the loser
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                //we increment pair_count so that when the i for loop runs again we store the comparison answer in a different spot inside the array
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    // first loop is need to go through all pairs one by one
    for (int i = 0; i < pair_count; i++)
    {
        // the inside loop is needed to compare the chosen in i loop pair to all other pairs
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[i].winner][pairs[i].loser] < preferences[pairs[j].winner][pairs[j].loser])
            {
                temp = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = temp;
            }
        }
    }
    return;
}

//this was the most challenging part
//so this function will use int loser and winner
bool cycle_check(int loser, int winner)
{
    // using recursion concept, the first thing we do is check if loser is the same as winner.
    //if it is then we return true which ends the cycle
    //if false then we go onto the for loop
    if (loser == winner)
    {
        return true;
    }
    // in the for loop we check if loser is locked with any of the candidates
    // if it is then we call this function, except instead we will use i instead of loser, this is needed becuase we checked if any candidates are locked with loser, so now we do same for winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[loser][i])
        {
            if (cycle_check(i, winner))
            {
                return true;
            }
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        // if cycle check is returned as false for i.loser and i.winner then we lock the pair
        if (!cycle_check(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // loop for the amount of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // create a bool variable for identificication, can use int but bool is just simpler
        bool looser = false;
        // loop the second time for candidate amount as we need j to go through each i value (which is essesially a candidate)
        for (int j = 0; j < candidate_count; j++)
        {
            //if j is locked with i then looser is true, if looser is true then loop does continue
            if (locked[j][i])
            {
                looser = true;
            }
        }
        if (looser == true)
        {
            continue;
        }
        // if looser was false on the other hand it means we can print out the candidate in i because that means that there are no arrows connected to them
        else if (looser == false)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}



//well that didnt work, will try to make a function instead--- might see whats wrong with this later

/*for (int i = 0; i < candidate_count; i++)
{
    for (int j = i + 1; j < pair_count; j++)
    {
        //check if the loser has already been used
        if (pairs[i].loser == pairs[j].winner)
        {
            // skip to the next iteration
            continue;
        }
        //if not then we check if its NOT locked in with something already
        else if (locked[pairs[i].loser][i] != 0)
        {
            //if its not then we add the locked pair in
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}
*/