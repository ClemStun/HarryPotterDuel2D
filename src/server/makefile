server : server_main.o init.o utils.o ../sdl/sdl.o
	gcc -o server server_main.o init.o utils.o ../sdl/sdl.o -lSDL2 -lSDL2_image -lSDL2_ttf
	
main_server.o : server_main.c
	gcc -o server_main.o -c server_main.c

../sdl/sdl.o : ../sdl/sdl.c
	gcc -o ../sdl/sdl.o -c ../sdl/sdl.c
	
init.o : init.c
	gcc -o init.o -c init.c
	
utils.o : utils.c
	gcc -o utils.o -c utils.c

clean:
	rm -rf *.o

