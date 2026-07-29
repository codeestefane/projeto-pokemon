#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "background.h"
#include "player.h"
#include "pokemon.h"
#include "global.h"
#include "batalha.h"
#include "aviso.h"
#include "backgroundMenu.h"
#include "teste.h"


int main(){
    ///////////////////////////////////////////////
    float escalaTela = 4;
    FILE* arquivoCSV;

    Player player;
    Background background;
    Posicoes posicoes;
    Pokemon pokemon;
    Dados* dadosPokemon;
    Aviso aviso;
    Batalha batalha;
    Cursor cursor;
    
    posicoes.posicaoGrama = NULL;
    posicoes.indice = 0;
    pokemon.desenhaPokemon = false;
    pokemon.aleatorizaPokemon = false;
    pokemon.apareceuPokemon = false;
    player.estadoJogo = 0;
    cursor.investida = true;
    cursor.posicaoCursor.y = 25;
    batalha.tamanhoFonteInvestida = 10;
    batalha.tamanhoFonteAtordoar = 8;
    batalha.ultimoTempo = 0;
    batalha.tempoPercorrido = 0;
    batalha.vidaPokemonAdversario = 20;
    batalha.vidaPokemonPlayer = 20;
    batalha.ataquePlayer = false;
    batalha.ataqueAdversario = false;
    player.genero = 1;
    //batalha.decrementoAdversario = -1;
    //batalha.decrementoPlayer = -1;

    aviso.frameBotao = 0;
    aviso.piscaBotao = false;
    batalha.contador = true;

    arquivoCSV = fopen("img/pokemon/csv/pokemons.csv", "r");

    if(arquivoCSV == NULL){
        perror("Erro ao abrir arquivo");
        exit(1);
    }
    
    fscanf(arquivoCSV, "%*[^\n]\n");
    dadosPokemon = (Dados*) malloc(721 * sizeof(Dados));

    for(int i = 0; i < 721; i++){
        fscanf(arquivoCSV, "%d ,%s ,%s ,%s ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%d ,%s ,%f ,%f ,%d", &dadosPokemon[i].numero, dadosPokemon[i].nome, dadosPokemon[i].tipo1, dadosPokemon[i].tipo2, &dadosPokemon[i].total, &dadosPokemon[i].hp, &dadosPokemon[i].ataque, &dadosPokemon[i].defesa, &dadosPokemon[i].ataqueEspecial, &dadosPokemon[i].defesaEspecial, &dadosPokemon[i].velocidade, &dadosPokemon[i].geracao, &dadosPokemon[i].lendario, dadosPokemon[i].cor, &dadosPokemon[i].altura, &dadosPokemon[i].peso, &dadosPokemon[i].taxaCaptura);
    }//for

    fclose(arquivoCSV);

    //salvaPokemonsPlanta(dadosPokemon, &pokemon);

    InitWindow(240 * escalaTela, 160 * escalaTela, "jogo");
    SetTargetFPS(60);

    carregarBackground(&background);
    carregaPokemon(&pokemon);
    carregaPokemonPlayer(&batalha);
    carregaPokemonPlayerFront(&batalha);
    carregaImagensAviso(&aviso, &pokemon);
    carregaTextureBatalha(&batalha, &pokemon, &cursor);
    carregaMenu();
    
    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(WHITE);

        switch(player.estadoJogo){
            //menu
            case 0:
                mainMenu(&player);
                break;
            //mapa
            case 1:
                identificaPosicoesBackground(&background, &posicoes, &player, &pokemon, escalaTela);
                atualizaPlayer(&player, escalaTela);
                //aleatorizaPokemon(&pokemon, &posicoes);
                //descobriuPokemon(&pokemon, &player);

                desenhaBackground(&batalha, &background, &posicoes, &player, &pokemon, escalaTela);
                desenhaPlayer(&player, escalaTela);
                break;
            //aviso de batalha
            case 2:

                aviso.frameBotao++;

                if(aviso.frameBotao >= 20){
                    aviso.frameBotao = 0;
                    aviso.piscaBotao = !aviso.piscaBotao;
                }

                ClearBackground(YELLOW);
                //desenhaBackgroundAviso();
                //desenhaAviso(&aviso, &pokemon);
                desenhaPokemonAdversario(&aviso, &pokemon);
                mensagemAviso(&aviso, &pokemon, dadosPokemon);
                desenhaBotao(&aviso, &player);
                break;
            
            case 3:
                desenhaBackgroundBatalha(&batalha);
                desenhaPokemonBatalha(&batalha, &pokemon);
                desenhaMenu(&batalha, &cursor);
                calculaBatalha(&cursor, &batalha, &player);
                verificaCursor(&cursor, &batalha);
                desenhaTexto(&cursor, &batalha, dadosPokemon, &pokemon);
                break;

            case 4:
                if(batalha.vidaPokemonAdversario <= batalha.vidaPokemonPlayer){
                    ClearBackground(GREEN);
                    desenhaPokemonPlayer(&batalha, &aviso, &pokemon);
                }else if(batalha.vidaPokemonPlayer <= 0){
                    ClearBackground(RED);
                    desenhaPokemonAdversario(&aviso, &pokemon);
                }

                aviso.frameBotao++;

                if(aviso.frameBotao >= 20){
                    aviso.frameBotao = 0;
                    aviso.piscaBotao = !aviso.piscaBotao;
                }

                mensagemAvisoFinal(&batalha, &aviso);
                desenhaBotaoFinal(&batalha, &aviso, &player, &pokemon);
                
                break;
        }//SWITCH
        
        EndDrawing();
    }//while
    
    descarregarBackground(&background);
    descarregaPlayer(&player);
    descarregaPokemon(&pokemon);
    descarregaAviso(&aviso, &pokemon);
    descarregaBatalha(&batalha, &cursor);
    descarregaPokemonPlayer(&batalha);
    descarregaMenu();
    //UnloadFont(fonte);
    CloseWindow();

    return 0;
}//main
