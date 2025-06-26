#ifndef PLAYER_H
#define PLAYER_H

//for Player struct

typedef struct player Player; //name has 10 characters

//alloccers

Player* Player_Alloc();
void Player_Free(Player* player);

//setters

void Player_Set_Name(Player* player, char* name);
void Player_Set_Timer(Player* player, int timer);

//for game_time value

char* Player_Get_Name(Player* player);
int Player_Get_Timer(Player* player);

#endif