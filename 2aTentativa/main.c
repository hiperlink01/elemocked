#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { FALSE, TRUE } bool;

typedef struct player {
    char* name;
    int timer;  
} Player;

typedef enum {

    A, B,

    map_qtt
} map_select;

typedef struct coordinates {
    int x, y;
} Coordinates;

typedef struct dimensions {
    int width, height;
} Dimensions;

typedef enum {
    BOMB, POTION,
    
    WEAPON_STEEL,
    WEAPON_AIR, WEAPON_EARTH,
    WEAPON_FIRE, WEAPON_WATER
} object_type, weapon_type;

typedef struct object {
    object_type type;
    char* name;
    int stats;
} Object;

typedef enum {
    EMPTY = ' ',
    CHEST = '?',
    ROCK = '@',
    WALL = '=',

    HERO = 'k',
    
    LOCK_AIR = 'A', LOCK_EARTH = 'E',
    LOCK_FIRE = 'F', LOCK_WATER = 'W',

    TREASURE = '+'
} block_type;

typedef struct block {
    block_type type;
    Object* object;
} Block;

typedef struct map {
    Dimensions dimensions;
    char** graphical;
    Block** functional;
} Map;

typedef struct POCHETE {
    Object* * weapons;
    Object* * potions;
    bool has_treasure;
} Bag;

typedef struct hero {
    char* name;
    int health;
    weapon_type current_weapon;
    Bag* magical_waist_bag;
    Coordinates position;
} Hero;

typedef enum {

    MOVE_UP = 'W', 
    MOVE_LEFT = 'A',
    MOVE_DOWN = 'S',
    MOVE_RIGHT = 'D',

    OPEN_CHEST = 'E',

    ATTACK = 'K',
    CHANGE_WEAPON = 'O'
    
} hero_action;

//UTILS

//helper function to clear the input stream after read character(s)
void Clear_Input_Stream() {
    int c;
    //d==card characters until newline or end-of-file
    do { c = getchar(); }
    while ( c != '\n' && c != EOF );
}

void Gui_Clear(){

    system("clear");
    
}

//helper function to count how many occurrences of a character appear in a string
int strcnt(char* str, char to_count){

    int count = 0;
    
    for (int i = 0; i < strlen(str) && str[i] != '\0'; i++)
    { if (str[i] == to_count) { count++; } }

    return count;
}

//ENDOF UTILS

//////////////////////////////////////////////////////////////////////////////////////////

void Hero_Set_Position(Hero* hero, Coordinates position)
{ hero->position = position; }


int Hero_Get_Health(Hero* hero){
    return hero->health;
}

//////////////////////////////////////////////////////////////////////////////////////////

//PLAYER


Player* Player_Alloc(){

    Player* new = (Player*)malloc(sizeof(Player));
    new->name = (char*)malloc(sizeof(char)*11);
    new->timer = 0;

    return new;

}

void Player_Set_Name(Player* player, char* name)
{ strcpy(player->name, name); }

//ENDOF PLAYER

//////////////////////////////////////////////////////////////////////////////////////////

//OBJECT

Object* Object_Alloc(){
    Object* new = (Object*)malloc(sizeof(Object));
    new->type = 0;
    new->name = (char*)malloc(sizeof(char)*32);
    new->stats = 0;
    return new;
};

void Object_Set_Type(Object* object, object_type type)
{ object->type = type; };
void Object_Set_Name(Object* object, char* name)
{ strcpy(object->name, name); };
void Object_Set_Stats(Object* object, int stats)
{ object->stats = stats; };

int Object_Get_Stats(Object* object){
    return object->stats;
}
object_type Object_Get_Type(Object* object){
    return object->type;
};
char* Object_Get_Name(Object* object)
{ return object->name; };

//ENDOF OBJECT

//////////////////////////////////////////////////////////////////////////////////////////

//BLOCK


void Block_Set_Type(Block* block, block_type type){
    block->type = type;
}
void Block_Set_Object(Block* block, Object* object){
    block->object = object; 
}

block_type Block_Get_Type(Block* block)
{ return block->type; };
Object * Block_Get_Object(Block* block){
    return block->object;
}

Block** Block_Matrix_Alloc(int height, int width){

    Block** block_matrix = (Block**)(malloc(sizeof(Block*)*height));

    for (int i = 0; i < height; i++){
        block_matrix[i] = (Block*)malloc(sizeof(Block)*width);
    }

    return block_matrix;

}

