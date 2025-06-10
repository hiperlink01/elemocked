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

typedef struct game {
    Player* player;
    game_map_select game_map;
} Game;

Game* Game_Init(Player* player, game_map_select game_map){

    Game* new_game = (Game*)malloc(sizeof(Game));

    new_game->player = player;
    new_game->game_map = game_map;

    return new_game;

}

game_map_select Game_Get_Map(Game* new_game)
{ return new_game->game_map; }