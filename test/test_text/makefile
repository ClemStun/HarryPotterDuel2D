sdl_options = -lSDL2 -lSDL2_image -lSDL2_ttf

BIN = test_text
OBJ = test_text.o sdl.o

test_text : $(OBJ)
	gcc -o $(BIN) $(OBJ) $(sdl_options) -lm -g

test_text.o : test_text.c
	gcc -o test_text.o -c test_text.c

sdl.o : ../../src/sdl/sdl.c
	gcc -o sdl.o -c ../../src/sdl/sdl.c

all : $(BIN) $(OBJ)

clean:
	rm -rf *.o