//ENDOF BLOCK

//////////////////////////////////////////////////////////////////////////////////////////


//MAP

Map* Map_Alloc(){ 
    
    Map* new = (Map*)malloc(sizeof(Map));

    return new;

}

//--helper functions for the loaders--

int Map_Count_Chest(Map* map){

    int chest_count = 0;
    for (int i = 0; i<map->dimensions.height; i++){
        
        chest_count += strcnt(map->graphical[i], '?');

    }

    return chest_count;

}

object_type* Generate_Rand_Chest_Objects_Arr(int chest_count){

    object_type* objects_arr = (object_type*)malloc(sizeof(object_type)* chest_count);
    object_type aux[chest_count];

    aux[0] = WEAPON_AIR; aux[1] = WEAPON_EARTH;
    aux[2] = WEAPON_FIRE; aux[3] = WEAPON_WATER;

    for (int i = 4; i<chest_count; i++){
        
        int rand_select = rand() % 2;
        
        if (rand_select == 1) { aux[i] = POTION; }
        if (rand_select == 0) { aux[i] = BOMB; }

    }

    int chest_count_aux = chest_count;

    for (int i = 0; i < chest_count; i++){

        int rand_index = rand() % chest_count_aux;
        
        objects_arr[i] = aux[rand_index];

        aux[rand_index] = aux[chest_count_aux-1];

        chest_count_aux--;

    }

    return objects_arr;
}
//--end of helper functions for the loaders--

void Map_Load_Dimensions(Map* map, map_select selected_map){
    
    FILE* f_map;

    if(selected_map == A)
    { f_map = fopen("map_a.txt", "r"); }
    if(selected_map == B)
    { f_map = fopen("map_b.txt", "r"); }
      
    int width = 0, height = 0;

    char buff[64];

    fgets(buff, sizeof(buff), f_map);
    width = strlen(buff);

    fseek(f_map, 0, SEEK_SET);

    while(fgets(buff, sizeof(buff), f_map))
    { height++; }

    fclose(f_map);

    map->dimensions.width = width;
    map->dimensions.height = height;

}

void Map_Load_Graphical(Map* map, map_select game_map){

    map->graphical = (char**)malloc(sizeof(char*)* (map->dimensions.height));

    for (int i = 0; i < map->dimensions.height; i++){
        map->graphical[i] = (char*)malloc(sizeof(char) * (map->dimensions.width));
    }

    FILE* f_map;

    if(game_map == A)
    { f_map = fopen("map_a.txt", "r"); }
    if(game_map == B)
    { f_map = fopen("map_b.txt", "r"); }

    for (int i = 0; i < map->dimensions.height; i++){

        fgets(map->graphical[i], map->dimensions.width + 1, f_map);

        char* check_new_line = strchr(map->graphical[i], '\n');

        if(check_new_line != NULL){ *check_new_line = '\0';}
        
    }
    
    fclose(f_map);

}

