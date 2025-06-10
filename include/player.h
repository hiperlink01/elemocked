#ifndef PLAYER_H
#define PLAYER_H

typedef struct player Player; //name has 10 characters

typedef enum {

    MOVE_UP = 'W', 
    MOVE_LEFT = 'A',
    MOVE_DOWN = 'S',
    MOVE_RIGHT = 'D',

    OPEN_CHEST = 'E',

    ATTACK = 'K',
    CHANGE_WEAPON = 'O',
    DRINK_POTION = 'P'
    
} player_action;

Player * Player_Start(Gui* GUI);
void Player_Quit(Player * player);



#endif