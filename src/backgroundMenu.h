#include <raylib.h>

#ifndef BACKGROUNDMENU_H
#define BACKGROUNDMENU_H

typedef struct{
    Texture2D textura;
    Vector2 posicao1;
    Vector2 posicao2;
    float velocidade; 
} BackgroundMenu;

void carregarBackgroundMenu(BackgroundMenu backgroundMenu[]);
void descarregarBackgroundMenu(BackgroundMenu backgroundMenu[]);
void desenhaBackgroundMenu(BackgroundMenu backgroundMenu[], float escalaTela);
void atualizaBackgroundMenu(BackgroundMenu backgroundMenu[]);

#endif