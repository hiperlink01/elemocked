#ifndef POSITION_H
#define POSITION_H

typedef struct coordinates {
    int x, y;
} Coordinates;

typedef struct dimensions {
    int width, height;
} Dimensions;

typedef enum {
    UP = 'W',
    LEFT = 'A',
    DOWN = 'S',
    RIGHT = 'D'
} movement;

#endif