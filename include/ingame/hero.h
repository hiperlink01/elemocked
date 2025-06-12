#ifndef HERO_H
#define HERO_H

#include "coordinates.h"
#include "map.h"
#include "object.h"

//for Bag struct

typedef struct POCHETE Bag; //weapons is hardcoded to Object arr of 5

Bag* Bag_Alloc();
void Bag_Free();

//setters

void Bag_Set_Weapons(Bag* bag, Object* * weapons);
void Bag_Set_Potions(Bag* bag, Object* * potions);
void Bag_Set_Treasure(Bag* bag, bool has_treasure);

// getters

Object* * Bag_Get_Weapons(Bag* bag);
Object* * Bag_Get_Potions(Bag* bag);
bool Bag_Get_Treasure(Bag* bag);

//

//for hero struct

typedef enum {

    MOVE_UP = 'W', 
    MOVE_LEFT = 'A',
    MOVE_DOWN = 'S',
    MOVE_RIGHT = 'D',

    OPEN_CHEST = 'E',

    ATTACK = 'K',
    CHANGE_WEAPON = 'O',
    DRINK_POTION = 'P'
    
} hero_action;

typedef struct hero Hero;

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
void Hero_Open_Chest(Hero* hero, Map* map, bool* failure);
void Hero_Change_Weapon(Hero* hero);

//check

bool Hero_Has_Treasure(Hero* hero);

#endif