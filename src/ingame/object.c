#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../../include/bool.h"
 
#include "../../include/ranking.h"
#include "../../include/player.h"
#include "../../include/game.h"

#include "../../include/ingame/turn.h"
#include "../../include/ingame/map.h"
#include "../../include/ingame/hero.h"
#include "../../include/ingame/block.h"
#include "../../include/ingame/object.h"
#include "../../include/ingame/coordinates.h"

//for Object struct

typedef struct object {
    object_type type;
    char name[16];
    int stats;
} Object;

//alloccers

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

void Object_Rand_Draw(Object * object);