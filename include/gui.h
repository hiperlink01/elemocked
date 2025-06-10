#ifndef GUI_H
#define GUI_H

typedef struct gui Gui;

typedef char ** window;

typedef enum {
    START_MENU,
    PLAYER_MENU,
    MAP_MENU,
    
    HUD,
    
    YOU_WIN,
    YOU_LOSE,
    
    RANKING,
    
    PLAY_AGAIN,
    QUIT,
    HELP,

    EXIT,

    window_qtt
} window_type, window_quantity;

Gui* Gui_Load();
void Gui_Unload(Gui* Gui);

void Gui_Update(Gui* Gui);

void Gui_Print(Gui* GUI, window_type to_print);

void Gui_Clear();

#endif