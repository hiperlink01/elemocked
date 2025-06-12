#ifndef GUI_H
#define GUI_H

// typedef struct gui Gui;

// typedef char ** graphical_element;

// typedef enum {
//     START_MENU,
//     PLAYER_MENU,
//     MAP_MENU,
    
//     MAP_A,
//     MAP_B,
    
//     HEALTH,
//     WEAPON,
//     POTION,
    
//     YOU_WIN,
//     YOU_LOSE,
    
//     RANKING,
    
//     PLAY_AGAIN,
//     QUIT,
//     HELP,

//     EXIT,
    
//     graphical_elements_qtt
// } graphical_element_type;

// char path_arr[graphical_elements_qtt][64] =
// {    
//     "../assets/menu/start_menu.txt",
//     "../assets/menu/player_menu.txt",
//     "../assets/menu/map_menu.txt",

//     "../assets/maps/map_a.txt",
//     "../assets/maps/map_b.txt",

//     "../assets/hud/health.txt",
//     "../assets/hud/weapon.txt",
//     "../assets/hud/potion.txt",

//     "../assets/menu/you_win.txt",
//     "../assets/menu/you_lose.txt",

//     "../assets/ranking.bin",

//     "../assets/menu/play_again.txt",
//     "../assets/menu/quit.txt",
//     "../assets/menu/help.txt",

//     "../assets/menu/exit.txt",  
// };

// Gui* Gui_Load();
// void Gui_Unload(Gui* Gui);

// void Gui_Update(Gui* Gui);

// void Gui_Print(Gui* GUI, graphical_element_type to_print);

void Gui_Clear();

#endif