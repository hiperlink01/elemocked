#include "../include/utils.h"

#include "../include/bool.h"
#include "../include/ranking.h"
#include "../include/player.h"
#include "../include/game.h"

#include "../include/ingame/turn.h"
#include "../include/ingame/map.h"
#include "../include/ingame/hero.h"
#include "../include/ingame/block.h"
#include "../include/ingame/object.h"
#include "../include/ingame/coordinates.h"

void Gui_Clear(){

    printf("\e[1;1H\e[2J");
    
}

typedef struct player {
    char name[11];
    int game_time;  
} Player;

Player* Player_Start(){

    Player* new = (Player*)malloc(sizeof(Player));

    printf("NAME:\n>> ");
    fgets(new->name, sizeof(new->name), stdin); clear_input_stream();
    new->name[10] = '\0';

    new->game_time = 0;

    return new;

}

int main() {

    char start_or_quit;

    do {

        printf("\n\nELEMOCKED\n\n[S] Start [Q] Quit\n\n>>");
        start_or_quit = fgetc(stdin); clear_input_stream();
        Gui_Clear();

    } while (start_or_quit ISNT 'S' && start_or_quit ISNT 'Q');

   while (start_or_quit IS 'S'){

        Game* game = Game_Alloc();
        Player* player = Player_Alloc();

        char name[11];
        printf("NAME (max 10 chars.):\n\n>>");
        fgets(name, 10, stdin); clear_input_stream();
        name[10] = '\0';

        Player_Set_Name(player, name);

        printf("Select Map ([A] or [B]):\n\n>>");
        game_map_select game_map = fgetc(stdin); clear_input_stream();

        Game_Set_Player(game, player);
        Game_Set_Map(game, game_map);

        Map* map = Map_Load();
        Hero* hero = Hero_Load();

        bool failed = FALSE;

        //START TIMER HERE OR INSIDE THE FUNCTION
        int timer = 0;
        Player_Set_Timer(player, timer);

        do { New_Turn(hero, map); }
        while ( 
            ( NOT failed )
            &&
            ( Hero_Has_Treasure(hero) IS FALSE )
        );

    //     Game_Timer_Stop(game);

    //     Hero_Unload(hero);
    //     Map_Unload(map);

    //     if (failed) { 

    //         Gui_Print(GUI, YOU_LOSE);

    //         //endgame logic (turn into function)

    //         Game_Finish(game);

    //         Gui_Print(GUI, PLAY_AGAIN);
            
    //         char play_again = fgetc(stdin);

    //         do { play_again = fgetc(stdin); }
    //         while (
    //             play_again ISNT 'Y'
    //             &&
    //             play_again ISNT 'N'
    //         );
            
    //         if(play_again IS 'Y') { start_or_quit = 'S'; }
    //         if(play_again IS 'N') { start_or_quit = 'Q'; }
    //     }

    //     if (NOT failed) {

    //         Gui_Print(GUI, YOU_WIN);

    //         //verify ranking

    //         Ranking* ranking = Ranking_Load(Game_Get_Map(game), GUI);
    //         Ranking_Update(Game_Get_Player_Data(game), GUI);

    //         Gui_Print(GUI, RANKING);

    //         Ranking_Unload(ranking);

    //         //endgame logic (turn into function)

    //         Game_Finish(game);

    //         Gui_Print(GUI, PLAY_AGAIN);

    //         char play_again = fgetc(stdin);

    //         do { play_again = fgetc(stdin); }
    //         while (
    //             play_again ISNT 'Y'
    //             &&
    //             play_again ISNT 'N'
    //         );
            
    //         if(play_again IS 'Y') { start_or_quit = 'S'; }
    //         if(play_again IS 'N') { start_or_quit = 'Q'; }
    //     }
    // }

    // Gui_Print(GUI, EXIT);

    // Gui_Unload(GUI);

    return 0 ;
    
    }
}