#ifndef RANKING_H
#define RANKING_H

#include "player.h"

//for Ranking struct

typedef struct ranking Ranking;

//alloccers

Ranking* Ranking_Alloc();
void Ranking_Free();

//setters

void Ranking_Set_Top_Players(Ranking* ranking);

//getters

Player** Ranking_Get_Top_Players();

//actions

void Ranking_Update_File();

#endif