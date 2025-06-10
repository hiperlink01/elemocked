#ifndef MAP_H
#define MAP_H

typedef struct map Map;

Map* Map_Load(game_map_select selected_map, Gui* GUI);
void Map_Unload(Map* map);

void Map_Dimension(Map* map);

char** Map_Alloc(Map* map);
void Map_Free(Map* map);

void Map_Fill(Map* map);

void Map_Update(Map* map);

void Map_Print(Map* map);

#endif