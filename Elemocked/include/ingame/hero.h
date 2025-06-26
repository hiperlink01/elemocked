#ifndef HERO_H
#define HERO_H

#include "coordinates.h"

typedef struct object Object;
typedef struct map Map;
typedef enum bool;
typedef enum weapon_type;

//for Bag struct

typedef struct POCHETE Bag;

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

//for hero struct

typedef enum {

    MOVE_UP = 'W', 
    MOVE_LEFT = 'A',
    MOVE_DOWN = 'S',
    MOVE_RIGHT = 'D',

    OPEN_CHEST = 'E',

    ATTACK = 'K',
    CHANGE_WEAPON = 'O'
    
} hero_action;

typedef struct hero Hero;

//alloccers 

Hero* Hero_Alloc();
void Hero_Free(Hero* hero);

//loader
void Hero_Load(Hero* hero);

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
void Hero_Open_Chest(Hero* hero, Map* map);
void Hero_Change_Weapon(Hero* hero);
void Hero_Drink_Potion(Hero* her, hero_action current_action);
void Hero_Print(Hero* hero);

//check

bool Hero_Has_Treasure(Hero* hero);

#endif