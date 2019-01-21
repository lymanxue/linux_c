main: worker.o
	gcc -o main worker.o -lpthread
