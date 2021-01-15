#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "structs.h"

#define WIDTH 80
#define HEIGHT 25
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define FOOD '@'
#define TOP 205
#define SIDE 186
#define HEAD 178
#define BODY 177
#define STEP 1

void generateFood();
void add_cube();

//  global variables
char board[HEIGHT][WIDTH];
unsigned int score = 0;
bool run = true;
Snake snake;


void delay(int times) 
{
    for (int i = 0; i < times; i++) {}
}

// Initialize board
void initialize_board() {
    // --- top label
    for (int i = 0; i < WIDTH; i++) {
        board[0][i] = TOP;
    }
    // || sides
    for (int i = 1; i < HEIGHT - 1; i++) {
        board[i][0] = SIDE;
        board[i][WIDTH - 1] = SIDE;
    }
    // --- bottom label
    for (int i = 0; i < WIDTH; i++) {
        board[HEIGHT - 1][i] = TOP;
    }
}

// draw board
void draw_board() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++)
        {
            if (board[row][col] != NULL) {
                printf("%c", board[row][col]);
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

void initialize_snake()
{
    Cube *head1 = malloc(sizeof(Cube));

    head1 -> col = WIDTH / 2;
    head1 -> row = HEIGHT / 2;
    head1 -> next = NULL;

    snake.direction = LEFT;
    snake.head = head1;
}


// draw snake
void add_snake_to_board()
{
    Cube *current_cube = snake.head->next;

    printf("row:%d col:%d\n", snake.head->row, snake.head->col);

    
    board[snake.head->row][snake.head->col] = HEAD; // the snake head has different mark
    
                                                   
    // looping through the snake's Cubes
    while (current_cube != NULL)
    {
        board[current_cube->row][current_cube->col] = BODY;
        current_cube = current_cube->next;
    }

}

void add_cube() 
{
    signed int addX, addY;
    Cube* add = malloc(sizeof(Cube));
    Cube* current_cube = snake.head;

    // looping through the snake's Cubes
    while (current_cube->next != NULL)
    {
        current_cube = current_cube->next;
    }

    // add new cube at the end of the snake
    add->row = current_cube->row;
    add->col = current_cube->col;               
    add->next = NULL;

    current_cube->next = add;

}


// snake movement and collision
void move() 
{
    signed int addX, addY;
    unsigned int fill=BODY, preR, preC, tempR, tempC;
    Cube* temp = snake.head -> next;

    preR = snake.head->row;
    preC = snake.head->col;

    board[snake.head->row][snake.head->col] = NULL;



    switch (snake.direction)
    {
    case UP: snake.head->row -= STEP; break;
    case DOWN: snake.head->row += STEP; break;
    case RIGHT: snake.head->col += STEP; break;
    case LEFT: snake.head->col -= STEP; break;
    }

    if (board[snake.head->row][snake.head->col] == FOOD)
    {
        score += 1;
        generateFood();
        add_cube();
    }

    board[snake.head->row][snake.head->col] = HEAD;

    if (temp != NULL) {

        // update Cubes' places
        while (temp -> next != NULL)
        {
            tempR = temp->row;
            tempC = temp->col;

            temp->row = preR;
            temp->col = preC;
            board[temp->row][temp->col] = fill;

            preR = tempR;
            preC = tempC;

            if (snake.head->row == preR && snake.head->col == preC) { run = false; }


            temp = temp->next;
        }

        board[temp->row][temp->col] = NULL;
        if (snake.head->row == temp->row && snake.head->col == temp->col){ run = false; }

        temp->row = preR;
        temp->col = preC;
        board[temp->row][temp->col] = fill;
    }


    // check collision
    if (snake.head->row < 1 || snake.head->row >= HEIGHT - 1 || snake.head->col < 1 || snake.head->col > WIDTH - 2) { run = false; }
}

// update snake direction by keyboard
void keyboardControl() 
{
    char key;
    if (_kbhit()) 
    {
        key = _getch();
        switch (key)
        {
        case UP: snake.direction = UP; break;
        case DOWN: snake.direction = DOWN; break;
        case LEFT: snake.direction = LEFT; break;
        case RIGHT: snake.direction = RIGHT; break;
        }
    }
}


void generateFood() 
{
    board[rand() % (HEIGHT-2)+1][rand() % (WIDTH-2)+1] = FOOD;
}

int main()
{
    srand(time(NULL));

    initialize_board();
    initialize_snake();
    add_snake_to_board();
    generateFood();
    draw_board();



    while (run)
    {
        system("cls");
        printf("SNAKE GAME - BY NADAV SHANI\n\n");
        printf("SCORE:%d    (%d, %d)\n", score, snake.head->row, snake.head->col);
        keyboardControl();
        move();
        draw_board();
        delay(10000000);
    }
    
    printf("FINISHED! PRESS ANY KEY TO EXIT");
    return 0;
}
