#ifndef HERO_H
#define HERO_H

typedef struct hero Hero;
typedef struct pochete Pochete; //weapons is hardcoded to Object arr of 5

Hero* Hero_Load(Gui* GUI);
void Hero_Unload(Hero* hero);

void Hero_Move(Hero* hero, player_action movement);
void Hero_Attack(Hero* hero);
void Hero_Drink_Potion(Hero* hero);
void Hero_Open_Chest(Hero* hero, bool* failure);
void Hero_Change_Weapon(Hero* hero);

bool Hero_Has_Treasure(Hero* hero);

#endif