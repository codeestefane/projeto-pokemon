#include "batalha.h"

void carregaTextureBatalha(Batalha* batalha, Pokemon* pokemon, Cursor* cursor){
    batalha->backgroundBatalha = LoadTexture("img/battles/backgrounds.png");
    batalha->posicaoBackground = (Vector2){0, 0};
    batalha->menuBase = LoadTexture("img/battles/menuBase.png");
    batalha->posicaoMenuBase = (Vector2){0, 0};
    batalha->pokemonSelvagem = LoadTexture(TextFormat("img/pokemon/front/%d.png", pokemon->indiceImagem));
    batalha->posicaoPokemonSelvagem = (Vector2){0, 0};
    batalha->menuMoveOptions = LoadTexture("img/battles/menuMoveOptions.png");
    batalha->posicaoMenuMoveOptions = (Vector2){0, 0};
    cursor->cursor = LoadTexture("img/battles/ponteiro.png");
    cursor->posicaoCursor = (Vector2){0, 0};
    return;
};

void carregaPokemonPlayer(Batalha* batalha){
    //srand(time(NULL));
    batalha->indice = rand() % 721;
    batalha->pokemonPlayer = LoadTexture(TextFormat("img/pokemon/back/%d.png", batalha->indice));
    batalha->posicaoPokemonPlayer = (Vector2){0, 0};
    return;
}

void carregaPokemonPlayerFront(Batalha* batalha){
    batalha->pokemonPlayerFront = LoadTexture(TextFormat("img/pokemon/front/%d.png", batalha->indice));
    batalha->posicaoPokemonPlayerFront = (Vector2){0, 0};
    return;
}

void desenhaBackgroundBatalha(Batalha* batalha){
    DrawTexturePro(batalha->backgroundBatalha, 
    (Rectangle){(batalha->backgroundBatalha.width/3), batalha->posicaoBackground.y, (batalha->backgroundBatalha.width/3), (batalha->backgroundBatalha.height/4)},
    (Rectangle){batalha->posicaoBackground.x * 4, batalha->posicaoBackground.y * 4, (batalha->backgroundBatalha.width/3) * 4, (batalha->backgroundBatalha.height/4) * 4},
    (Vector2){0, 0}, 0, WHITE);
    return;
}

void desenhaPokemonBatalha(Batalha* batalha, Pokemon* pokemon){
    DrawTexturePro(pokemon->textura,
    (Rectangle){0, 0, (pokemon->textura.width), (pokemon->textura.height)},
    (Rectangle){((batalha->backgroundBatalha.width/3) - pokemon->textura.width - 15) * 4, (pokemon->posicao.y * 4) - 10, (pokemon->textura.width) * 4, (pokemon->textura.height) * 4},
    (Vector2){0, 0}, 0, WHITE);

    DrawTexturePro(batalha->pokemonPlayer,
    (Rectangle){0, 0, (batalha->pokemonPlayer.width), (batalha->pokemonPlayer.height)},
    (Rectangle){15, 200, (batalha->pokemonPlayer.width) * 4, (batalha->pokemonPlayer.height) * 4},
    (Vector2){0, 0}, 0, WHITE);
    
    return;
}

void desenhaMenu(Batalha* batalha, Cursor* cursor){
    DrawTexturePro(batalha->menuBase, 
    (Rectangle){batalha->posicaoMenuBase.x, batalha->posicaoMenuBase.y, batalha->menuBase.width, (batalha->menuBase.height)},
    (Rectangle){batalha->posicaoMenuBase.x, (batalha->backgroundBatalha.height/4) * 4, (batalha->menuBase.width) * 4, (batalha->menuBase.height) * 4},
    (Vector2){0, 0}, 0, WHITE);
    
    return;
}

