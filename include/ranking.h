#ifndef RANKING_H
#define RANKING_H

typedef struct ranking Ranking;

Ranking * Ranking_Load();
void Ranking_Unload(Ranking * ranking);

#endif