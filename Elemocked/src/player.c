#include <stdlib.h>
#include <string.h>

#include "../include/player.h"

//for player struct

typedef struct player {
    char* name;
    int timer;  
} Player;

//alloccers

Player* Player_Alloc(){

    Player* new = (Player*)malloc(sizeof(Player));
    new->name = (char*)malloc(sizeof(char)*11);
    new->timer = 0;

    return new;

}

void Player_Free(Player* player){ 
    free(player->name);
    free(player);
}

//setters

void Player_Set_Name(Player* player, char* name)
{ strcpy(player->name, name); }//player->name = name; }
void Player_Set_Game_Time(Player* player, int timer)
{ player->timer = timer; }

//getters

char* Player_Get_Name(Player* player)
{ return player->name; }
int Player_Get_Game_Time(Player* player)
{ return player->timer; }