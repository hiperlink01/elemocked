#ifndef GAME_H
#define GAME_H

typedef struct game Game; //must store game time (INCLUDE TIME LIB)

typedef enum {
    MAP_A,
    MAP_B,
    map_qtt
} game_map_select;

Game* Game_Init();
void Game_Finish(Game* game);

game_map_select Game_Map_Select(Gui* GUI);

game_map_select Game_Get_Map(Game* new_game);

#endif