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

typedef struct Gui {
    window * window;
    window_type window_type;
    Dimensions Gui_size;
} Gui;

Gui* Gui_Load(){
    
    Gui* new = (Gui*)malloc(sizeof(Gui));

    new->window = (window*)malloc(sizeof(window)*window_qtt);

    for (int i = 0; i < window_qtt; i++){
        
        switch (i) {
        case START_MENU:
            /* code */
            break;

        case PLAYER_MENU:
        case MAP_MENU:case HUD:
        case YOU_WIN:case YOU_LOSE:
        case RANKING:case PLAY_AGAIN:
        case QUIT:case HELP:
        
        default:
            break;
        }


    }

}

void Gui_Unload(Gui* GUI){}

void Gui_Clear() {

    printf("\e[1;1H\e[2J");
    
}