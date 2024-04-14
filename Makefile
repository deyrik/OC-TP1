compile:
	gcc main.c tp.c -lm -o exefile

run:
	./exefile

all:
	gcc main.c tp.c -lm -o exefile
	./exefile