void Map_Load_Functional(Map* map, Hero* hero){

    int chest_count = Map_Count_Chest(map);
    object_type* objects_arr = Generate_Rand_Chest_Objects_Arr(chest_count);

    map->functional = Block_Matrix_Alloc(map->dimensions.height, map->dimensions.width);

    for (int i = 0; i < map->dimensions.height; i++){
        for (int j = 0; j < map->dimensions.width; j++){

            switch (map->graphical[i][j]) {

            case EMPTY:
                map->functional[i][j].type = EMPTY;
                map->functional[i][j].object = NULL;
                break;

            case CHEST:
                map->functional[i][j].type = CHEST;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, objects_arr[chest_count-1]);

                switch (map->functional[i][j].object->type) {
                case BOMB:
                    Object_Set_Name(map->functional[i][j].object, "BOMB\0");
                    int rand_stats_bomb = -(1 + (rand()%4)); //random value from -1 to -4
                    Object_Set_Stats(map->functional[i][j].object, rand_stats_bomb);
                    break;

                case POTION:
                    Object_Set_Name(map->functional[i][j].object, "POTION\0");
                    int rand_stats_potion = 1 + (rand()%3); //random value from 1 to 3
                    Object_Set_Stats(map->functional[i][j].object, rand_stats_potion);
                    break;

                case WEAPON_AIR:
                    Object_Set_Name(map->functional[i][j].object, "AIR WHIP\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_EARTH:
                    Object_Set_Name(map->functional[i][j].object, "EARTH GAUNTLETS\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_FIRE:
                    Object_Set_Name(map->functional[i][j].object, "FIRE SPEAR\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                case WEAPON_WATER:
                    Object_Set_Name(map->functional[i][j].object, "WATER SWORD\0");
                    Object_Set_Stats(map->functional[i][j].object, 0);
                    break;

                default:
                    break;
                }

                chest_count--;

                break;

            case ROCK:
                map->functional[i][j].type = ROCK;
                map->functional[i][j].object = NULL;                
                break;

            case WALL:
                map->functional[i][j].type = WALL;
                map->functional[i][j].object = NULL;                
                break;

            case HERO:
                map->graphical[i][j] = ' ';
                Coordinates hero_coordinates;
                hero_coordinates.x = j;
                hero_coordinates.y = i;
                Hero_Set_Position(hero, hero_coordinates);
                break;

            case LOCK_AIR:
                map->functional[i][j].type = LOCK_AIR;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_AIR);
                Object_Set_Name(map->functional[i][j].object, "AIR WHIP\0");
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_EARTH:
                map->functional[i][j].type = LOCK_EARTH;             
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_EARTH);
                Object_Set_Name(map->functional[i][j].object, "EARTH GAUNTLETS\0");
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_FIRE:
                map->functional[i][j].type = LOCK_FIRE;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_FIRE);
                Object_Set_Name(map->functional[i][j].object, "FIRE SPEAR\0");
                Object_Set_Stats(map->functional[i][j].object, 0);
                break;

            case LOCK_WATER:
                map->functional[i][j].type = LOCK_WATER;
                map->functional[i][j].object = Object_Alloc();
                Object_Set_Type(map->functional[i][j].object, WEAPON_WATER);
                Object_Set_Name(map->functional[i][j].object, "WATER SWORD\0");
                Object_Set_Stats(map->functional[i][j].object, 0);          
                break;

            case TREASURE:
                map->functional[i][j].type = TREASURE;
                map->functional[i][j].object = NULL;                
                break;

            default:
                break;
            }
        }
    }

    free(objects_arr);

}

void Map_Load(Map* map, map_select selected_map, Hero* hero){

    Map_Load_Dimensions(map, selected_map);
    Map_Load_Graphical(map, selected_map);
    Map_Load_Functional(map, hero);

}

Block* Map_Get_Block(Map* map, int x, int y)
{ return &(map->functional[y][x]); }

void Map_Print(Map* map){

    for (int i = 0; i<map->dimensions.height; i++)
    { printf("%s\n", map->graphical[i]); }

}

void Map_Update_Graphical(Map* map, Hero* hero){

    for (int i=0; i<map->dimensions.height; i++){
        for (int j=0; j<map->dimensions.width; j++){

            if (i == hero->position.y && j == hero->position.x){
                map->graphical[i][j] = 'k';
            }

            else {

                switch (map->functional[i][j].type) {

                case EMPTY:
                    map->graphical[i][j] = ' ';
                    break;

                case CHEST:
                    if (map->functional[i][j].object == NULL)
                    {map->graphical[i][j] = 'o';}
                    else {map->graphical[i][j] = '?';}
                    break;

                case ROCK:
                    map->graphical[i][j] = '@';
                    break;

                case WALL:
                    map->graphical[i][j] = '=';
                    break;

                case LOCK_AIR:
                    map->graphical[i][j] = 'A';
                    break;

                case LOCK_EARTH:
                    map->graphical[i][j] = 'E';
                    break;

                case LOCK_FIRE:
                    map->graphical[i][j] = 'F';
                    break;

                case LOCK_WATER:
                    map->graphical[i][j] = 'W';
                    break;

                case TREASURE:
                    map->graphical[i][j] = '+';
                    break;

                default:
                    break;
                }
            }

        }
    }
}

//ENDOF MAP

//////////////////////////////////////////////////////////////////////////////////////////

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


Hero* Hero_Alloc(){

    Hero* new = (Hero*)malloc(sizeof(Hero));
    new->magical_waist_bag = Bag_Alloc();
    new->name = (char*)malloc(sizeof(char)*9);
    strcpy(new->name, "Joaquim\0");
    new->health = 10;
    new->current_weapon = WEAPON_STEEL;
    new->magical_waist_bag = Bag_Alloc();
    //hero->position == set by Map_Load()

    return new;

};


