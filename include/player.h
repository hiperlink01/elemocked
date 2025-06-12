#ifndef PLAYER_H
#define PLAYER_H

//for Player struct

typedef struct player Player; //name has 10 characters

//alloccers

Player* Player_Alloc();
void Player_Free(Player* player);

//for name value

void Player_Set_Name(Player* player, char* name);
char* Player_Get_Name(Player* player);

//for game_time value

void Player_Set_Timer(Player* player, int timer);
int Player_Get_Timer(Player* player);

#endif