#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/bool.h"
#include "../include/ranking.h"
#include "../include/player.h"
#include "../include/game.h"

#include "../include/ingame/turn.h"
#include "../include/ingame/map.h"
#include "../include/ingame/hero.h"
#include "../include/ingame/block.h"
#include "../include/ingame/object.h"
#include "../include/ingame/coordinates.h"

//for Game struct

typedef struct game {
    Player* player;
    game_map_select game_map;
} Game;

//alloccers

Game* Game_Alloc(){
    Game* new_game = (Game*)malloc(sizeof(Game));
    return new_game;
}
void Game_Free();

//setters

void Game_Set_Player(Game* game, Player* player)
{ game->player = player; }
void Game_Set_Map(Game* game, game_map_select game_map)
{ game->game_map = game_map; }

//getters

Player* Game_Get_Player(Game* game)
{ return game->player; }
game_map_select Game_Get_Map(Game* game)
{ return game->game_map; }