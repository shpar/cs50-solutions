/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// positions
int pos[2];
int emptypos[2];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// prototype helpers
bool checkMove(void);
void findTile(int tile);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(200000);
        }

        // sleep thread for animation's sake
        usleep(200000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(1000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    // fills board with decreasing numbers
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
            board[i][j] = d*d - i*d - j - 1;
    }
    
    // replaces last two numbers on board if number of tiles is odd
    if (d % 2 == 0)
    {
        board[d-1][d-2] = 2;
        board[d-1][d-3] = 1;
    }
    
    // initial position of empty tile
    emptypos[0] = d - 1;
    emptypos[1] = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // prints out single/two digit tiles and the empty tile on current board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == 0)
                printf("\x1B[31m X  \x1B[0m");
            else if (board[i][j] < 10)
                printf(" %i  ", board[i][j]);
            else
                printf("%i  ", board[i][j]);
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // checks if tile number is legal for current dimension
    if (tile < 0 || tile > (d*d - 1))
        return false;

    findTile(tile);
    
    // if move is legal replaces tile values and updates empty tile position
    if (checkMove())
    {
        board[emptypos[0]][emptypos[1]] = board[pos[0]][pos[1]];
        board[pos[0]][pos[1]] = 0;
        emptypos[0] = pos[0];
        emptypos[1] = pos[1];
        return true;
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    // returns false in case board is not in winning position yet
    for (int i = 0; i < d - 1; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] != j + i*d + 1)
                return false;
        }
    }
    for (int j = 0; j < d - 1; j++)
    {
        if (board[d-1][j] != j + d*d - d + 1)
            return false;
    }        
    return true;
}

bool checkMove(void) 
{
    // checks if selected tile is next to an empty tile
    if (emptypos[0] == pos[0] && (emptypos[1] - 1 == pos[1] || emptypos[1] + 1 == pos[1]))
        return true;
    else if (emptypos[1] == pos[1] && (emptypos[0] - 1 == pos[0] || emptypos[0] + 1 == pos[0]))
        return true;
    else
        return false;
}

void findTile(int tile) 
{
    // linear search for tile position in board
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {    
                pos[0] = i;
                pos[1] = j;
            }
        }
    }
}