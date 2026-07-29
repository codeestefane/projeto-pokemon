#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "pokemon.h"
#include "global.h"

void carregarBackground(Background* background);
void descarregarBackground(Background* background);
void identificaPosicoesBackground(Background* background, Posicoes* posicoes, Player* player, Pokemon* pokemon, float escalaTela);
void desenhaBackground(Batalha* batalha, Background* background, Posicoes* posicoes, Player* player, Pokemon* pokemon, float escalaTela);
//void atualizaBackground(Background* background);

#endif