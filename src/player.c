#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/bool.h"
#include "../include/gui.h"
#include "../include/ranking.h"
#include "../include/player.h"
#include "../include/game.h"

#include "../include/ingame/turn.h"
#include "../include/ingame/map.h"
#include "../include/ingame/hero.h"
#include "../include/ingame/block.h"
#include "../include/ingame/object.h"
#include "../include/ingame/coordinates.h"

typedef struct player {
    char name[10];
    int game_time;
} Player;