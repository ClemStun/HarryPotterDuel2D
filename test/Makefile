test_sort: ../src/player/spell/expelliarmus.o ./testsort.o
	gcc ../src/player/spell/expelliarmus.o testsort.o -o ./testsort -lm

test_sort.o: ./testsort.c
	gcc ./testsort.c -c testsort.o

expelliarmus.o: ../src/player/spell/expelliarmus.c
	gcc ../src/player/spell/expelliarmus.c -c expelliarmus.o -lm