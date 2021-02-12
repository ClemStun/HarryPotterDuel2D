sdl_options = -lSDL2 -lSDL2_image

./client/main_client : ./client/main_client.o ./sdl/sdl.o ./player/move.o
	gcc -o ./client/main_client ./client/main_client.o ./sdl/sdl.o ./player/move.o $(sdl_options) -lm
	
./client/main_client.o : ./client/main_client.c
	gcc -o ./client/main_client.o -c ./client/main_client.c
	
./player/move.o : ./player/move.c
	gcc -o ./player/move.o -c ./player/move.c
	
./sdl/sdl.o : ./sdl/sdl.c
	gcc -o ./sdl/sdl.o -c ./sdl/sdl.c

clean:
	rm -rf *.o

