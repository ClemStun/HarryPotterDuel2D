sdl_options = -lSDL2 -lSDL2_image

BIN = ./client/main_client
OBJ = ./client/main_client.o ./player/move.o ./player/player.o ./sdl/sdl.o ./HUD/hud_ingame.o

./client/main_client : $(OBJ)
	gcc -o $(BIN) $(OBJ) $(sdl_options) -lm

./client/main_client.o : ./client/main_client.c
	gcc -o ./client/main_client.o -c ./client/main_client.c

./player/move.o : ./player/move.c
	gcc -o ./player/move.o -c ./player/move.c

./player/player.o : ./player/player.c
	gcc -o ./player/player.o -c ./player/player.c

./sdl/sdl.o : ./sdl/sdl.c
	gcc -o ./sdl/sdl.o -c ./sdl/sdl.c

./HUD/hud_ingame.o : ./HUD/hud_ingame.c
	gcc -o ./HUD/hud_ingame.o -c ./HUD/hud_ingame.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
