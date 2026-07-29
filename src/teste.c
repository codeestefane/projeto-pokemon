
///////////////////////////////////////////////////////////

#include <raylib.h>
#include <time.h>
#include <stdlib.h>
#include "backgroundMenu.h"
#include "teste.h"
#include "player.h"
#include "global.h"

        static float escalaTela = 4;

        static int selectedOption;//menu_opções
        static char *menuOptions[4] = {"start", "pokedex", "export data", "exit"};//"start-0", "pokedex-1", "export data-2", "exit-3" (menu)
        
        static int frame_largura = 166; //logo
        static int frame_altura = 56; //logo

        static int frameAtual = 0; //logo
        static float tempoFrame = 0.0f; //logo
        static float tempo_max_frame = 0.09f; //logo

        static int escolha = 0; // 0 for boy, 1 for girl
        static int avatar_genero = -1;//armazena a escolha

        static char nome[200] = { };//armazena nome

        static int largura_tela = 240;
        static int altura_tela = 160;

        static int estado_jogo = -1;

        static BackgroundMenu backgroundMenu[3];

        static Font fonte;
        static Font fonte2;
        static Texture2D texturaQuadroMenu;
        static Texture2D setaMenu;
        static Texture2D logo;
        static Texture2D boy;
        static Texture2D girl;
        static Texture2D BackgroundMenu_avatar_escolha;
        static Texture2D caixa_nome;
        static int ultimaTecla;
        static int teclaAtual;
        static int entra;
        //static float enterCooldown = 9.0f; // Cooldown para o ENTER //MEXIDO
        //static int enter = 0;

void carregaMenu(){
    carregarBackgroundMenu(backgroundMenu);
    fonte = LoadFont("recursos/fonts/pokemon_fire_red_70.ttf");
    fonte2 = LoadFont("recursos/fonts/pokemon_fire_red_32.ttf");
    texturaQuadroMenu = LoadTexture("recursos/menu/menuOptions.png");//menu
    setaMenu = LoadTexture("recursos/menu/pointer.png");
    logo = LoadTexture("recursos/menu/logo.png");
    boy = LoadTexture("recursos/menu/boy_escolha.png");
    girl = LoadTexture("recursos/menu/girl_escolha.png");
    BackgroundMenu_avatar_escolha = LoadTexture("recursos/menu/background4.png");
    caixa_nome = LoadTexture("recursos/menu/nome_editado.png");

            selectedOption = 0;//menu_opções

        frameAtual = 0; //logo
        tempoFrame = 0.0f; //logo
        tempo_max_frame = 0.09f; //logo

        escolha = 0; // 0 for boy, 1 for girl
        avatar_genero = -1;//armazena a escolha

        //nome[200] = { };//armazena nome

        estado_jogo = -1;
        entra = 0;
}

void atualizaLogoMenuEOpcoes(BackgroundMenu backgroundMenu[], int *selectedOption, int *estado_jogo) {
    // Atualiza o fundo do menu
    atualizaBackgroundMenu(backgroundMenu);
    
    // Controla o tempo do logo
    static float tempoFrame = 0.0f;
    static int frameAtual = 0;
    static float tempo_max_frame = 0.09f;
    static const int totalFrames = 5;

    tempoFrame += GetFrameTime();
    if (tempoFrame >= tempo_max_frame) {
        tempoFrame = 0.0f; // Reseta o tempo
        if (frameAtual == totalFrames) {
            frameAtual = 0; // Reinicia para o primeiro frame
        } else {
            frameAtual++; // Troca para o próximo frame
        }

        if (frameAtual == 0) {
            tempo_max_frame = 2.5f; // Logo mais tempo no frame 0
        } else {
            tempo_max_frame = 0.09f; // Tempo padrão para os outros frames
        }
    }

    // Controle de navegação do menu com as setas
    if (IsKeyPressed(KEY_UP)) {
        (*selectedOption)--;
        if (*selectedOption < 0) {
            *selectedOption = 3; // Vai para a última opção ao sair da primeira
        }
    } else if (IsKeyPressed(KEY_DOWN)) {
        (*selectedOption)++;
        if (*selectedOption > 3) {
            *selectedOption = 0; // Vai para a primeira opção ao sair da última
        }
    }

    // Controle da seleção do menu com ENTER
    if (IsKeyPressed(KEY_ENTER)) {
        switch (*selectedOption) {
            case 0:
                *estado_jogo = 0; // Vai para a escolha do avatar
                break;
            case 1:
                // Ação para "pokedex"
                break;
            case 2:
                // Ação para "export data"
                break;
            case 3:
                CloseWindow(); // Fecha o jogo
                break;
        }
       // enterCooldown = 9.0f; // Impede que ENTER seja detectado novamente por 0.3 segundos
        //printf("Entrou");
    }

    // Botão que retorna ao menu inicial
    if (IsKeyPressed(KEY_ONE)) {
        *estado_jogo = -1; // Retorna ao menu principal
    }
}


