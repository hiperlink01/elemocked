#ifndef MAP_H
#define MAP_H

#include "coordinates.h"

typedef struct hero Hero;

//for Object struct

typedef enum {
    BOMB, POTION,
    
    WEAPON_STEEL,
    WEAPON_AIR, WEAPON_EARTH,
    WEAPON_FIRE, WEAPON_WATER
} object_type, weapon_type;

typedef struct object Object;

//allocators

Object* Object_Alloc();
void Object_Free(Object * object);

//setters

void Object_Set_Type(Object* object, object_type type);
void Object_Set_Name(Object* object, char* name);
void Object_Set_Stats(Object* object, int stats);

//getters

object_type Object_Get_Type(Object* object);
char* Object_Get_Name(Object* object);
int Object_Get_Stats(Object* object);

/////////////////////////////////////////////////////////////////////////////////

//for Block struct

typedef enum {
    EMPTY = ' ',
    CHEST = '?',
    ROCK = '@',
    WALL = '=',

    HERO = 'k',
    
    LOCK_AIR = 'A', LOCK_EARTH = 'E',
    LOCK_FIRE = 'F', LOCK_WATER = 'W',

    TREASURE = '+'
} block_type;

typedef struct block Block;

//alloccers

Block** Block_Matrix_Alloc(int height, int width);
void Block_Free(Block* block);

//setters

void Block_Set_Type(Block* block, block_type type);
void Block_Set_Position(Block* block, Coordinates position);
void Block_Set_Object(Block* block, Object* object);

//getters

block_type Block_Get_Type(Block* block);
Coordinates Block_Get_Position(Block* block);
Object * Block_Get_Object(Block* block);

/////////////////////////////////////////////////////////////////////////////////

//for Map struct

typedef enum {

    A, B,

    map_qtt
} map_select;

typedef struct map Map;

//alloccers

Map* Map_Alloc();
void Map_Free(Map* map);

//loader
void Map_Load(Map* map, map_select selected_map, Hero* hero);

//getters

Block* Map_Get_Block(Map* map, int x, int y);

//actions

void Map_Print(Map* map);
void Map_Update_Graphical(Map* map, Hero* hero);

/*
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
*/

#endif