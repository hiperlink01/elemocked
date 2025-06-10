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

bool New_Turn(Hero* hero, Map* map, Gui* GUI) {

    Gui_Print(GUI, HUD);

    bool failure = FALSE;

    player_action current_action = fgetc(stdin);

    switch (current_action){

        case MOVE_UP: case MOVE_LEFT:
        case MOVE_DOWN: case MOVE_RIGHT:
            Hero_Move(hero, current_action);
            break;
        
        case ATTACK:
            Hero_Attack(hero);
            break;

        case OPEN_CHEST:
            Hero_Open_Chest(hero, &failure);
            break;

        case DRINK_POTION:
            Hero_Drink_Potion(hero);
            break;
        
        case CHANGE_WEAPON:
            Hero_Change_Weapon(hero);
            break;

        default:
            printf("\nInvalid entry.\n");
    }

    return;

}