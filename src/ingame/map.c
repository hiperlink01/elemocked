#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>


#include "../../include/bool.h"
#include "../../include/gui.h"
#include "../../include/ranking.h"
#include "../../include/player.h"
#include "../../include/game.h"

#include "../../include/ingame/turn.h"
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

Map* Map_Load(game_map_select selected_map){

    if (selected_map == MAP_A){
        //fopen map a, do all the stuff, return pointer
    }
    if (selected_map == MAP_B){
        //fopen map a, do all the stuff, return pointer
    }

}

void Map_Unload(Map* map) {
    
    for (int i = 0; i < map->size.i; i++){
        free(map->graphical[i]);
    }
    free(map->graphical);

};

void Map_Dimension(Map* map);

char** Map_Alloc(Map* map);
void Map_Free(Map* map);

void Map_Fill(Map* map);

void Map_Update(Map* map);

void Map_Print(Map* map);