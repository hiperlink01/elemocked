#include "../include/hero.h"
#include "../include/map.h"

typedef struct hero {
    char* name;
    int health;
    Pochete magical_bag;
    Position current_position;
} HERO;

typedef struct pochete {
    Object* weapons;
    Object* potions;
} Pochete;