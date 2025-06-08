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

typedef struct hero {
    char* name;
    int health;
    Fanny_Pack* magical_waist_bag;
    Coordinates position;
} Hero;

typedef struct POCHETE {
    Object * weapons[5];
    Object* * potions;
} Fanny_Pack;