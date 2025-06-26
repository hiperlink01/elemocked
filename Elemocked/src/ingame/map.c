#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../../include/utils.h"
#include "../../include/bool.h"

#include "../../include/ingame/map.h"
#include "../../include/ingame/coordinates.h"
#include "../../include/ingame/hero.h"

//for Object struct

typedef struct object {
    object_type type;
    char* name;
    int stats;
} Object;

//alloccers

Object* Object_Alloc(){
    Object* new = (Object*)malloc(sizeof(Object));
    new->type = 0;
    new->name = (char*)malloc(sizeof(char)*32);
    new->stats = 0;
    return new;
};

void Object_Free(Object * object);

//setters

void Object_Set_Type(Object* object, object_type type)
{ object->type = type; };
void Object_Set_Name(Object* object, char* name)
{ strcpy(object->name, name); };
void Object_Set_Stats(Object* object, int stats)
{ object->stats = stats; };

//getters

object_type Object_Get_Type(Object* object);
char* Object_Get_Name(Object* object)
{ return object->name; };
int Object_Get_Stats(Object* object);

/////////////////////////////////////////////////////////////////////////////////

//for Block struct

typedef struct block {
    block_type type;
    Object* object;
} Block;

//alloccers

Block** Block_Matrix_Alloc(int height, int width){

    Block** block_matrix = (Block**)(malloc(sizeof(Block*)*height));

    for (int i = 0; i < height; i++){
        block_matrix[i] = (Block*)malloc(sizeof(Block)*width);
    }

    return block_matrix;

}

void Block_Free(Block* block);

//setters

void Block_Set_Type(Block* block, block_type type);
void Block_Set_Position(Block* block, Coordinates position);
void Block_Set_Object(Block* block, Object* object);

//getters

block_type Block_Get_Type(Block* block){ return block->type; };
Coordinates Block_Get_Position(Block* block);
Object * Block_Get_Object(Block* block);

/////////////////////////////////////////////////////////////////////////////////

//for Map struct

typedef struct map {
    Dimensions dimensions;
    char** graphical;
    Block** functional;
} Map;

//ALLOCCERS

Map* Map_Alloc(){ 
    
    Map* new = (Map*)malloc(sizeof(Map));

    return new;

}

void Map_Free(Map* map) { };

//END OF ALLOCCERS

//LOADERS

//--helper functions for the loaders--

    int Map_Count_Chest(Map* map){

        int chest_count = 0;
        for (int i = 0; i<map->dimensions.height; i++){
            
            chest_count += strcnt(map->graphical[i], '?');

        }

        return chest_count;

    }

    object_type* Generate_Rand_Chest_Objects_Arr(int chest_count){

        int chest_count_aux = chest_count;

        object_type* objects_arr = (object_type*)malloc(sizeof(object_type)* chest_count);
        object_type aux[chest_count_aux];

        aux[0] = WEAPON_AIR; aux[1] = WEAPON_EARTH;
        aux[2] = WEAPON_FIRE; aux[3] = WEAPON_WATER;

        for (int i = 4; i<chest_count_aux; i++){
            
            int rand_select = rand() % 2;
            
            if (rand_select == 1) { aux[i] = POTION; }
            if (rand_select == 0) { aux[i] = BOMB; }

        }

        for (int i = 0; i < chest_count; i++){

            int rand_index = rand() % chest_count_aux;
            
            objects_arr[i] = aux[rand_index];

            for (int j=rand_index; j<chest_count_aux; j++){

                if (j == chest_count_aux - 1) { aux[j] = EMPTY; }
                else { aux[j] = aux[j+1]; }

            }

            chest_count_aux--;

        }

        return objects_arr;

    }

//--end of helper functions for the loaders--

void Map_Load_Dimensions(Map* map, map_select selected_map){
    
    FILE* f_map;

    if(selected_map == A)
    { f_map = fopen("../../assets/maps/map_a.txt", "r"); }
    if(selected_map == B)
    { f_map = fopen("../../assets/maps/map_b.txt", "r"); }
      
    int width = 0, height = 0;

    char buff[64];

    fgets(buff, sizeof(buff), f_map);
    width = strlen(buff);

    fseek(f_map, 0, SEEK_SET);

    while(fgets(buff, sizeof(buff), f_map))
    { height++; }

    fclose(f_map);

    map->dimensions.width = width;
    map->dimensions.height = height;

}

void Map_Load_Graphical(Map* map, map_select game_map){

    map->graphical = (char**)malloc(sizeof(char*)* (map->dimensions.height));

    for (int i = 0; i < map->dimensions.height; i++){
        map->graphical[i] = (char*)malloc(sizeof(char) * (map->dimensions.width));
    }

    FILE* f_map;

    if(game_map == A)
    { f_map = fopen("../../assets/maps/map_a.txt", "r"); }
    if(game_map == B)
    { f_map = fopen("../../assets/maps/map_b.txt", "r"); }

    for (int i = 0; i < map->dimensions.height; i++){

        fgets(map->graphical[i], map->dimensions.width + 1, f_map);
        
        char* check_new_line = strchr(map->graphical[i], '\n');

        if(check_new_line != NULL){ *check_new_line = '\0';}
        
    }

    for (int i = 0; i<map->dimensions.height; i++){
        for (int j = 0; j < map->dimensions.width; j++) {

            printf("%c", map->graphical[i][j]);
            if (map->graphical[i][j] == '\0'){ printf("\n"); }
        
        }

    }
    
    fclose(f_map);

}

