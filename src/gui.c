#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "../include/bool.h"
#include "../include/gui.h"
#include "../include/ranking.h"
#include "../include/player.h"
#include "../include/game.h"

#include "../include/ingame/turn.h"
#include "../include/ingame/map.h"
#include "../include/ingame/hero.h"
#include "../include/ingame/block.h"
#include "../include/ingame/object.h"
#include "../include/ingame/coordinates.h"

// typedef struct Gui {
//     graphical_element * graphical_element;
//     Dimensions dimensions;
// } Gui;

// Gui* Gui_Load(){

//     Gui* GUI = (Gui*)malloc(sizeof(Gui));

//     GUI->graphical_element = (graphical_element*)malloc(sizeof(graphical_element)*graphical_elements_qtt);

//     for (graphical_element_type graphical_element_i = START_MENU; graphical_element_i < graphical_elements_qtt; graphical_element_i++){
        
//         if (
//             graphical_element_i ISNT MAP_A
//             AND graphical_element_i ISNT HUD //potion, health, weapon
//             AND graphical_element_i ISNT YOU_WIN
//             AND graphical_element_i ISNT YOU_LOSE
//             AND graphical_element_i ISNT RANKING
//         ){
//             Gui_Graphical_Element_Load(GUI, graphical_element_i);
//         }
//     }

// }

// void Gui_Graphical_Element_Load(Gui* GUI, graphical_element_type element){

//     FILE* to_load = fopen(path_arr[element], "r");

// };

void Gui_Clear(){

    printf("\e[1;1H\e[2J");
    
}