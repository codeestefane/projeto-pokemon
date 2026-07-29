#ifndef PLAYER_H
#define PLAYER_H

#include <time.h>
#include <raylib.h>
#include <stdbool.h>
#include "pokemon.h"
#include "global.h"

void carregaPlayer(Player* player);
void desenhaPlayer(Player* player, float escalaTela);
void atualizaPlayer(Player* player, float escalaTela);
void sobreposicaoPlayerGrama(Batalha* batalha, Player* player, int posicaoGramaX, int posicaoGramaY, Pokemon* pokemon, Posicoes* posicoes);
void descarregaPlayer(Player* player);

#endif