void mainMenu(Player* player){
    // if (enterCooldown > 0) {
    //     enterCooldown -= GetFrameTime(); // Reduz o cooldown com base no tempo do frame
    //     printf("cooldown: %f", enterCooldown);
    //     if(enterCooldown < 0){
    //         enter = 0;
    //     }
    // } //MEXIDO////////////////////////////////////////////////////////////////////////
    if(IsKeyReleased(KEY_ENTER) && entra < 2){
        entra++;
    }

    // Loop principal
        // Atualização e renderização aqui
        ultimaTecla = GetKeyPressed();
        teclaAtual = GetKeyPressed();
         // Exibe o código da última tecla pressionada
        // Menu inicial (atualiza)_________________________________________________________________________________________________
        atualizaLogoMenuEOpcoes(backgroundMenu, &selectedOption, &estado_jogo); // Função que atualiza logo e menu

        // Menu incial(fim)___________________________________________________________________________________________________________
        //printf("Estado jogo: %d\n", estado_jogo);
        // Escolha avatar (Atualiza)______________________________________________________________________________________________
        setbuf(stdin, NULL);
        if (IsKeyPressed(KEY_LEFT))
        {
            ultimaTecla = GetKeyPressed();
            escolha = 0;
        }
        else if (IsKeyPressed(KEY_RIGHT))
        {
            ultimaTecla = GetKeyPressed();
            escolha = 1;
            // printf("O valor de cooldown é: %f\n", enterCooldown);
        }
       else if (IsKeyPressed(KEY_ENTER) && estado_jogo == 0 && entra == 1) {
            avatar_genero = escolha;
            estado_jogo = 1;
            player->genero = avatar_genero;
        }
        // Escolha avatar(fim)_________________________________________________________________________________________________________
        
        // Pede nome(atualiza)

        //BeginDrawing();

        // Limpar o fundo
        ClearBackground(WHITE);

        // Lógica baseada no estado
        switch (estado_jogo) {
            case -1:
                // Desenho menu inicial
                desenhaBackgroundMenu(backgroundMenu, escalaTela);
                
                DrawTexturePro(texturaQuadroMenu,
                    (Rectangle) {0, 0, 104, 77},
                    (Rectangle) {600 * 0.8, 560 * 0.8, 104 * escalaTela, 77 * escalaTela},
                    (Vector2) {(104 * escalaTela)/2, (77*escalaTela)/2},
                    0,
                    WHITE);

                for (int i = 0; i < 4; i++)
                {
                    Vector2 size = MeasureTextEx(fonte, menuOptions[i], 80 * 0.8, 4);

                    if (i == selectedOption)
                    {
                        DrawTexturePro(setaMenu,
                            (Rectangle) {0, 0, 6, 10},
                            (Rectangle) {(600*0.8-(size.x/2)-(6 * escalaTela)), 460*0.8 + 60 * i, 6 * escalaTela, 10 * escalaTela},
                            (Vector2) {(6 * escalaTela)/2, (10 * escalaTela)/2},
                            0,
                            WHITE);

                        DrawTextPro(
                            fonte, 
                            TextFormat("%s", menuOptions[i]),
                            (Vector2){ 600 * 0.8, 450 * 0.8 + 60 * i}, //a posição na tela onde você deseja desenhar o texto.
                            (Vector2){size.x/2,size.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                            0, //a rotação do texto em graus.
                            80 * 0.8, //tamaho
                            4, //spacing
                            GRAY
                        );
                    }
                    else
                    {
                        DrawTextPro(
                            fonte,
                            TextFormat("%s", menuOptions[i]),
                            (Vector2){ 600 * 0.8, 450 * 0.8 + 60 * i},
                            (Vector2){size.x/2,size.y/2},
                            0,
                            80 * 0.8,
                            4,
                            GRAY
                        );
                    }
                }

                // Definir as coordenadas e dimensões do frame atual //logo
                Rectangle origem_retangulo = { 0, frameAtual * frame_altura, frame_largura, frame_altura };
                Rectangle destino_retangulo = { 
                    (largura_tela*escalaTela) / 2 - (frame_largura*escalaTela) / 2, 
                    (altura_tela*escalaTela) / 5 - (frame_altura*escalaTela) / 2, 
                    frame_largura*escalaTela, 
                    frame_altura*escalaTela};

                // Desenhar o frame atual
                DrawTexturePro(logo, origem_retangulo, destino_retangulo, (Vector2){ 0, 0 }, 0.0f, WHITE);
                        // desenho menu incial (fim)
            break;
            
            case 0:
                DrawTexturePro(BackgroundMenu_avatar_escolha,
                    (Rectangle){0, 0, BackgroundMenu_avatar_escolha.width, BackgroundMenu_avatar_escolha.height},
                    (Rectangle){0, 0, BackgroundMenu_avatar_escolha.width * escalaTela, BackgroundMenu_avatar_escolha.height * escalaTela},
                    (Vector2){0, 0},
                    0,
                    WHITE);

                if (escolha == 0)
                {
                    DrawTexturePro(boy, 
                    (Rectangle){0, 0, boy.width, boy.height}, 
                    (Rectangle){(largura_tela*escalaTela)/4 - (boy.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (boy.height*escalaTela)/2, boy.width*escalaTela, boy.height*escalaTela},
                    (Vector2) {0,0},
                    0,
                    WHITE);
                    DrawTexturePro(girl,
                    (Rectangle){0, 0, girl.width, girl.height},
                    (Rectangle){(largura_tela*escalaTela)*3/4 - (girl.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (girl.height*escalaTela)/2, girl.width*escalaTela, girl.height*escalaTela},
                    (Vector2){0,0},
                    0,
                    GRAY);
                }
                else
                {
                    DrawTexturePro(boy, 
                    (Rectangle){0, 0, boy.width, boy.height}, 
                    (Rectangle){(largura_tela*escalaTela)/4 - (boy.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (boy.height*escalaTela)/2, boy.width*escalaTela, boy.height*escalaTela},
                    (Vector2) {0,0},
                    0,
                    GRAY);
                    DrawTexturePro(girl,
                    (Rectangle){0, 0, girl.width, girl.height},
                    (Rectangle){(largura_tela*escalaTela)*3/4 - (girl.width*escalaTela)/2, (altura_tela*escalaTela)/2 - (girl.height*escalaTela)/2, girl.width*escalaTela, girl.height*escalaTela},
                    (Vector2){0,0},
                    0,
                    WHITE);
                }

                Vector2 tamanho_fonte2 = MeasureTextEx(fonte2, "Escolha Seu Avatar:", 55, 3.5);

                DrawTextPro(
                    fonte2, 
                    "Escolha Seu Avatar:",
                    (Vector2){(largura_tela*escalaTela/2)+3, ((altura_tela*escalaTela)*26/30)+3}, //a posição na tela onde você deseja desenhar o texto.
                    (Vector2){tamanho_fonte2.x/2,tamanho_fonte2.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                    0, //a rotação do texto em graus.
                    55, //tamaho
                    3.5, //spacing
                    DARKGRAY
                );

                DrawTextPro(
                    fonte2, 
                    "Escolha Seu Avatar:",
                    (Vector2){largura_tela*escalaTela/2, (altura_tela*escalaTela)*26/30}, //a posição na tela onde você deseja desenhar o texto.
                    (Vector2){tamanho_fonte2.x/2,tamanho_fonte2.y/2}, //o ponto de origem do texto. Isso afeta a rotação e o alinhamento do texto.
                    0, //a rotação do texto em graus.
                    55, //tamaho
                    3.5, //spacing
                    WHITE
                );

            break;
            case 1:
                player->estadoJogo = 1;
                carregaPlayer(player);
                break;
                //CloseWindow();
                // DrawTexturePro(BackgroundMenu_avatar_escolha,
                //     (Rectangle){0, 0, BackgroundMenu_avatar_escolha.width, BackgroundMenu_avatar_escolha.height},
                //     (Rectangle){0, 0, BackgroundMenu_avatar_escolha.width * escalaTela, BackgroundMenu_avatar_escolha.height * escalaTela},
                //     (Vector2){0, 0},
                //     0,
                //     WHITE);
                
                // DrawTexturePro(caixa_nome,
                //     (Rectangle){0, 0, caixa_nome.width, caixa_nome.height},
                //     (Rectangle){(largura_tela*escalaTela)/2, (altura_tela*escalaTela)/2, caixa_nome.width*escalaTela, caixa_nome.height*escalaTela},
                //     (Vector2){caixa_nome.width*escalaTela/2,caixa_nome.height*escalaTela/2},
                //     0,
                //     WHITE);


            default:
                break;
        }

        // Outras operações de desenho aqui

        //EndDrawing();


    return;
}
//Mudar barra de espaço
//Colocar para pegar

void descarregaMenu(){
    descarregarBackgroundMenu(backgroundMenu);
    UnloadFont(fonte);
    UnloadFont(fonte2);
    UnloadTexture(texturaQuadroMenu);
    UnloadTexture(setaMenu);
    UnloadTexture(logo);
    UnloadTexture(boy);
    UnloadTexture(girl);
}