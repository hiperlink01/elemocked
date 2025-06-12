#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/bool.h"
 
#include "../../include/ranking.h"
#include "../../include/player.h"
#include "../../include/game.h"

#include "../../include/ingame/turn.h"
#include "../../include/ingame/map.h"
#include "../../include/ingame/hero.h"
#include "../../include/ingame/block.h"
#include "../../include/ingame/object.h"
#include "../../include/ingame/coordinates.h"

//for Block struct

typedef struct block {
    block_type type;
    Coordinates position;
    Object* object;
} Block;

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