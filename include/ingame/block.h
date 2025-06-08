#ifndef BLOCK_H
#define BLOCK_H

#include "object.h"

typedef struct block Block;

typedef enum {
    EMPTY,
    CHEST,
    ROCK,
    WALL,
    
    LOCK_AIR, LOCK_EARTH,
    LOCK_FIRE, LOCK_WATER
} block_type;

Block* Block_Load(block_type block_type);
void Block_Unload(Block* block);

void Block_Chest_Open(Block* block);

void Block_Obstacle_Destroy(Block* obstacle, Object* used_weapon);

#endif