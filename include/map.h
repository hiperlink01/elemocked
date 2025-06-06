#ifndef MAP_H
#define MAP_H

typedef struct map MAP;
typedef struct block Block;
typedef struct object Object;

typedef struct position {
    int i, j;
} Position;

void Map_Load(MAP* map, char select);
void Map_Start(MAP* map);

#endif