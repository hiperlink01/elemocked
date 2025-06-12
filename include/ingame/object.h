#ifndef OBJECT_H
#define OBJECT_H
//for Object struct

typedef enum {
    BOMB, POTION,
    
    WEAPON_STEEL,
    WEAPON_AIR, WEAPON_EARTH,
    WEAPON_FIRE, WEAPON_WATER
} object_type, weapon_type;

typedef struct object Object;

//allocators

Object* Object_Alloc();
void Object_Free(Object * object);

//setters

void Object_Set_Type(Object* object, object_type type);
void Object_Set_Name(Object* object, char* name);
void Object_Set_Stats(Object* object, int stats);

//getters

object_type Object_Get_Type(Object* object);
char* Object_Get_Name(Object* object);
int Object_Get_Stats(Object* object);

//actions

void Object_Rand_Draw(Object * object);

#endif