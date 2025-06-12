#ifndef MAP_H
#define MAP_H

#include "coordinates.h"
#include "block.h"

//for Map struct

typedef struct map Map;

//alloccers

Map* Map_Alloc();
void Map_Free(Map* map);

//to set dimensions, I need to load lines & colls of maps
//

//setters

void Map_Set_Dimensions(Map* map, Dimensions dimensions);
void Map_Set_Graphical(Map* map, char** graphical);
void Map_Set_Functional(Map* map, Block** * functional);
void Map_Set_Hero_Position(Map* map, Coordinates hero_position);

//getters

Dimensions Map_Get_Dimenstions(Map*);
char** Map_Get_Graphical(Map*);
Block** * Map_Get_Functional(Map*);
Coordinates Map_Get_Hero_Position(Map*);

//actions

void Map_Print(Map* map);

#endif