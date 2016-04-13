//
// breakout.c
//
// Computer Science 50
// Problem Set 4
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include "gevents.h"
#include "gobjects.h"
#include "gwindow.h"

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

double x_velocity = 1.5;
double y_velocity = 3.0;

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    // wait for click before launching the game
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {       
        // update Scoreboard
        updateScoreboard(window, label, points);
           
        move(ball, x_velocity, y_velocity);

        pause(10);
       
        GEvent event = getNextEvent(MOUSE_EVENT);
       
        // Lock the paddle X to the cursor.
        if (event != NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                // for the paddle to follow the top of the cursor
                double x = getX(event) - getWidth(paddle) / 2;
                double y = 500;
                setLocation(paddle, x, y);
            }
        }
       
       
        GObject object = detectCollision(window, ball);
       
        if (object != NULL)
        {
            // If the ball hits the paddle.
            if (object == paddle)
            {
                y_velocity = -y_velocity;
            }
           
            // If the ball hits a block
            else if (strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                y_velocity = -y_velocity;
                points++;
                bricks--;               
            }
        }
       
        // If the ball hits the right side
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
            x_velocity = -x_velocity;
        }
       
        // If the ball hits the left side
        if (getX(ball) <= 0)
        {
            x_velocity = -x_velocity;
        }
       
        // If the ball hits the top side
        if (getY(ball) <= 0)
        {
            y_velocity = -y_velocity;
        }
       
        // If the ball hits the bottom we remove a life
        if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
            lives--;
            setLocation(ball, 190, 200);
            setLocation(paddle, 160, 500);
            waitForClick(); //wait to start over again
        }
       
    }
    //game_over labels
    if(bricks == 0)
    {
        //show a label if the player wins
        GLabel win = newGLabel("Yow, You Win!");
        setFont(win,"SansSerif-40");
        setColor(win,"GREEN");
        add(window,win);
        setLocation(win,50,300);
    }
    else
    {
        //show a label if the player loses
        GLabel lose = newGLabel("Ooh, You LOSE!");
        setFont(lose,"SansSerif-40");
        setColor(lose,"RED");
        add(window,lose);
        setLocation(lose,50,300);   
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int brick_y = 50; //starting y position
    int row_space = 15; //space between each line
    
    for(int i = 0;i < ROWS;i++)
    {
        int brick_x = 2; //starting x position
        for(int j = 0;j < COLS;j++)
        {
            GRect brick = newGRect(brick_x+5,brick_y,30,10);
             // set the break's color for each row
             if(i == 0)
                setColor(brick,"GREEN");
             if(i == 1)
                setColor(brick,"ORANGE");
             if(i == 2)
                setColor(brick,"RED");
             if(i == 3)
                setColor(brick,"BLUE");
             if(i == 4)
                setColor(brick,"FF00FF"); //purple color
             
             setFilled(brick,true);
             add(window,brick);
             brick_x += 39; // space between each two bricks in a row          
        }
        
        brick_y += 20; // space between each two bricks in a Col
    }
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    GOval ball = newGOval(WIDTH/2-RADIUS,HEIGHT/2,2*RADIUS,2*RADIUS);
    setColor(ball,"BLACK");
    setFilled(ball,true);
    add(window,ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    GRect paddle = newGRect(WIDTH/2-40,HEIGHT-100,80,15);
    setColor(paddle,"808080"); //for a dark gray
    setFilled(paddle,true);
    add(window,paddle);
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    GLabel label = newGLabel("");
    setColor(label,"C0C0C0"); //for the silver color
    setFont(label,"SansSerif-65");
    add(window,label);
    setLocation(label,WIDTH-10,HEIGHT/2);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
