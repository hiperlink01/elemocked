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

typedef struct hero {
    char* name;
    int health;
    Fanny_Pack* magical_waist_bag;
    Coordinates position;
} Hero;

typedef struct POCHETE {
    Object * weapons[5];
    Object* * potions;
    bool has_treasure;
} Fanny_Pack;

Hero* Hero_Load(Gui* GUI);
void Hero_Unload(Hero* hero);

void Hero_Move(Hero* hero, player_action movement);
void Hero_Attack(Hero* hero);
void Hero_Drink_Potion(Hero* hero);
void Hero_Open_Chest(Hero* hero);
void Hero_Change_Weapon(Hero* hero);

bool Hero_Has_Treasure(Hero* hero);