#include "player.h"
#include "background.h"

void carregaPlayer(Player* player){
    printf("\nplayer %d\n", player->genero);
    player->textura = LoadTexture(TextFormat("img/player/%d/walk.png", player->genero));
    player->posicao = (Vector2) {0, 0};
    player->ultimoTempo = 0;
    player->tempoPercorrido = 0;
    player->velocidade = 0.5;
    player->frameX = 0;
    player->frameY = 0;
    return;
}

void desenhaPlayer(Player* player, float escalaTela){

    DrawTexturePro(player->textura,
    (Rectangle){player->frameX * (player->textura.width/4), player->frameY * (player->textura.height/4), player->textura.width/4, player->textura.height/4},
    (Rectangle){player->posicao.x * escalaTela, player->posicao.y * escalaTela, (player->textura.width/4) * escalaTela, (player->textura.height/4) * escalaTela},
    (Vector2){0, 0}, 0, WHITE);
                       
    return;
}

void atualizaPlayer(Player* player, float escalaTela){

    int andando = 0;

    float tempo;

    if(IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        player->posicao.y += player->velocidade;
        player->frameY = 0;
        andando = 1;  
    }else if(IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        player->posicao.y -= player->velocidade; 
        player->frameY = 1;
        andando = 1;
    }else if(IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)){
        player->posicao.x -= player->velocidade;
        player->frameY = 2;
        andando = 1;
    }else if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)){
        player->posicao.x += player->velocidade;
        player->frameY = 3;
        andando = 1;
    }else{
        player->frameX = 0;
    }

    if(andando == 1){
        player->tempoPercorrido += GetFrameTime() * 1000;
        tempo = player->tempoPercorrido - player->ultimoTempo;
        if(tempo > 150){
            player->ultimoTempo = player->tempoPercorrido;
            player->frameX++;
            if(player->frameX >= 4){
                player->frameX = 0;
            }
        }
    }

    if(player->posicao.y > (160 - (player->textura.height)/4)){
        player->posicao.y = (160 - (player->textura.height)/4);
    }else if(player->posicao.y < (-10)){
        player->posicao.y = (-10);
    }else if(player->posicao.x > 240 - ((player->textura.width)/4)){
        player->posicao.x = (240 - ((player->textura.width)/4));
    }else if(player->posicao.x < 0){
        player->posicao.x = 0;
    }

    return;
}

void sobreposicaoPlayerGrama(Batalha* batalha, Player* player, int posicaoGramaX, int posicaoGramaY, Pokemon* pokemon, Posicoes* posicoes){
    srand(time(NULL));
    
    int numero;

    player->posicaoPlayer = (Rectangle){player->posicao.x * 4, (player->posicao.y + 16)* 4, (player->textura.width/4) * 4, ((player->textura.height/8))  * 4};
    Rectangle gramaPosicao = {posicaoGramaX * 4, posicaoGramaY * 4, 16 * 4, 16 * 4};

    if(CheckCollisionRecs(player->posicaoPlayer, gramaPosicao)){
        if(!pokemon->apareceuPokemon){
            numero = rand() % 10;

            if(numero == rand() % 10 || numero == rand() % 10){
                //carregaPokemon(pokemon);
                pokemon->desenhaPokemon = true;
                player->estadoJogo = 2;
                batalha->estadoBatalha = rand() % 1;
                if(batalha->estadoBatalha == 0){
                    batalha->contador = false;
                }else{
                    batalha->contador = true;
                }
            }
        }

        player->colisao = true;
        
    }//if
    
    return;
}



void descarregaPlayer(Player* player){
    UnloadTexture(player->textura);
    return;
}