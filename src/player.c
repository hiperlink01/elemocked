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

//for player struct

typedef struct player {
    char* name;
    int timer;  
} Player;

//alloccers

Player* Player_Alloc(){

    Player* new = (Player*)malloc(sizeof(Player));
    return new;

}
void Player_Free(Player* player)
{ free(player); }

//setters

void Player_Set_Name(Player* player, char* name)
{ player->name = name; }
void Player_Set_Game_Time(Player* player, int timer)
{ player->timer = timer; }

//getters

char* Player_Get_Name(Player* player)
{ return player->name; }
int Player_Get_Game_Time(Player* player)
{ return player->timer; }