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

//for Map struct

typedef struct map {
    Dimensions dimensions;
    char** graphical;
    Block** * functional;
    Coordinates hero_position;
} Map;

//alloccers

Map* Map_Alloc(){ 
    
    Map* new = (Map*)malloc(sizeof(Map));

    return new;

}

void Map_Free(Map* map) { };

Load_Map(Map* map, game_map_select game_map){

    FILE* f_map;

    if(game_map = A)
    { f_map = fopen("../../assets/maps/map_b.txt", "r"); }
    if(game_map = B)
    { f_map = fopen("../../assets/maps/map_b.txt", "r"); }
      
    int width = 0, height = 0;

    while (fgetc(f_map) != '\n' && !(feof(f_map)))
    { width++; }

    fseek(f_map, 0, SEEK_SET);

    char* buff = (char*)malloc(sizeof(char)*width+1);

    while(fgets(buff, width+2, f_map))
    { height++; }

    fclose(f_map);

    map->dimensions.height = height;
    map->dimensions.width = width;

}

//setters

void Map_Set_Dimensions(Map* map, Dimensions dimensions)
{ map->dimensions = dimensions; }
void Map_Set_Graphical(Map* map, char** graphical)
{ map->graphical = graphical; }
void Map_Set_Functional(Map* map, Block** * functional)
{ map->functional = functional; }
void Map_Set_Hero_Position(Map* map, Coordinates hero_position)
{ map->hero_position = hero_position; }

//getters

Dimensions Map_Get_Dimenstions(Map* map)
{ return map->dimensions; }
char** Map_Get_Graphical(Map* map)
{ return map->graphical; }
Block** * Map_Get_Functional(Map* map)
{ return map->functional; }
Coordinates Map_Get_Hero_Position(Map* map)
{ return map->hero_position; }

//actions

void Map_Print(Map* map);