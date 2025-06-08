#ifndef GAME_H
#define GAME_H

typedef struct game Game; //must store game time (INCLUDE TIME LIB)

typedef enum {
    MAP_A,
    MAP_B
} game_map_select;

Game* Game_Init(game_map_select game_map);
void Game_Finish(Game* game);

#endif