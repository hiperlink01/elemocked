#ifndef OBJECT_H
#define OBJECT_H

typedef struct object Object;

typedef enum {
    POTION, BOMB,
    WEAPON_STEEL,
    WEAPON_AIR, WEAPON_EARTH,
    WEAPON_FIRE, WEAPON_WATER
} object_type;

Object* Object_Load(object_type type);
void Object_Unload(Object* object);

void Object_Rand_Draw(Object* object);

#endif