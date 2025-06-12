#ifndef GAME_H
#define GAME_H

#include "player.h"

//for Game struct

typedef enum {
    A,
    B,
    map_qtt
} game_map_select;

typedef struct game Game; //must store game time (INCLUDE TIME LIB)

//alloccers

Game* Game_Alloc();
void Game_Free(Game* game);

//setters

void Game_Set_Player(Game* game, Player* player);
void Game_Set_Map(Game* game, game_map_select game_map);

//getters

Player* Game_Get_Player(Game* game);
game_map_select Game_Get_Map(Game* game);

// game_map_select Game_Get_Map(Game* new_game);

#endif