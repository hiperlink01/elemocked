#ifndef BLOCK_H
#define BLOCK_H

#include "coordinates.h"
#include "object.h"

//for Block struct

typedef enum {
    EMPTY,
    CHEST,
    ROCK,
    WALL,
    
    LOCK_AIR, LOCK_EARTH,
    LOCK_FIRE, LOCK_WATER
} block_type;

typedef struct block Block;

//alloccers

Block* Block_Alloc();
void Block_Free(Block* block);

//setters

void Block_Set_Type(Block* block, block_type type);
void Block_Set_Position(Block* block, Coordinates position);
void Block_Set_Object(Block* block, Object* object);

//getters

block_type Block_Get_Type(Block* block);
Coordinates Block_Get_Position(Block* block);
Object * Block_Get_Object(Block* block);

//actions

void Block_Chest_Open(Block* block);

void Block_Obstacle_Destroy(Block* obstacle, Object* used_weapon);
#endif