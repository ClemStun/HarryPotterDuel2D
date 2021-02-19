server : server_main.o init.o utils.o
	gcc -o server server_main.o init.o utils.o
	
main_server.o : server_main.c
	gcc -o server_main.o -c server_main.c
	
init.o : init.c
	gcc -o init.o -c init.c
	
utils.o : utils.c
	gcc -o utils.o -c utils.c

clean:
	rm -rf *.o

