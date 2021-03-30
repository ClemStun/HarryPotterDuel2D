sdl_options = -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = ./main
OBJ = ./obj/main_client.o ./obj/move.o ./obj/player.o ./obj/sdl.o ./obj/hud_ingame.o ./obj/expelliarmus.o ./obj/petrificus.o ./obj/menu.o ./obj/game.o ./obj/waiting.o ./obj/train.o

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

./obj/menu.o : ./src/states/menu.c
	gcc -o ./obj/menu.o -c ./src/states/menu.c

./obj/game.o : ./src/states/game.c
	gcc -o ./obj/game.o -c ./src/states/game.c

./obj/train.o : ./src/states/train.c
	gcc -o ./obj/train.o -c ./src/states/train.c

./obj/waiting.o : ./src/states/waiting.c
	gcc -o ./obj/waiting.o -c ./src/states/waiting.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
