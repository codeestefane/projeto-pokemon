#include "aviso.h"
#include "teste.h"

void carregaImagensAviso(Aviso* aviso, Pokemon* pokemon){
    aviso->tituloPokemon = LoadTexture("img/menu/logo.png");
    aviso->pokemonAviso = LoadTexture(TextFormat("img/pokemon/front/%d.png", pokemon->indiceImagem));
    aviso->botaoIniciar = LoadTexture("img/menu/pressStart.png");
    aviso->fonte = LoadFont("img/fonts/pokemon_fire_red_70.ttf");
    aviso->posicaoPokemon = (Vector2){0, 0};
    aviso->posicaoTitulo = (Vector2){0, 0};
    aviso->posicaoBotao = (Vector2){0, 0};
    return;
}

void desenhaPokemonAdversario(Aviso* aviso, Pokemon* pokemon){
    DrawTexturePro(pokemon->textura, 
    (Rectangle){aviso->posicaoPokemon.x, aviso->posicaoPokemon.y, pokemon->textura.width, pokemon->textura.height},
    (Rectangle){((240/2) * 4) - (pokemon->textura.width * 2) - 5, ((160/2) * 4) - (pokemon->textura.height + 190), pokemon->textura.width * 4, pokemon->textura.height * 4},
    (Vector2){0, 0}, 0, WHITE);

    return;
};

void desenhaPokemonPlayer(Batalha* batalha, Aviso* aviso, Pokemon* pokemon){
    DrawTexturePro(batalha->pokemonPlayerFront, 
    (Rectangle){batalha->posicaoPokemonPlayerFront.x, batalha->posicaoPokemonPlayerFront.y, batalha->pokemonPlayerFront.width, batalha->pokemonPlayerFront.height},
    (Rectangle){((240/2) * 4) - (pokemon->textura.width * 2) - 5, ((160/2) * 4) - (pokemon->textura.height + 190),pokemon->textura.width * 4, pokemon->textura.height * 4},
    (Vector2){0, 0}, 0, WHITE);

    return;
};

void mensagemAvisoFinal(Batalha* batalha, Aviso* aviso){
    setbuf(stdin, NULL);

    if(batalha->vidaPokemonPlayer <= 0){  
        DrawTextEx(aviso->fonte, "Que pena! Seu pokemon perdeu! =(", (Vector2){((240/2)), ((160/2) * 4) + 90}, 16 * 3, 5, WHITE);
    } else {
        DrawTextEx(aviso->fonte, "Eba! Seu pokemon venceu! =)", (Vector2){((240/2)) + 50, ((160/2) * 4) + 90}, 16 * 3, 5, WHITE);
    }

    DrawTextEx(aviso->fonte, "ou pressione a tecla Z para retornar ao Menu!", (Vector2){((240/2)), ((160/2) * 4) + 235}, 32, 5, WHITE);

    return;
};

void mensagemAviso(Aviso* aviso, Pokemon* pokemon, Dados* dadosPokemon){
    DrawTextEx(aviso->fonte, TextFormat("Voce encontrou %s selvagem...", dadosPokemon[pokemon->indiceImagem - 1].nome), (Vector2){((240/2)), ((160/2) * 4) + 70}, 16 * 3, 5, (Color){0, 0, 0, 255});
    DrawTextEx(aviso->fonte, "Hora de batalhar!", (Vector2){((240/2)) + 160, ((160/2) * 4) + 120}, 16 * 3, 5, (Color){0, 0, 0, 255});
    return;
};

void desenhaBotao(Aviso* aviso, Player* player){

    if(aviso->piscaBotao){
        DrawTexturePro(aviso->botaoIniciar, 
        (Rectangle){aviso->posicaoBotao.x, aviso->posicaoBotao.y, aviso->botaoIniciar.width, aviso->botaoIniciar.height},
        (Rectangle){((240/2) * 4) - (aviso->botaoIniciar.width * 2) - 25, ((160/2) * 4) - (aviso->botaoIniciar.height) + 210, aviso->botaoIniciar.width * 4, aviso->botaoIniciar.height * 4},
        (Vector2){0, 0}, 0, WHITE);
    }

    setbuf(stdin, NULL);

    if(IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_ENTER)){
        player->estadoJogo = 3;
        setbuf(stdin, NULL);
    }
    return;
}

void desenhaBotaoFinal(Batalha* batalha, Aviso* aviso, Player* player, Pokemon* pokemon){

    if(aviso->piscaBotao){
        DrawTexturePro(aviso->botaoIniciar, 
        (Rectangle){aviso->posicaoBotao.x, aviso->posicaoBotao.y, aviso->botaoIniciar.width, aviso->botaoIniciar.height},
        (Rectangle){((240/2) * 4) - (aviso->botaoIniciar.width * 2) - 25, ((160/2) * 4) - (aviso->botaoIniciar.height) + 180, aviso->botaoIniciar.width * 4, aviso->botaoIniciar.height * 4},
        (Vector2){0, 0}, 0, WHITE);
    }

    if(IsKeyPressed(KEY_SPACE)){
        setbuf(stdin, NULL);
        player->estadoJogo = 1;
        player->posicao = (Vector2){0, 0};
        descarregaPokemon(pokemon);
        carregaPokemon(pokemon);
        descarregaPokemonPlayer(batalha);
        carregaPokemonPlayer(batalha);
        carregaPokemonPlayerFront(batalha);
        batalha->vidaPokemonPlayer = 20;
        batalha->vidaPokemonAdversario = 20;
    }

    if(IsKeyDown(KEY_Z)){
        setbuf(stdin, NULL);
        player->estadoJogo = 0;
        player->posicao = (Vector2){0, 0};
        descarregaPokemon(pokemon);
        carregaPokemon(pokemon);
        descarregaPokemonPlayer(batalha);
        carregaPokemonPlayer(batalha);
        carregaPokemonPlayerFront(batalha);
        descarregaMenu();
        carregaMenu();
        batalha->vidaPokemonPlayer = 20;
        batalha->vidaPokemonAdversario = 20;
        //mainMenu(player);
    }

    return;
}

void descarregaAviso(Aviso* aviso, Pokemon* pokemon){
    UnloadTexture(aviso->pokemonAviso);
    UnloadTexture(aviso->botaoIniciar);
    UnloadFont(aviso->fonte);
    UnloadTexture(pokemon->textura);
    return;
}

