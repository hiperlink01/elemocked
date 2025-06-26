#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/bool.h"
 
#include "../../include/ranking.h"
#include "../../include/player.h"

#include "../../include/ingame/turn.h"
#include "../../include/ingame/map.h"
#include "../../include/ingame/hero.h"
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

    new->has_treasure = FALSE;

    new->potions = (Object**)malloc(sizeof(Object*)*10);
    for (int i=0; i<10; i++) { new->potions[i] = NULL; }

    new->weapons = (Object**)malloc(sizeof(Object*)*5);

    new->weapons[0] = Object_Alloc(); //allocating the steel knife
    Object_Set_Type(new->weapons[0], WEAPON_STEEL);
    Object_Set_Name(new->weapons[0], "STEEL KNIFE");
    Object_Set_Stats(new->weapons[0], 0);

    for (int i=1; i<5; i++){ new->weapons[i] = NULL; }
    
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

Hero* Hero_Alloc(){

    Hero* new = (Hero*)malloc(sizeof(Hero));
    new->magical_waist_bag = Bag_Alloc();
    new->name = (char*)malloc(sizeof(char)*9);
    strcpy(new->name, "Joaquim\0");
    new->health = 10;
    new->current_weapon = WEAPON_STEEL;
    new->magical_waist_bag = Bag_Alloc();
    //hero->position is set by Map_Load()

    return new;

};

void Hero_Free(Hero* hero);

//setters

void Hero_Set_Name(Hero* hero, char* name);
void Hero_Set_Health(Hero* hero, int health);
void Hero_Set_Current_Weapon(Hero* hero, weapon_type weapon);
void Hero_Set_Magical_Waist_Bag(Hero* hero, Bag* magical_Waist_bag);
void Hero_Set_Position(Hero* hero, Coordinates position)
{ hero->position = position; }

//getters

char* Hero_Get_Name(Hero* hero);
int Hero_Get_Health(Hero* hero);
weapon_type Hero_Get_Current_Weapon(Hero* hero);
Bag* Hero_Get_Magical_Waist_Bag(Hero* hero);
Coordinates Hero_Get_Position(Hero* hero);

//actions

void Hero_Move(Hero* hero, Map* map, hero_action movement){

    //get current position
    //check if next position is valid
    //move if it is
    //do nothing if it isnt

    block_type destination_block_type;
    
    switch (movement) {
    case MOVE_UP:

        destination_block_type = Block_Get_Type(Map_Get_Block(map, hero->position.x, (hero->position.y)+1));

        if(destination_block_type ISNT ROCK AND destination_block_type ISNT WALL)
        { hero->position.y++; }
        break;

    case MOVE_LEFT:
        
        destination_block_type = Block_Get_Type(Map_Get_Block(map, (hero->position.x)-1, hero->position.y));

        if(destination_block_type ISNT ROCK AND destination_block_type ISNT WALL)
        { hero->position.x--; }
        break;
        
    case MOVE_DOWN:

        destination_block_type = Block_Get_Type(Map_Get_Block(map, hero->position.x, (hero->position.y)-1));

        if(destination_block_type ISNT ROCK AND destination_block_type ISNT WALL)
        { hero->position.y--; }
        break;
        
    case MOVE_RIGHT:
        
        destination_block_type = Block_Get_Type(Map_Get_Block(map, (hero->position.x)+1, hero->position.y));

        if(destination_block_type ISNT ROCK AND destination_block_type ISNT WALL)
        { hero->position.x++; }
        break;

    default: break;
    }

}

