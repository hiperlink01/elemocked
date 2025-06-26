#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/utils.h"
#include "../../include/bool.h"

#include "../../include/ingame/turn.h"
#include "../../include/ingame/map.h"
#include "../../include/ingame/hero.h"

bool New_Turn(Hero* hero, Map* map) {

    bool failure = FALSE;

    Map_Print(map);
    Hero_Print(hero);

    printf("[H] for help\n\n>>");
    hero_action current_action = fgetc(stdin); Clear_Input_Stream();

    switch (current_action){

        case MOVE_UP: case MOVE_LEFT:
        case MOVE_DOWN: case MOVE_RIGHT:
            Hero_Move(hero, map, current_action);
            // update map
            break;
        
        case ATTACK:
            Hero_Attack(hero, map);
            // update map (@AEFW to ' ')
            break;

        case OPEN_CHEST:
            Hero_Open_Chest(hero, map);
            // update map (? to o)
            break;
        
        case CHANGE_WEAPON:
            Hero_Change_Weapon(hero);
            break;

        default:
            if( (current_action >= '0' AND current_action <= '9') )
            { Hero_Drink_Potion(hero, current_action); }
            else { printf("\nInvalid entry.\n"); }
    }

    Map_Update_Graphical(map, hero);

    if (Hero_Get_Health(hero) <= 0) { failure = TRUE; }

    return failure;

}