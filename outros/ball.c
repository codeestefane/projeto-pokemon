#include <raylib.h>
#include <time.h>
#include <stdlib.h>

typedef struct{
    Vector2 position;
    Vector2 speed;
    int isJumping;
    Color color;
} Ball;

int main(){
    //cria janela p/ desenho (largura, altura, título)
    InitWindow(600, 600, "teste");
    SetTargetFPS(60);
    Ball ball[1000];

    srand(time(NULL));

    for(int i = 0; i < 1000; i++){
        ball[i].position = (Vector2){rand()%580, rand()%580};
        ball[i].speed = (Vector2){0, 0};
        ball[i].isJumping = 0;
        ball[i].color = (Color){rand()%255, rand()%255, rand()%255, 255};
    }//for

    //usa o while para evitar que a janela seja fechada
    while(!WindowShouldClose()){

        for(int i = 0; i < 1000; i++){
            //no momento em que você clica
            if(IsKeyPressed(KEY_SPACE)){
                ball[i].speed.y = -(rand()%20 + 10);
                ball[i].isJumping = 1;
            }//if

            //enquanto estiver apertado
            if(IsKeyDown(KEY_LEFT)){
                ball[i].speed.x = -5;
            }

            if(IsKeyDown(KEY_RIGHT)){
                ball[i].speed.x = 5;
            }

            ball[i].speed.y += 0.2;
            ball[i].position.y += ball[i].speed.y;
            ball[i].position.x += ball[i].speed.x;

            if(ball[i].position.y >= 580){
                ball[i].position.y = 580;
                ball[i].isJumping = 1;
                ball[i].speed.y *= -0.8;
            }//if
            
            if(ball[i].position.x >= 580){
                ball[i].position.x = 580;
            }//if
            
            if(ball[i].position.x <= 20){
                ball[i].position.x = 20;
            }//if
        }//for

        BeginDrawing();//inicia desenho
        ClearBackground(BLACK); //limpa tudo o que foi feito na tela e aplica uma cor
        for(int i = 0; i < 1000; i++){
            DrawCircle(ball[i].position.x, ball[i].position.y, 1, ball[i].color);
        }//for
        //DrawRectangle(x, y, 50, 50, BLUE);
        EndDrawing();//finaliza desenho
    }//while

    CloseWindow();

    return 0;
}//main


/*
#segundo arquivo: o que não funciona

export PATH := C:/raylib/w64devkit/bin:$(PATH)

CC = gcc #compilador
EXE = main.exe
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces -g #parâmetros de compilação
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm #bibliotecas que serão utilizadas

SRCS = $(wildcard src/.c) #salva todos os arquivos de código fonte na pasta src
HDRS = $(wildcard src/.h) #salva todos os cabeçalhos na pasta src

#atribui os valores das variáveis na linha de comando para compilar -> make
$(EXE):
    $(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(HDRS) $(LIBS)

#limpa a compilação -> make clean
clean:
    rm -f $(EXE) 

#executa a compilação -> make run
run:
    ./$(EXE)

#define os comandos
.PHONY: clean run



export PATH := C:/raylib/w64devkit/bin:$(PATH)

CC = gcc
EXE = main.exe
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces
LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
INCLUDES_DIR = -Iinclude
LIBS_DIR = -Llib

SRCS = $(wildcard src/*.c)
HDRS = $(wildcard src/*.h)

$(EXE):
	$(CC) -o $(EXE) $(CFLAGS) $(SRCS) $(HDRS) $(LIBS)

clean:
	rm -f $(EXE)

.PHONY: clean*/