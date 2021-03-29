sdl_options = -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = ./main
OBJ = ./obj/main_client.o ./obj/move.o ./obj/player.o ./obj/sdl.o ./obj/hud_ingame.o ./obj/expelliarmus.o ./obj/petrificus.o ./obj/menus.o

./main : $(OBJ)
	gcc -o $(BIN) $(OBJ) $(sdl_options) -lm -g

./obj/main_client.o : ./src/client/main_client.c
	gcc -o ./obj/main_client.o -c ./src/client/main_client.c

./obj/move.o : ./src/player/move.c
	gcc -o ./obj/move.o -c ./src/player/move.c

./obj/expelliarmus.o: ./src/player/spell/expelliarmus.c
	gcc -o ./obj/expelliarmus.o -c ./src/player/spell/expelliarmus.c

./obj/petrificus.o: ./src/player/spell/petrificus.c
	gcc -o ./obj/petrificus.o -c ./src/player/spell/petrificus.c

./obj/player.o : ./src/player/player.c
	gcc -o ./obj/player.o -c ./src/player/player.c

./obj/sdl.o : ./src/sdl/sdl.c
	gcc -o ./obj/sdl.o -c ./src/sdl/sdl.c

./obj/hud_ingame.o : ./src/HUD/hud_ingame.c
	gcc -o ./obj/hud_ingame.o -c ./src/HUD/hud_ingame.c

./obj/menus.o : ./src/menus/menus.c
	gcc -o ./obj/menus.o -c ./src/menus/menus.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
