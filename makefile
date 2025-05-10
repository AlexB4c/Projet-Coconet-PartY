all: Coconut

main.o: main.c game.h
	gcc -c main.c -o main.o

map.o: map.c game.h
	gcc -c map.c -o map.o

menus.o: menus.c game.h
	gcc -c menus.c -o menus.o

crab.o: crab.c game.h
	gcc -c crab.c -o crab.o

monkey.o: monkey.c game.h
	gcc -c monkey.c -o monkey.o

save.o: save.c game.h
	gcc -c save.c -o save.o


Coconut: main.o map.o menus.o crab.o monkey.o save.o
	gcc main.o map.o menus.o crab.o monkey.o save.o -o Coconut 

clean:
	rm -f *.o
	rm -f Coconut













