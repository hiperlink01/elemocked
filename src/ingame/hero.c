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

//for Bag struct

typedef struct POCHETE {
    Object* * weapons;
    Object* * potions;
    bool has_treasure;
} Bag;

//alloccers

Bag* Bag_Alloc(){
    Bag* new = (Bag*)malloc(sizeof(Bag));
    return new;
}
void Bag_Free(){}

//setters

void Bag_Set_Weapons(Bag* bag, Object* * weapons);
void Bag_Set_Potions(Bag* bag, Object* * potions);
void Bag_Set_Treasure(Bag* bag, bool has_treasure);

//getters

Object* * Bag_Get_Weapons(Bag* bag);
Object* * Bag_Get_Potions(Bag* bag);
bool Bag_Get_Treasure(Bag* bag);

//for Hero struct

typedef struct hero {
    char* name;
    int health;
    weapon_type current_weapon;
    Bag* magical_waist_bag;
    Coordinates position;
} Hero;

//alloccers

Hero* Hero_Alloc();
void Hero_Free(Hero* hero);

//setters

void Hero_Set_Name(Hero* hero, char* name);
void Hero_Set_Health(Hero* hero, int health);
void Hero_Set_Current_Weapon(Hero* hero, weapon_type weapon);
void Hero_Set_Magical_Waist_Bag(Hero* hero, Bag* magical_Waist_bag);
void Hero_Set_Position(Hero* hero, Coordinates position);

//getters

char* Hero_Get_Name(Hero* hero);
int Hero_Get_Health(Hero* hero);
weapon_type Hero_Get_Current_Weapon(Hero* hero);
Bag* Hero_Get_Magical_Waist_Bag(Hero* hero);
Coordinates Hero_Get_Position(Hero* hero);

//actions

void Hero_Move(Hero* hero, Map* map, hero_action movement);
void Hero_Attack(Hero* hero, Map* map);
void Hero_Drink_Potion(Hero* hero);
void Hero_Open_Chest(Hero* hero, Map* map);
void Hero_Change_Weapon(Hero* hero);

//check

bool Hero_Has_Treasure(Hero* hero);