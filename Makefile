# Verifica o sistema operacional
ifdef OS
  OS := $(strip $(OS))
else
  OS := $(strip $(shell uname))
endif

ifeq ($(OS),Windows_NT)
	export PATH := C:/raylib/w64devkit/bin:$(PATH)
	INCLUDE = -I./include/ -L./libwin
	EXTRA_FLAGS = -Wall -Wextra -std=c99 -Wno-missing-braces -lraylib -lm -lopengl32 -lgdi32 -lwinmm
	BIN =./pokemon.exe
	RM = del /Q /F
else
	INCLUDE=-I./include/ -L./lib
	EXTRA_FLAGS = -Wall -Wextra -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	BIN =./pokemon
	RM = rm -f
endif

SRC=./src/*.c

all:
	gcc $(SRC) -g $(EXTRA_FLAGS) $(INCLUDE) -o $(BIN)

run:
	$(BIN)

config:
	export LD_LIBRARY_PATH=./lib/
	sudo ldconfig

clean:
	$(RM) $(BIN)

valgrind:
	valgrind --tool=memcheck --leak-check=full --track-origins=yes --show-leak-kinds=all --show-reachable=yes ./$(BIN)