#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/ranking.h"
#include "../../include/player.h"
#include "../../include/game.h"

#include "../../include/ingame/hud.h"
#include "../../include/ingame/map.h"
#include "../../include/ingame/hero.h"
#include "../../include/ingame/block.h"
#include "../../include/ingame/object.h"
#include "../../include/ingame/coordinates.h"

typedef struct block {
    block_type type;
    Coordinates position;
    Object* object;
} Block;

Block* Block_Create(block_type block_type);

void Block_Destroy(Block* block);

void Block_Chest_Open(Block* block);

void Block_Obstacle_Destroy(Block* obstacle, Object* used_weapon);