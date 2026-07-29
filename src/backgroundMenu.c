#include "backgroundMenu.h"
#include <stdio.h>

void carregarBackgroundMenu(BackgroundMenu backgroundMenu[]){
    for(int i = 0; i < 3; i++){
        backgroundMenu[i].textura = LoadTexture(TextFormat("img/menu/background%d.png", i+1));
        backgroundMenu[i].posicao1 = (Vector2){-(backgroundMenu[i].textura.width), 0};
        backgroundMenu[i].posicao2 = (Vector2){0, 0};
    }
        
    backgroundMenu[2].posicao1.y = 25;
    backgroundMenu[2].posicao2.y = 25;

    backgroundMenu[0].velocidade = 0.2;
    backgroundMenu[1].velocidade = 0.8;
    backgroundMenu[2].velocidade = 1.2;
    return;
}

void descarregarBackgroundMenu(BackgroundMenu backgroundMenu[]){
    for(int i = 0; i < 3; i++){
       UnloadTexture(backgroundMenu[i].textura);
    }
    return;
}

void desenhaBackgroundMenu(BackgroundMenu backgroundMenu[], float escalaTela){
    for(int i = 0; i < 3; i++){
        DrawTexturePro(backgroundMenu[i].textura,
         (Rectangle){0, 0, backgroundMenu[i].textura.width, backgroundMenu[i].textura.height},
         (Rectangle){backgroundMenu[i].posicao1.x * escalaTela, backgroundMenu[i].posicao1.y * escalaTela, backgroundMenu[i].textura.width * escalaTela, backgroundMenu[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);

         DrawTexturePro(backgroundMenu[i].textura,
         (Rectangle){0, 0, backgroundMenu[i].textura.width, backgroundMenu[i].textura.height},
         (Rectangle){(backgroundMenu[i].posicao2.x) * escalaTela, backgroundMenu[i].posicao2.y * escalaTela, backgroundMenu[i].textura.width * escalaTela, backgroundMenu[i].textura.height * escalaTela},
         (Vector2){0, 0},
         0,
         WHITE);
    }
    return;
}

void atualizaBackgroundMenu(BackgroundMenu backgroundMenu[]){
    for(int i = 0; i < 3; i++){
        backgroundMenu[i].posicao1.x -= backgroundMenu[i].velocidade;
        backgroundMenu[i].posicao2.x -= backgroundMenu[i].velocidade;

        if(backgroundMenu[i].posicao1.x <= -(backgroundMenu[i].textura.width)){
            backgroundMenu[i].posicao1.x = (backgroundMenu[i].posicao2.x + backgroundMenu[i].textura.width);
        }

        if(backgroundMenu[i].posicao2.x <= -(backgroundMenu[i].textura.width)){
            backgroundMenu[i].posicao2.x = (backgroundMenu[i].posicao1.x + backgroundMenu[i].textura.width);
        }
    }
    return;
}