void Hero_Move(Hero* hero, Map* map, hero_action movement){

    //get current position
    //check if next position == valid
    //move if it ==
    //do nothing if it !=

    block_type destination_block_type;
    
    switch (movement) {
    case MOVE_UP:

        destination_block_type = Block_Get_Type(Map_Get_Block(map, hero->position.x, (hero->position.y)-1));

        if(
            destination_block_type != ROCK && destination_block_type != WALL
            &&
            destination_block_type != LOCK_AIR && destination_block_type != LOCK_EARTH
            && destination_block_type != LOCK_FIRE && destination_block_type != LOCK_WATER)
        { hero->position.y--; }
        break;

    case MOVE_LEFT:
        
        destination_block_type = Block_Get_Type(Map_Get_Block(map, (hero->position.x)-1, hero->position.y));

        if(
            destination_block_type != ROCK && destination_block_type != WALL
            &&
            destination_block_type != LOCK_AIR && destination_block_type != LOCK_EARTH
            && destination_block_type != LOCK_FIRE && destination_block_type != LOCK_WATER)
        { hero->position.x--; }
        break;
        
    case MOVE_DOWN:

        destination_block_type = Block_Get_Type(Map_Get_Block(map, hero->position.x, (hero->position.y)+1));

        if(
            destination_block_type != ROCK && destination_block_type != WALL
            &&
            destination_block_type != LOCK_AIR && destination_block_type != LOCK_EARTH
            && destination_block_type != LOCK_FIRE && destination_block_type != LOCK_WATER)
        { hero->position.y++; }
        break;
        
    case MOVE_RIGHT:
        
        destination_block_type = Block_Get_Type(Map_Get_Block(map, (hero->position.x)+1, hero->position.y));

        if(
            destination_block_type != ROCK && destination_block_type != WALL
            &&
            destination_block_type != LOCK_AIR && destination_block_type != LOCK_EARTH
            && destination_block_type != LOCK_FIRE && destination_block_type != LOCK_WATER)
        { hero->position.x++; }
        break;

    default: break;
    }

    if (Block_Get_Type(&(map->functional[hero->position.y][hero->position.x])) == TREASURE){ 

        hero->magical_waist_bag->has_treasure = TRUE;

    }

}

weapon_type Hero_Get_Current_Weapon(Hero* hero){
    return hero->current_weapon;
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
                == 
                Object_Get_Type(
                    Block_Get_Object(block_to_check)
                ) //all 4 locks store the value corresponding to the weapons that break them;
            ){    //therefore, if the hero == wielding the weapon, values will match, blocks will be set to empty.
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
        ) == CHEST
        &&
        Block_Get_Object(
            Map_Get_Block(map, hero->position.x, hero->position.y)
        ) != NULL
    ){

        Object* inside_chest = Block_Get_Object(Map_Get_Block(map, hero->position.x, hero->position.y));

        switch(Object_Get_Type(inside_chest)){

        case BOMB:
            hero->health += Object_Get_Stats(inside_chest);
            break;

        case POTION:
            for (int i = 0; i<10; i++){
                if (hero->magical_waist_bag->potions[i] == NULL)
                { hero->magical_waist_bag->potions[i] = inside_chest; break; }
            }
            break;
        
        case WEAPON_AIR: case WEAPON_EARTH:
        case WEAPON_FIRE: case WEAPON_WATER:
            for (int i = 0; i<5; i++){
                if (hero->magical_waist_bag->weapons[i] == NULL)
                { hero->magical_waist_bag->weapons[i] = inside_chest; break; }
            }
            break;
        }

        Block_Set_Object(Map_Get_Block(map, hero->position.x, hero->position.y), NULL);
    }
}

void Hero_Change_Weapon(Hero* hero){

    int i = 0;
    while ( Object_Get_Type(hero->magical_waist_bag->weapons[i]) != hero->current_weapon ) 
    { i++; } //set index to current weapon
    if(i==4){i=-1;}
    while ( hero->magical_waist_bag->weapons[i+1] == NULL )
    { i++; if(i==4){i=-1;} } //search next indexes for available weapons; when exceeds max index, returns to first
    i++;

    hero->current_weapon = Object_Get_Type(hero->magical_waist_bag->weapons[i]);
    //sets current weapon to found available index

};

