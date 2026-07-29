#ifndef BATALHA_H
#define BATALHA_H

#include "global.h"
#include <time.h>

void carregaTextureBatalha(Batalha* batalha, Pokemon* pokemon, Cursor* cursor);
void desenhaBackgroundBatalha(Batalha* batalha);
void descarregaBatalha(Batalha* batalha, Cursor* cursor);
void desenhaMenu(Batalha* batalha, Cursor* cursor);
void desenhaTexto(Cursor* cursor, Batalha* batalha, Dados* dadosPokemon, Pokemon* pokemon);
void verificaCursor(Cursor* cursor, Batalha* batalha);
void calculaBatalha(Cursor* cursor, Batalha* batalha, Player* player);
void desenhaPokemonBatalha(Batalha* batalha, Pokemon* pokemon);
void descarregaPokemonPlayer(Batalha* batalha);
void carregaPokemonPlayer(Batalha* batalha);
void carregaPokemonPlayerFront(Batalha* batalha);

#endif