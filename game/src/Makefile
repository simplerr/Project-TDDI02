#
# Makefile
#

CCC	= g++ -std=c++11 -Wall -pedantic 
LFLAGS	= -lSDL2 -lSDL2_image

all: main.cc Game.o PlayState.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o BaseState.h
	$(CCC) -o main main.cc Game.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o $(LFLAGS)

Game.o: Game.cc Game.h
	$(CCC) -c Game.cc 

PlayState.o: PlayState.cc PlayState.h
	$(CCC) -c PlayState.cc

Renderer.o: Renderer.cc Renderer.h
	$(CCC) -c Renderer.cc

Level.o: Level.cc Level.h
	$(CCC) -c Level.cc

Platform.o: Platform.cc Platform.h
	$(CCC) -c Platform.cc

Object.o: Object.cc Object.h Vec2.h
	$(CCC) -c Object.cc
	
Player.o: Player.cc Player.h
	$(CCC) -c Player.cc

Texture.o: Texture.cc Texture.h
	$(CCC) -c Texture.cc
	
MenuState.o: MenuState.cc MenuState.h
	$(CCC) -c MenuState.cc
	
clean:
	@ \rm -rf *.o *.gch core

zap:
	@ \rm -f main *~