void Hero_Attack(Hero* hero, Map* map){

    int c=0;
    int i=0, j=1;

    while(c<4){

        Block* block_to_check = Map_Get_Block(map, hero->position.x + j, hero->position.y + i);

        switch ( Block_Get_Type(block_to_check) )
        {
        case ROCK:
            Block_Set_Type(block_to_check, EMPTY);
            Block_Set_Object(block_to_check, NULL);
            break;
        case LOCK_AIR: case LOCK_EARTH:
        case LOCK_FIRE: case LOCK_WATER:
            if (
                Hero_Get_Current_Weapon(hero)
                IS 
                Object_Get_Type(
                    Block_Get_Object(block_to_check)
                ) //all 4 locks store the value corresponding to the weapons that break them;
            ){    //therefore, if the hero is wielding the weapon, values will match, blocks will be set to empty.
                Block_Set_Type(block_to_check, EMPTY);
                Block_Set_Object(block_to_check, NULL);
            }
            break;
        default:
            break;
        }

        j*=(-1); i*=(-1);

        if (c==1){ i=1; j=0; }

        c++;

    }
};

void Hero_Open_Chest(Hero* hero, Map* map){

    if (
        Block_Get_Type(
            Map_Get_Block(map, hero->position.x, hero->position.y)
        ) IS CHEST
        AND
        Block_Get_Object(
            Map_Get_Block(map, hero->position.x, hero->position.y)
        ) ISNT NULL
    ){

        Object* inside_chest = Block_Get_Object(Map_Get_Block(map, hero->position.x, hero->position.y));

        switch(Object_Get_Type(inside_chest)){

        case BOMB:
            hero->health += Object_Get_Stats(inside_chest);

        case POTION:
            for (int i = 0; i<10; i++){
                if (hero->magical_waist_bag->potions[i] == NULL)
                { hero->magical_waist_bag->potions[i] = inside_chest; break; }
            }
        
        case WEAPON_AIR: case WEAPON_EARTH:
        case WEAPON_FIRE: case WEAPON_WATER:
            for (int i = 0; i<5; i++){
                if (hero->magical_waist_bag->weapons[i] == NULL)
                { hero->magical_waist_bag->weapons[i] = inside_chest; break; }
            }
        }

        Block_Set_Object(Map_Get_Block(map, hero->position.x, hero->position.y), NULL);
    }
}

void Hero_Change_Weapon(Hero* hero){

    int i = 0;
    while ( Object_Get_Type(hero->magical_waist_bag->weapons[i]) ISNT hero->current_weapon ) 
    { i++; } //set index to the same weapon we have
    while ( hero->magical_waist_bag->weapons[i] IS NULL )
    { i++; if(i==5){i=0;} } //search next indexes for available weapons; when exceeds max index, returns to first

    hero->current_weapon = Object_Get_Type(hero->magical_waist_bag->weapons[i]);
    //sets current weapon to found available index

};

void Hero_Drink_Potion(Hero* hero, hero_action current_action){

    if (hero->magical_waist_bag->potions[current_action-'0'] ISNT NULL){
        
        hero->health += Object_Get_Stats(
            hero
            ->magical_waist_bag
            ->potions[current_action-'0']
        );

        hero->magical_waist_bag->potions[current_action-'0'] = NULL;

    }
}

//check

bool Hero_Has_Treasure(Hero* hero);

void Hero_Print(Hero* hero){

    int health;
    health = hero->health;

    char* current_weapon_name;
    for(int i = 0; i < 5; i++){
        if(hero->magical_waist_bag->weapons[i] ISNT NULL){
            if(Object_Get_Type(hero->magical_waist_bag->weapons[i]) == hero->current_weapon)
            { current_weapon_name = Object_Get_Name(hero->magical_waist_bag->weapons[i]); }
        }
    }

    printf("HEALTH: %d/10 | WEAPON: %s\n\n", health, current_weapon_name);

    Object* * potions;
    potions = hero->magical_waist_bag->potions;

    printf("POTIONS:\n");
    for (int i = 0; i<10; i++){

        if (potions[i] ISNT NULL){
            
            switch (Object_Get_Stats(potions[i])) {
            case 1:
                printf("|C|");
                break;
            case 2:
                printf("|B|");
                break;
            case 3:
                printf("|A|");
                break;
            
            default:
                break;
            }
        } else { printf("| |"); }
    } printf("\n");

    for (int i = 0; i<10; i++){
        if (i+1 == 10) { printf(" 0 "); } 
        else { printf(" %d ", i+1); }
    }

    printf("\n\n");

}