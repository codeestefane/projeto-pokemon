#include "background.h"

void carregarBackground(Background* background){
    
    background->textura = LoadTexture(TextFormat("img/map/bg_floresta.png"));
    background->posicao = (Vector2){0, 0};

    return;
}

void descarregarBackground(Background* background){
    UnloadTexture(background->textura);

    return;
}

/*    
    int map[10][15] = {
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 4, 9, 4, 9, 4, 9, 4, 9, 31, 9, 9, 9, 9},
        {9, 9, 9, 4, 9, 9, 9, 4, 9, 9, 9, 9, 9, 9, 9},
        {9, 9, 9, 9, 9, 4, 9, 4, 9, 9, 9, 4, 9, 9, 9},
        {9, 9, 9, 9, 4, 9, 9, 9, 9, 9, 9, 9, 4, 9, 9},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {4, 16, 17, 17, 18, 9, 31, 9, 9, 9, 9, 9, 9, 9, 9},
        {4, 22, 23, 23, 24, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9},
        {9, 26, 23, 23, 35, 9, 4, 9, 9, 4, 4, 4, 4, 4, 4}
    };
*/

void identificaPosicoesBackground(Background* background, Posicoes* posicoes, Player* player, Pokemon* pokemon, float escalaTela){
    posicoes->qtdGrama = 0;
    
    int map[10][15] = {
        {9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        {9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4},
        {9, 9, 4, 9, 4, 9, 4, 9, 4, 9, 31, 9, 9, 9, 4},
        {4, 9, 9, 4, 9, 9, 9, 4, 9, 9, 9, 9, 9, 9, 4},
        {4, 9, 9, 9, 9, 4, 9, 4, 9, 9, 9, 4, 9, 9, 4},
        {4, 9, 9, 9, 4, 9, 9, 9, 9, 9, 9, 9, 4, 9, 4},
        {4, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4},
        {4, 16, 17, 17, 18, 9, 31, 9, 9, 9, 9, 9, 9, 9, 4},
        {4, 22, 23, 23, 24, 9, 9, 9, 9, 9, 9, 9, 9, 9, 4},
        {4, 26, 23, 23, 35, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}
    };

    for(int i = 0; i < 10; i++){
        for(int j = 0; j < 15; j++){
            background->map[i][j] = map[i][j];
        }
    }

    for(int y = 0; y < 10; y++){
        for(int x = 0; x < 15; x++){

            int quadradinhoID = background->map[y][x];

            background->quadradinhoX = quadradinhoID % 11;
            background->quadradinhoY = quadradinhoID / 11;

            if(background->quadradinhoX == 4 || background->quadradinhoY == 3){
                posicoes->qtdGrama++;
                posicoes->posicaoGrama = (Rectangle*) realloc(posicoes->posicaoGrama, posicoes->qtdGrama * sizeof(Rectangle));
                posicoes->posicaoGrama[posicoes->qtdGrama - 1] = (Rectangle){x * 16, y * 16, 16, 16};
            }//if
        }//for
    }//for

    return;
}

void desenhaBackground(Batalha* batalha, Background* background, Posicoes* posicoes, Player* player, Pokemon* pokemon, float escalaTela){
    
    for(int y = 0; y < 10; y++){
        for(int x = 0; x < 15; x++){

            int quadradinhoID = background->map[y][x];

            background->quadradinhoX = quadradinhoID % 11;
            background->quadradinhoY = quadradinhoID / 11;

            DrawTexturePro(background->textura,
                (Rectangle){background->quadradinhoX * 16, background->quadradinhoY * 16, 16, 16},
                (Rectangle){x * 16 * escalaTela, y * 16 * escalaTela, 16 * escalaTela, 16 * escalaTela},
                (Vector2){0, 0}, 0, WHITE);

            if(background->quadradinhoX == 4 || background->quadradinhoX == 3){
                sobreposicaoPlayerGrama(batalha, player, x * 16, y * 16, pokemon, posicoes);
            }//if
        }//for
    }//for

    return;
}