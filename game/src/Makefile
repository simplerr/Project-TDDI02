#
# Makefile
#

CCC	= g++ -std=c++11 -Wall -pedantic 
LFLAGS	= -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: main.cc Game.o Enemy.o PlayState.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o PauseState.o EditorState.o Sound.o Button.o Background.o Decoration.o Powerup.o Credit.o
	$(CCC) -o main main.cc Game.o Enemy.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o PauseState.o EditorState.o Sound.o Button.o Background.o Decoration.o Powerup.o Credit.o $(LFLAGS)

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

PauseState.o: PauseState.cc PauseState.h
	$(CCC) -c PauseState.cc

EditorState.o: EditorState.cc EditorState.h
	$(CCC) -c EditorState.cc

Button.o: Button.cc Button.h
	$(CCC) -c Button.cc

Sound.o: Sound.cc Sound.h
	$(CCC) -c Sound.cc

Background.o: Background.cc Background.h
	$(CCC) -c Background.cc

Decoration.o: Decoration.cc Decoration.h
	$(CCC) -c Decoration.cc

Enemy.o: Enemy.cc Enemy.h
	$(CCC) -c Enemy.cc

Powerup.o: Powerup.cc Powerup.h
	$(CCC) -c Powerup.cc

Credit.o: Credit.cc Credit.h
	$(CCC) -c Credit.cc

clean:
	@ \rm -rf *.o *.gch core

zap:
	@ \rm -f main *~

