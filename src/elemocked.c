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


int main(){

    Gui* GUI = Gui_Load();

    char start_or_quit;

    do {

        Gui_Print(GUI, START_MENU);
        start_or_quit = fgetc(stdin);
        Gui_Clear();

    } while (start_or_quit ISNT 'S' && start_or_quit ISNT 'Q');

    while (start_or_quit IS 'S'){

        Game* game = Game_Init(Player_Start(GUI), Game_Map_Select(GUI));

        Map* map = Map_Load(Game_Get_Map(game), GUI);
        Hero* hero = Hero_Load(GUI);

        bool failed = FALSE;

        Game_Timer_Start(game);

        do { New_Turn(hero, map, GUI); }
        while ( 
            ( NOT failed )
            &&
            ( Hero_Has_Treasure(hero) IS FALSE )
        );

        Game_Timer_Stop(game);

        Hero_Unload(hero);
        Map_Unload(map);

        if (failed) { 

            Gui_Print(GUI, YOU_LOSE);

            //endgame logic (turn into function)

            Game_Finish(game);

            Gui_Print(GUI, PLAY_AGAIN);
            
            char play_again = fgetc(stdin);

            do { play_again = fgetc(stdin); }
            while (
                play_again ISNT 'Y'
                &&
                play_again ISNT 'N'
            );
            
            if(play_again IS 'Y') { start_or_quit = 'S'; }
            if(play_again IS 'N') { start_or_quit = 'Q'; }
        }

        if (NOT failed) {

            Gui_Print(GUI, YOU_WIN);

            //verify ranking

            Ranking* ranking = Ranking_Load(Game_Get_Map(game), GUI);
            Ranking_Update(Game_Get_Player_Data(game), GUI);

            Gui_Print(GUI, RANKING);

            Ranking_Unload(ranking);

            //endgame logic (turn into function)

            Game_Finish(game);

            Gui_Print(GUI, PLAY_AGAIN);

            char play_again = fgetc(stdin);

            do { play_again = fgetc(stdin); }
            while (
                play_again ISNT 'Y'
                &&
                play_again ISNT 'N'
            );
            
            if(play_again IS 'Y') { start_or_quit = 'S'; }
            if(play_again IS 'N') { start_or_quit = 'Q'; }
        }
    }

    Gui_Print(GUI, EXIT);

    Gui_Unload(GUI);
    
}