test_sort: ../src/player/spell/petrificus.o ./testsort.o ../src/player/player.o
	gcc ../src/player/spell/petrificus.o testsort.o ../src/player/player.o -o ./testsort -lm -lSDL2

test_sort.o: ./testsort.c
	gcc ./testsort.c -c testsort.o

petrificus.o: ../src/player/spell/petrificus.c
	gcc ../src/player/spell/petrificus.c -c petrificus.o

player.o: ../src/player/player.c
	gcc ../src/player/player.c -c player.o

clean:
	rm -rf *.o