void Map_Load_Functional(Map* map, Hero* hero){

    int chest_count = Map_Count_Chest(map);
    object_type* objects_arr = Generate_Rand_Chest_Objects_Arr(chest_count);

    map->functional = Block_Matrix_Alloc(map->dimensions.height, map->dimensions.width);

    for (int i = 0; i < map->dimensions.height; i++){
        for (int j = 0; j < map->dimensions.width; j++){

            switch (map->graphical[i][j]) {

            case EMPTY:
                map->functional[i][j].type = EMPTY;
                map->functional[i][j].object = NULL;
                break;

            case CHEST:
                map->functional[i][j].type = CHEST;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, objects_arr[chest_count-1]);

                switch (map->functional[i][j].object->type) {
                case BOMB:
                    Object_Set_Name(map->functional[i][j].object, "BOMB\0");
                    int rand_stats_bomb = -(1 + (rand()%4)); //random value from -1 to -4
                    Object_Set_Stats(map->functional[i][j].object, rand_stats_bomb);
                    break;

                case POTION:
                    Object_Set_Name(map->functional[i][j].object, "POTION\0");
                    int rand_stats_potion = 1 + (rand()%3); //random value from 1 to 3
                    Object_Set_Stats(map->functional[i][j].object, rand_stats_potion);
                    break;

                case WEAPON_AIR:
                    Object_Set_Name(map->functional[i][j].object, "AIR WHIP\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_EARTH:
                    Object_Set_Name(map->functional[i][j].object, "EARTH GAUNTLETS\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_FIRE:
                    Object_Set_Name(map->functional[i][j].object, "FIRE SPEAR\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_WATER:
                    Object_Set_Name(map->functional[i][j].object, "WATER SWORD\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                default:
                    break;
                }

                chest_count--;

                break;

            case ROCK:
                map->functional[i][j].type = ROCK;
                map->functional[i][j].object = NULL;                
                break;

            case WALL:
                map->functional[i][j].type = WALL;
                map->functional[i][j].object = NULL;                
                break;

            case HERO:
                Coordinates hero_coordinates;
                hero_coordinates.x = j;
                hero_coordinates.y = i;
                Hero_Set_Position(hero, hero_coordinates);
                break;

            case LOCK_AIR:
                map->functional[i][j].type = LOCK_AIR;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_AIR);
                Object_Set_Name(map->functional[i][j].object, NULL);
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_EARTH:
                map->functional[i][j].type = LOCK_EARTH;             
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_EARTH);
                Object_Set_Name(map->functional[i][j].object, NULL);
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_FIRE:
                map->functional[i][j].type = LOCK_FIRE;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_FIRE);
                Object_Set_Name(map->functional[i][j].object, NULL);
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_WATER:
                map->functional[i][j].type = LOCK_WATER;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_WATER);
                Object_Set_Name(map->functional[i][j].object, NULL);
                Object_Set_Stats(map->functional[i][j].object, 0);          
                break;

            case TREASURE:
                map->functional[i][j].type = TREASURE;
                map->functional[i][j].object = NULL;                
                break;

            default:
                break;
            }
        }
    }

    free(objects_arr);

}

void Map_Load(Map* map, map_select selected_map, Hero* hero){

    Map_Load_Dimensions(map, selected_map);
    Map_Load_Graphical(map, selected_map);
    Map_Load_Functional(map, hero);

}

//END OF LOADERS

//getter

Block* Map_Get_Block(Map* map, int x, int y)
{ return &(map->functional[y][x]); }

//actions

void Map_Print(Map* map){

    for (int i = 0; i<map->dimensions.height; i++)
    { printf("%s\n", map->graphical[i]); }

}

void Map_Update_Graphical(Map* map, Hero* hero){

    for (int i=0; i<map->dimensions.height; i++){
        for (int j=0; j<map->dimensions.width; j++){

            switch (map->functional[i][j].type) {

            case EMPTY:
                map->graphical[i][j] = ' ';
                break;

            case CHEST:
                if (map->functional[i][j].object == NULL)
                {map->graphical[i][j] = 'o';}
                else {map->graphical[i][j] = '?';}
                break;

            case ROCK:
                map->graphical[i][j] = '@';
                break;

            case WALL:
                map->graphical[i][j] = '=';
                break;

            case LOCK_AIR:
                map->graphical[i][j] = 'A';
                break;

            case LOCK_EARTH:
                map->graphical[i][j] = 'E';
                break;

            case LOCK_FIRE:
                map->graphical[i][j] = 'F';
                break;

            case LOCK_WATER:
                map->graphical[i][j] = 'W';
                break;

            case TREASURE:
                map->graphical[i][j] = '+';
                break;

            default:
                break;
            }

        }
    }
}

/*
//SETTERS

void Map_Set_Dimensions(Map* map, Dimensions dimensions)
{ map->dimensions = dimensions; }
void Map_Set_Graphical(Map* map, char** graphical)
{ map->graphical = graphical; }
void Map_Set_Functional(Map* map, Block** functional)
{ map->functional = functional; }

//getters

Dimensions Map_Get_Dimenstions(Map* map)
{ return map->dimensions; }
char** Map_Get_Graphical(Map* map)
{ return map->graphical; }
Block** Map_Get_Functional(Map* map)
{ return map->functional; }

*/