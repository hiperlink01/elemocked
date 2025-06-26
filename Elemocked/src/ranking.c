#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/bool.h"
#include "../include/ranking.h"
#include "../include/player.h"


#include "../include/ingame/turn.h"
#include "../include/ingame/map.h"
#include "../include/ingame/hero.h"
#include "../include/ingame/coordinates.h"

//for Ranking struct

typedef struct ranking {
    Player* * top_players;
} Ranking;

//alloccers

Ranking* Ranking_Alloc(){
    Ranking* ranking = (Ranking*)malloc(sizeof(Ranking));
    return ranking;
}

void Ranking_Free(Ranking* ranking)
{ free(ranking); }

//setters

void Ranking_Set_Top_Players(Ranking* ranking, Player* * top_players)
{ ranking->top_players = top_players; }

//getters

Player** Ranking_Get_Top_Players(Ranking* ranking)
{ return ranking->top_players; }

//actions

void Ranking_Update_File();