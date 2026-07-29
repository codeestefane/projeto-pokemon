#include "pokemon.h"

void carregaPokemon(Pokemon* pokemon){

    srand(time(NULL));

    pokemon->indiceImagem = rand() % 721;
    
    pokemon->textura = LoadTexture(TextFormat("img/pokemon/front/%d.png", pokemon->indiceImagem));
    pokemon->posicao = (Vector2){0, 0};
    
    return;
}

void descarregaPokemon(Pokemon* pokemon){
    UnloadTexture(pokemon->textura);
    return;
}

void aleatorizaPokemon(Pokemon* pokemon, Posicoes* posicoes){
    
    srand(time(NULL));

    if(!pokemon->aleatorizaPokemon){
        pokemon->posicaoPokemon = posicoes->posicaoGrama[rand() % (posicoes->qtdGrama - 1)];
        pokemon->aleatorizaPokemon = true;
    }

    return;
}

void descobriuPokemon(Pokemon* pokemon, Player* player){
    if(CheckCollisionRecs(player->posicaoPlayer, pokemon->posicaoPokemon)){
        player->posicao = (Vector2){0, 0};
        pokemon->desenhaPokemon = true;
    }

    return;
}