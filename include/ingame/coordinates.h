#ifndef POSITION_H
#define POSITION_H

typedef struct coordinates {
    int i, j;
} Coordinates, Dimensions;

typedef enum {
    UP = 'W',
    LEFT = 'A',
    DOWN = 'S',
    RIGHT = 'D'
} movement;

#endif