void Hero_Drink_Potion(Hero* hero, hero_action current_action){

    if (hero->magical_waist_bag->potions[current_action-'0'-1] != NULL){
        
        hero->health += Object_Get_Stats(
            hero
            ->magical_waist_bag
            ->potions[current_action-'0'-1]
        );

        hero->magical_waist_bag->potions[current_action-'0'-1] = NULL;

    }
}

bool Hero_Has_Treasure(Hero* hero){
    return hero->magical_waist_bag->has_treasure;
};

void Hero_Print(Hero* hero){

    int health;
    health = hero->health;

    char* current_weapon_name;
    for(int i = 0; i < 5; i++){
        if(hero->magical_waist_bag->weapons[i] != NULL){
            if(Object_Get_Type(hero->magical_waist_bag->weapons[i]) == hero->current_weapon)
            { current_weapon_name = Object_Get_Name(hero->magical_waist_bag->weapons[i]); }
        }
    }

    printf("HEALTH: %d/10 | WEAPON: %s\n\n", health, current_weapon_name);

    Object* * potions;
    potions = hero->magical_waist_bag->potions;

    printf("POTIONS:\n");
    for (int i = 0; i<10; i++){

        if (potions[i] != NULL){
            
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

//ENDOF HERO

//////////////////////////////////////////////////////////////////////////////////////////

//TURN

bool New_Turn(Hero* hero, Map* map) {

    bool failure = FALSE;

    Map_Print(map);
    Hero_Print(hero);

    printf("[H] for help\n\n>>");
    hero_action current_action = fgetc(stdin); Clear_Input_Stream();

    switch (current_action){

        case MOVE_UP: case MOVE_LEFT:
        case MOVE_DOWN: case MOVE_RIGHT:
            Hero_Move(hero, map, current_action);
            // update map
            break;
        
        case ATTACK:
            Hero_Attack(hero, map);
            // update map (@AEFW to ' ')
            break;

        case OPEN_CHEST:
            Hero_Open_Chest(hero, map);
            // update map (? to o)
            break;
        
        case CHANGE_WEAPON:
            Hero_Change_Weapon(hero);
            break;

        default:
            if( (current_action >= '0' && current_action <= '9') )
            { Hero_Drink_Potion(hero, current_action); }
            else { printf("\nInvalid entry.\n"); }
            break;
    }

    Map_Update_Graphical(map, hero);

    Gui_Clear();

    if (Hero_Get_Health(hero) <= 0) { failure = TRUE; }

    return failure;

}

//ENDOF TURN

//////////////////////////////////////////////////////////////////////////////////////////

int main() {

    srand(time(NULL));

    char start_or_quit;

    do {

        printf("\n\nELEMOCKED\n\n[S] Start [Q] Quit\n\n>>");
        start_or_quit = fgetc(stdin); Clear_Input_Stream();
        Gui_Clear();

    } while (start_or_quit != 'S' && start_or_quit != 'Q');

    while (start_or_quit == 'S'){

        Player* player = Player_Alloc();

        char name[11];
        printf("NAME (max 10 chars.):\n\n>>");
        fgets(name, 10, stdin); Clear_Input_Stream(); Gui_Clear();
        name[10] = '\0';

        Player_Set_Name(player, name);

        map_select selected_map; do {

            printf("Select Map ([A] or [B]):\n\n>>");
            selected_map = fgetc(stdin); Clear_Input_Stream(); Gui_Clear();

            if(selected_map == 'A' || selected_map == 'B') { selected_map-='A'; }

        } while (selected_map != A && selected_map != B);
        
        Map* map = Map_Alloc();
        Hero* hero = Hero_Alloc();

        Map_Load(map, selected_map, hero);

        bool failed = FALSE;

        //START TIMER HERE
        //int timer = 0;
        //Player_Set_Timer(player, timer);

        do { failed = New_Turn(hero, map); }
        while ( 
            ( ! failed )
            &&
            ( Hero_Has_Treasure(hero) == FALSE )
        );

        do {

            printf("\n\nPLAY AGAIN?\n\n[S] YES [Q] NO\n\n>>");
            start_or_quit = fgetc(stdin); Clear_Input_Stream();
            Gui_Clear();

        } while (start_or_quit != 'S' && start_or_quit != 'Q');

    }
}