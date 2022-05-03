CC = g++
INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = main.o

all: frogger clean

frogger: main.o
	$(CC) main.o -o Frogger $(INCLUDES)

main.o : main.cpp
	$(CC) -c main.cpp

clean:
	rm -f $(OBJS)