#ifndef HERO_H
#define HERO_H

typedef struct hero Hero;
typedef struct pochete Pochete; //weapons is hardcoded to Object arr of 5

Hero* Hero_Load();
void Hero_Unload(Hero* hero);

void Hero_Move(Hero* hero);
void Hero_Attack(Hero* hero);
void Hero_Change_Stat(Hero* hero);
void Hero_Open_Chest(Hero* hero);
void Hero_Switch_Weapon(Hero* hero);

#endif