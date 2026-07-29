#include <raylib.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
    Texture2D textura;
    Vector2 posicao1;
    Vector2 posicao2;
    Vector2 posicao3;
    float velocidade; 
}Background;

void carregarBackground(Background background[]);
void descarregarBackground(Background background[]);
void desenhaBackground(Background background[], float escalaTela);
void atualizaBackground(Background background[]);

int main(){
    float escalaTela = 5;
    Background background[3];

    InitWindow(240 * escalaTela, 160 * escalaTela, "jogo");
    SetTargetFPS(60);

    carregarBackground(background);
    
    while(!WindowShouldClose()){
        atualizaBackground(background);

        BeginDrawing();
        ClearBackground(WHITE);
        desenhaBackground(background, escalaTela);
        EndDrawing();
    }//while

    descarregarBackground(background);
    CloseWindow();

    return 0;
}//main

void carregarBackground(Background background[]){
    for(int i = 0; i < 3; i++){
        background[i].textura = LoadTexture(TextFormat("img/menu/background%d.png", i+1));
        background[i].posicao1 = (Vector2){-(background[i].textura.width), 0};
        background[i].posicao2 = (Vector2){0, 0};
        background[i].posicao3 = (Vector2){(background[i].textura.width), 0};
    }

    background[0].posicao1.y = 25;
    background[1].posicao2.y = 25;
    background[2].posicao3.y = 25;

    background[0].velocidade = 0.2;
    background[1].velocidade = 0.3;
    background[2].velocidade = 0.4;
    return;
}

void descarregarBackground(Background background[]){
    for(int i = 0; i < 3; i++){
       UnloadTexture(background[i].textura);
    }

    return;
}

void desenhaBackground(Background background[], float escalaTela){
    for(int i = 0; i < 3; i++){
        /*DrawTexturePro(background[i].textura,
         (Rectangle){0, 0, background[i].textura.width, background[i].textura.height},
         (Rectangle){background[i].posicao1.x * escalaTela, background[i].posicao1.y * escalaTela, background[i].textura.width * escalaTela, background[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);*/

         DrawTexturePro(background[i].textura,
         (Rectangle){0, 0, background[i].textura.width, background[i].textura.height},
         (Rectangle){(background[i].posicao2.x) * escalaTela, background[i].posicao2.y * escalaTela, background[i].textura.width * escalaTela, background[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);

         DrawTexturePro(background[i].textura,
         (Rectangle){0, 0, background[i].textura.width, background[i].textura.height},
         (Rectangle){(background[i].posicao3.x) * escalaTela, background[i].posicao3.y * escalaTela, background[i].textura.width * escalaTela, background[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);
    }

    return;
}

void atualizaBackground(Background background[]){
    for(int i = 0; i < 3; i++){
        background[i].posicao1.x += background[i].velocidade * 5;
        background[i].posicao2.x += background[i].velocidade * 5;
        background[i].posicao3.x += background[i].velocidade * 5;


        if(background[i].posicao1.x >= 240){
            background[i].posicao1.x = -(background[i].textura.width);
        }

        if(background[i].posicao2.x >= 240){
            background[i].posicao2.x = -(background[i].textura.width);
        }
        if(background[i].posicao3.x >= 240){
            background[i].posicao3.x = -(background[i].textura.width);
        }
    }

    return;
}