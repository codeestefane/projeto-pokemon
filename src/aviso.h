#ifndef AVISO_H
#define AVISO_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include "global.h"
#include "pokemon.h"
#include "batalha.h"

//void desenhaBackgroundAviso(Aviso* aviso);
void carregaImagensAviso(Aviso* aviso, Pokemon* pokemon);
//void desenhaAviso(Aviso* aviso, Pokemon* pokemon);
void desenhaPokemonAviso(Aviso* aviso, Pokemon* pokemon);
void desenhaPokemonPlayer(Batalha* batalha, Aviso* aviso, Pokemon* pokemon);
void desenhaPokemonAdversario(Aviso* aviso, Pokemon* pokemon);
//void atualizaTituloAviso(Aviso* aviso);
void mensagemAviso(Aviso* aviso, Pokemon* pokemon, Dados* dadosPokemon);
void mensagemAvisoFinal(Batalha* batalha, Aviso* aviso);
void desenhaBotao(Aviso* aviso, Player* player);
void desenhaBotaoFinal(Batalha* batalha, Aviso* aviso, Player* player, Pokemon* pokemon);
void descarregaAviso(Aviso* aviso, Pokemon* pokemon);

#endif