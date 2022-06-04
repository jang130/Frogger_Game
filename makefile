CC = g++
INCLUDES = -lsfml-graphics -lsfml-window -lsfml-system
OBJS = main.o engine.o player.o enemy.o canNotLoadTexture.o menu.o

all: frogger clean

frogger: $(OBJS)
	$(CC) $(OBJS) -g -o Frogger $(INCLUDES)

%.o : %.cpp
	$(CC) -g -c $< -o $@

clean:
	rm -f $(OBJS)