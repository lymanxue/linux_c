
TARGET = libworker
C_FILES = $(wildcard *.c)
CC = gcc
LIBS = pthread
OBJS = $(C_FILES:.c=.o)

main: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) -l$(LIBS)

clean:
	rm *.o
