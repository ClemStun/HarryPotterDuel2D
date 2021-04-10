sdl_options = -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = test_svg
OBJ = test_svg.o sdl.o player.o trait_donnees.o

test_svg : $(OBJ)
	gcc -o $(BIN) $(OBJ) $(sdl_options) -lm -g

test_svg.o : test_svg.c
	gcc -o test_svg.o -c test_svg.c

sdl.o : ../../src/sdl/sdl.c
	gcc -o sdl.o -c ../../src/sdl/sdl.c

player.o : ../../src/player/player.c
	gcc -o player.o -c ../../src/player/player.c

trait_donnees.o : ../../src/trait_donnees/trait_donnees.c
	gcc -o trait_donnees.o -c ../../src/trait_donnees/trait_donnees.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