void desenhaTexto(Cursor* cursor, Batalha* batalha, Dados* dadosPokemon, Pokemon* pokemon){
    batalha->tempoPercorrido += GetFrameTime() * 1000;
    int tempo = batalha->tempoPercorrido - batalha->ultimoTempo;

    DrawTextEx(batalha->menuAtaque, TextFormat("%d", batalha->vidaPokemonAdversario), (Vector2){((240/2)) + 740, ((160/2) * 4) - 280}, 16 * 3, 5, (Color){0, 0, 0, 255});
    DrawTextEx(batalha->menuAtaque, TextFormat("%d", batalha->vidaPokemonPlayer), (Vector2){((240/2)) - 70, ((160/2) * 4) - 100}, 16 * 3, 5, (Color){0, 0, 0, 255});
    
    if(batalha->estadoBatalha){
        if(tempo <= 4000){
            DrawTextEx(batalha->menuAtaque,"Sua vez de atacar! Escolha seu melhor ataque!", (Vector2){(240/4) + 20, (batalha->backgroundBatalha.height) + (batalha->menuBase.height/2) + 30}, 8 * 3, 5, WHITE);
            DrawTextEx(batalha->menuAtaque, TextFormat("%d", batalha->vidaPokemonPlayer), (Vector2){((240/2)) - 70, ((160/2) * 4) - 100}, 16 * 3, 5, (Color){255, 0, 0, 255});
            // if (batalha->decrementoAdversario != -1) {
            // DrawTextEx(batalha->menuAtaque, TextFormat("-%d", batalha->decrementoAdversario), (Vector2){((240/2)), ((160/2) * 4) - 100}, 16 * 3, 5, (Color){255, 0, 0, 255});
            // } 
        } else {
            DrawTextEx(batalha->menuAtaque,"INVESTIDA", (Vector2){(240/4) + 20, (batalha->backgroundBatalha.height) + (batalha->menuBase.height/2) + 30}, batalha->tamanhoFonteInvestida * 3, 5, WHITE);
            DrawTextEx(batalha->menuAtaque, "ATORDOAR", (Vector2){(240/4) + 20, (batalha->backgroundBatalha.height) + (batalha->menuBase.height/2) + 80}, batalha->tamanhoFonteAtordoar * 3, 5, WHITE);

            DrawTexturePro(cursor->cursor, 
            (Rectangle){0, 0, cursor->cursor.width, (cursor->cursor.height)},
            (Rectangle){cursor->posicaoCursor.x + 45, (batalha->backgroundBatalha.height) + (batalha->menuBase.height/2) + cursor->posicaoCursor.y, (cursor->cursor.width) * 3, (cursor->cursor.height) * 3},
            (Vector2){0, 0}, 0, WHITE);
            
            batalha->ataquePlayer = true;
        }
    }else {
        if(tempo <= 4000){
            DrawTextEx(batalha->menuAtaque,TextFormat("Prepare-se, %s vai atacar!",  dadosPokemon[pokemon->indiceImagem - 1].nome), (Vector2){(240/4) + 20, (batalha->backgroundBatalha.height) + (batalha->menuBase.height/2) + 30}, 8 * 3, 5, WHITE);
            DrawTextEx(batalha->menuAtaque, TextFormat("%d", batalha->vidaPokemonAdversario), (Vector2){((240/2)) + 740, ((160/2) * 4) - 280}, 16 * 3, 5, (Color){255, 0, 0, 255});
            
            // if (batalha->decrementoPlayer != -1) {
            //     DrawTextEx(batalha->menuAtaque, TextFormat("-%d", batalha->decrementoPlayer), (Vector2){((240/2)), ((160/2) * 4) - 100}, 16 * 3, 5, (Color){255, 0, 0, 255});
            // } 
        } else{
            batalha->ataqueAdversario = true;

        }
    }
}

void calculaBatalha(Cursor* cursor, Batalha* batalha, Player* player){
    srand(time(NULL));

    int decremento;

    if(batalha->vidaPokemonPlayer <= 0 || batalha->vidaPokemonAdversario <= 0){
        batalha->tempoPercorrido = 0;
        batalha->ultimoTempo = 0;
        batalha->ataqueAdversario = false;
        batalha->ataquePlayer = false;
        player->estadoJogo = 4;
        setbuf(stdin, NULL);
    }

    if(!batalha->estadoBatalha){

        if(batalha->ataqueAdversario){
            decremento = rand() % 7;
            batalha->vidaPokemonPlayer -= decremento;
            //batalha->decrementoAdversario = decremento;
            printf("Ataque Adversario: %d\n\n", decremento);
            batalha->estadoBatalha = true;
            batalha->ataqueAdversario = false;
            batalha->ultimoTempo = batalha->tempoPercorrido;
        }

    }

}

void verificaCursor(Cursor* cursor, Batalha* batalha){

    srand(time(NULL));

    int decremento;
    
    if(cursor->investida){
        batalha->tamanhoFonteInvestida = 10;
        batalha->tamanhoFonteAtordoar = 8;
        cursor->posicaoCursor.y = 25;

        if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
            cursor->investida = false;
            cursor->atordoar = true;
            cursor->posicaoCursor.y = 78;
        }

        if(IsKeyDown(KEY_ENTER)){
            setbuf(stdin, NULL);
        
            if(batalha->ataquePlayer){
                decremento = rand() % 7;
                batalha->vidaPokemonAdversario -= decremento;
                batalha->ataquePlayer = false;
                //batalha->decrementoPlayer = decremento;
                printf("Ataque Player: %d\n\n", decremento);
                batalha->estadoBatalha = false;
                batalha->ultimoTempo = batalha->tempoPercorrido;
            }
            
        }

    }else if(cursor->atordoar){

        batalha->tamanhoFonteInvestida = 8;
        batalha->tamanhoFonteAtordoar = 10;

        if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
            cursor->investida = true;
            cursor->atordoar = false;
            cursor->posicaoCursor.y = 25;
        }

        if(IsKeyDown(KEY_ENTER)){
            setbuf(stdin, NULL);
        
            if(batalha->ataquePlayer){
                decremento = rand() % 7;
                batalha->vidaPokemonAdversario -= decremento;
                batalha->ataquePlayer = false;
                printf("Ataque Player: %d\n\n", decremento);
                batalha->estadoBatalha = false;
                batalha->ultimoTempo = batalha->tempoPercorrido;
            }
        }
    }

}

void descarregaBatalha(Batalha* batalha, Cursor* cursor){
    UnloadTexture(batalha->backgroundBatalha);
    UnloadTexture(batalha->menuBase);
    UnloadTexture(batalha->pokemonSelvagem); 
    UnloadTexture(cursor->cursor);
    //UnloadTexture(batalha->menuChoose);
    //UnloadTexture(batalha->menuMoveOptions);
    return;
};

void descarregaPokemonPlayer(Batalha* batalha){
    UnloadTexture(batalha->pokemonPlayer);
    UnloadTexture(batalha->pokemonPlayerFront);
}