#include <raylib.h>
#include <stdlib.h>

typedef struct{
    Texture2D textura;
    Vector2 posicao;
    float velocidade;
    float tempoPercorrido;
    float ultimoTempo;
    int frameX;
    int frameY;
} Player;

void carregaPlayer(Player* player);
void atualizaPlayer(Player* player);
void desenhaPlayer(Player* player, float escalaTela);
void descarregaPlayer(Player* player);

int main(){
    float escalaTela = 4;
    Player player;
    
    player.frameX = 0;
    player.frameY = 0;

    InitWindow(240 * escalaTela, 160 * escalaTela, "player");
    SetTargetFPS(60);

    carregaPlayer(&player);

    player.tempoPercorrido = 0;
    player.ultimoTempo = 0;
    

    while(WindowShouldClose){
        atualizaPlayer(&player);

        BeginDrawing();
        ClearBackground(WHITE);

        desenhaPlayer(&player, escalaTela);

        EndDrawing();
    }

    descarregaPlayer(&player);
    CloseWindow();

    return 0;
}//main

void carregaPlayer(Player* player){
    player->textura = LoadTexture("img/player/0/walk.png");
    player->posicao = (Vector2){0, 0};
    player->velocidade = 0.5;

    return;
}

void atualizaPlayer(Player* player){
    int tempo;
    player->tempoPercorrido += GetFrameTime() * 1000;
    tempo = player->tempoPercorrido - player->ultimoTempo;

    if(tempo >= 150){
        player->ultimoTempo = player->tempoPercorrido;
        player->frameX++;
        if(player->frameX >= 4){
            player->frameX = 0;
        }
    }

    if(IsKeyDown(KEY_W)){
        player->posicao.y -= player->velocidade;
        player->frameY = 1;
    }else if(IsKeyDown(KEY_S)){
        player->posicao.y += player->velocidade;
        player->frameY = 0;
    }else if(IsKeyDown(KEY_A)){
        player->posicao.x -= player->velocidade;
        player->frameY = 2;
    }else if(IsKeyDown(KEY_D)){
        player->posicao.x += player->velocidade;
        player->frameY = 3;
    }else{
        /*caso esteja parado*/
    }

}

void desenhaPlayer(Player* player, float escalaTela){
    
    DrawTexturePro(player->textura, 
    (Rectangle){(player->posicao.x/4) * player->frameX, (player->posicao.y/4) * player->frameY, (player->textura.width/4), (player->textura.height/4)},
    (Rectangle){player->posicao.x * escalaTela, player->posicao.y * escalaTela, (player->textura.width/4) * escalaTela, (player->textura.height/4) * escalaTela},
    (Vector2){0, 0},
    0,
    WHITE);
}

void descarregaPlayer(Player* player){
    UnloadTexture(player->textura);
    return;
}


