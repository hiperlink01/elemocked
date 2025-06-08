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

typedef struct map {
    Dimensions size;
    char** graphical;
    Block** * functional;
    Coordinates position_of_hero;
} Map;

Map* Map_Load(Game* game);