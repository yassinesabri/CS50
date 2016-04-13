/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements the Game of Fifteen (generalized to d x d).
 *
 * Usage: ./fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [MIN,MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// board's minimal dimension
#define MIN 3

// board's maximal dimension
#define MAX 9

// board, whereby board[i][j] represents row i and column j
int board[MAX][MAX];

// board's dimension
int d;

//global variables
int tile_r = 0;
int tile_c = 0;
int blank_r = 0;
int blank_c = 0;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);
void save(void);

int main(int argc, string argv[])
{
    // greet player
    greet();

    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < MIN || d > MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            MIN, MIN, MAX, MAX);
        return 2;
    }

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // saves the current state of the board (for testing)
        save();

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep for animation's sake
        usleep(500000);
    }

    // that's all folks
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
    printf("GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1,
 * (i.e., fills board with values but does not actually print them),
 * whereby board[i][j] represents row i and column j.
 */


void init(void)
{
    //check if the number of tiles is odd or not
    bool odd = false;
    int number_til = d*d-1;
    //fisrt position of the blank tile
    blank_r = d-1;
    blank_c = d-1;
    
    if (number_til%2 != 0) 
        odd = true;
        
    for(int r = 0;r < d;r++) //r : row
    {
        for(int c = 0;c < d;c++) //c : colum
        {
            board[r][c] = number_til;
            number_til--;
        }
    }
    if(odd)
    {
        int temp;
        temp = board[d-1][d-2];
        board[d-1][d-2] = board[d-1][d-3];
        board[d-1][d-3] = temp;
            
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
     for(int r = 0;r < d;r++) //r : row
    {
        for(int c = 0;c < d;c++) //c : colum
        {
            if(board[r][c] < 10)
                printf(" ");    
            if(board[r][c] != 0)
                printf(" %d ",board[r][c]);
            else
                printf(" _ "); // for the blank tile
        }
        printf("\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool find_tile(int tile)
    {
        for (int r = 0; r < d; r++)//r : row
        {
            for (int c = 0; c < d; c++)//c : colum
            {
                if (board[r][c] == tile)
                {
                    tile_r = r;
                    tile_c = c;
                    return true;
                }
            }
        }
        return false;
    }
bool check_move(void)
    {
        if (tile_r > 0 && board[tile_r - 1][tile_c] == 0) //check up
        {
            return true;
        }
        else if (tile_r <= d-2 && board[tile_r + 1][tile_c] == 0) //down
        {
            return true;
        }
        else if (tile_c > 0 && board[tile_r][tile_c - 1] == 0) //left
        {
            return true;
        }
        else if (tile_c <= d-2 && board[tile_r][tile_c + 1] == 0) //right
        {
            return true;
        }
        else
        {
            return false;
        }
    }
bool move(int tile)
{
   
   if (find_tile(tile))
   {
        // If true switch it.
        if (check_move())
        {
            int temp_r = tile_r;
            int temp_c = tile_c;
            int temp = board[tile_r][tile_c];
            board[tile_r][tile_c] = board[blank_r][blank_c];
            board[blank_r][blank_c] = temp;
            blank_r = temp_r;
            blank_c = temp_c;
            return true;
        }   
        
    }
    return false;
}


/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    int tile_number = 1;
    int counter = 1;
    for(int r = 0;r < d;r++) //r : row
    {
        for(int c = 0;c < d;c++) //c : colum
        {
            if ( board[r][c] == tile_number && counter == tile_number)
            {
                if(tile_number == d*d-1)
                    return true;
            } 
            counter++;  
        }
        
    }
    return false;
}

/**
 * Saves the current state of the board to disk (for testing).
 */
void save(void)
{
    // log
    const string log = "log.txt";

    // delete existing log, if any, before first save
    static bool saved = false;
    if (!saved)
    {
        unlink(log);
        saved = true;
    }

    // open log
    FILE* p = fopen(log, "a");
    if (p == NULL)
    {
        return;
    }

    // log board
    fprintf(p, "{");
    for (int i = 0; i < d; i++)
    {
        fprintf(p, "{");
        for (int j = 0; j < d; j++)
        {
            fprintf(p, "%i", board[i][j]);
            if (j < d - 1)
            {
                fprintf(p, ",");
            }
        }
        fprintf(p, "}");
        if (i < d - 1)
        {
            fprintf(p, ",");
        }
    }
    fprintf(p, "}\n");

    // close log
    fclose(p);
}
