#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Cube Cube;

// Cube
typedef struct Cube
{
    unsigned int col;
    unsigned int row;
    Cube* next;
} Cube;

// Snake
typedef struct Snake
{
    Cube* head;
    char direction; // u/d/l/r
}Snake;

#endif // STRUCTS_H

