#
# Makefile
#

CCC	= g++ -std=c++11 -Wall -pedantic
LFLAGS	= -lSDL2 -lSDL2_image -lSDL2_ttf

all: main.cc Game.o PlayState.o Game.o PlayState.o Renderer.o Level.o Object.o
	$(CCC) -o main main.cc Game.o PlayState.o Renderer.o Level.o Object.o $(LFLAGS)

Game.o: Game.cc Game.h
	$(CCC) -c Game.cc 

PlayState.o: PlayState.cc PlayState.h
	$(CCC) -c PlayState.cc

Renderer.o: Renderer.cc Renderer.h
	$(CCC) -c Renderer.cc

Level.o: Level.cc Level.o Object.o
	$(CCC) -c Level.cc 

Object.o: Object.cc Object.h Texture.cc Texture.h Vec2.h Player.cc Player.h
	$(CCC) -c Object.cc Texture.cc Player.cc

clean:
	@ \rm -rf *.o *.gch core

zap:
	@ \rm -f main *~

