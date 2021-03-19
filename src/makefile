sdl_options = -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = ./client/main_client
OBJ = ./client/main_client.o ./player/move.o ./player/player.o ./sdl/sdl.o ./HUD/hud_ingame.o ./player/spell/expelliarmus.o ./player/spell/petrificus.o ./menus/menus.o

./client/main_client : $(OBJ)
	gcc -o $(BIN) $(OBJ) $(sdl_options) -lm -g

./client/main_client.o : ./client/main_client.c
	gcc -o ./client/main_client.o -c ./client/main_client.c

./player/move.o : ./player/move.c
	gcc -o ./player/move.o -c ./player/move.c

./player/spell/expelliarmus.o: ./player/spell/expelliarmus.c
	gcc -o ./player/spell/expelliarmus.o -c ./player/spell/expelliarmus.c

./player/spell/petrificus.o: ./player/spell/petrificus.c
	gcc -o ./player/spell/petrificus.o -c ./player/spell/petrificus.c

./player/player.o : ./player/player.c
	gcc -o ./player/player.o -c ./player/player.c

./sdl/sdl.o : ./sdl/sdl.c
	gcc -o ./sdl/sdl.o -c ./sdl/sdl.c

./HUD/hud_ingame.o : ./HUD/hud_ingame.c
	gcc -o ./HUD/hud_ingame.o -c ./HUD/hud_ingame.c

./menus/menus.o : ./menus/menus.c
	gcc -o ./menus/menus.o -c ./menus/menus.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
