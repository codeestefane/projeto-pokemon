#ifndef POKEMON_H
#define POKEMON_H

#include <raylib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "background.h"
#include "global.h"

void carregaPokemon(Pokemon* pokemon);
void desenhaPokemon(Player* player, Pokemon* pokemon);
void descobriuPokemon(Pokemon* pokemon, Player* player);
void aleatorizaPokemon(Pokemon* pokemon, Posicoes* posicoes);
void descarregaPokemon(Pokemon* pokemon);
//void salvaPokemonsPlanta(Dados* dadosPokemon, Pokemon* pokemon);

#endif