#include <cs50.h>
#include <stdio.h>
#include <math.h>
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
bool cycle(int loser, int start_of_cycle);
void lock_pairs(void);
int find_pointer(int source);
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
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("%i, %i\n", pairs[i].winner, pairs[i].loser);
    //}
    lock_pairs();
    //for (int i = 0; i < pair_count; i++)
    //{
    //    printf("%i index with %i index is %i\n", pairs[i].winner, pairs[i].loser, locked[pairs[i].winner][pairs[i].loser]);

    //}
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}


// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    pair temporary;

    for (int i = 0; i < pair_count - 1; i++)
    {
        int ith_sum = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].loser];
        for (int j = i + 1; j < pair_count; j++)
        {
            int jth_sum = preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].loser];
            if (ith_sum < jth_sum)
            {
                temporary = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temporary;
            }
        }
    }
    return;
}




bool cycle(int loser, int start_of_cycle)
{
    // base case
    if (loser == start_of_cycle)
    {
        return true;
    }

    bool result = false;
    for (int i = 0; i < pair_count; i++)
    {
        if (pairs[i].winner == loser && locked[pairs[i].winner][pairs[i].loser])
        {
            result = result || cycle(pairs[i].loser, start_of_cycle);
        }
    }
    return result;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}


int find_pointer(int source)
{
    for (int i = 0; i < pair_count; i++)
    {
        if (locked[i][source])
        {
            source = find_pointer(i);
        }
    }
    return source;
}

// Print the winner of the election
void print_winner(void)
{
    //TODO
    for (int i = 0; i < pair_count; i++)
    {
        for (int j = 0; j < pair_count; j++)
        {
            if (locked[i][j])
            {
                int source = find_pointer(i);
                printf("%s\n", candidates[source]);
                return;
            }
        }
    }

    return;
}
