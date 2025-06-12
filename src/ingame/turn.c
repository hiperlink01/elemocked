#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/utils.h"
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

bool New_Turn(Hero* hero, Map* map) {

    //Gui_Print();

    //print map, print stats

    bool failure = FALSE;

    printf("[H] for help\n\n>>");
    hero_action current_action = fgetc(stdin); clear_input_stream();

    switch (current_action){

        case MOVE_UP: case MOVE_LEFT:
        case MOVE_DOWN: case MOVE_RIGHT:
            Hero_Move(hero, map, current_action);
            // check if there is rock, lock or wall in direction
            // move to direction
            // update hero_position
            // update map
            break;
        
        case ATTACK:
            Hero_Attack(hero, map);
            // check if there are rocks or locks on surroundings
            // rocks turn into empty
            // to any lock found, check corresponding weapon, turn into empty
            // update map (RAEFW to ' ')
            break;

        case OPEN_CHEST:
            Hero_Open_Chest(hero, map, &failure);
            // check if current position is chest,
            // check object,
            // make action (decrease health or store potion),
            // destroy object in block, null object pointer
            // update map (C turns to c)
            break;

        case DRINK_POTION:
            Hero_Drink_Potion(hero);
            //shows available potions,
            // prompts for choice,
            // checks if it's valid,
            // increases health,
            // destroys potion from bag 
            break;
        
        case CHANGE_WEAPON:
            Hero_Change_Weapon(hero);
            //shows available weapons,
            // asks prompts for choice,
            // checks if it's valid,
            // sets current_weapon 
            break;

        default:
            printf("\nInvalid entry.\n");
    }

    return;

}