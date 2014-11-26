#
# Makefile
#

CCC	= g++ -std=c++11 -Wall -pedantic 
LFLAGS	= -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: main.cc Game.o Enemy.o PlayState.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o PauseState.o EditorState.o Sound.o Button.o Background.o Decoration.o Powerup.o Credit.o constants.h
	$(CCC) -o main main.cc Game.o Enemy.o PlayState.o Renderer.o Level.o Platform.o Object.o Player.o Texture.o MenuState.o PauseState.o EditorState.o Sound.o Button.o Background.o Decoration.o Powerup.o Credit.o $(LFLAGS)

Game.o: Game.cc Game.h constants.h
	$(CCC) -c Game.cc		

PlayState.o: PlayState.cc PlayState.h constants.h
	$(CCC) -c PlayState.cc

Renderer.o: Renderer.cc Renderer.h constants.h
	$(CCC) -c Renderer.cc

Level.o: Level.cc Level.h constants.h
	$(CCC) -c Level.cc

Platform.o: Platform.cc Platform.h constants.h
	$(CCC) -c Platform.cc

Object.o: Object.cc Object.h Vec2.h constants.h
	$(CCC) -c Object.cc

Player.o: Player.cc Player.h constants.h
	$(CCC) -c Player.cc

Texture.o: Texture.cc Texture.h constants.h
	$(CCC) -c Texture.cc

MenuState.o: MenuState.cc MenuState.h constants.h
	$(CCC) -c MenuState.cc

PauseState.o: PauseState.cc PauseState.h constants.h
	$(CCC) -c PauseState.cc

EditorState.o: EditorState.cc EditorState.h constants.h
	$(CCC) -c EditorState.cc

Button.o: Button.cc Button.h constants.h
	$(CCC) -c Button.cc

Sound.o: Sound.cc Sound.h constants.h
	$(CCC) -c Sound.cc

Background.o: Background.cc Background.h constants.h
	$(CCC) -c Background.cc

Decoration.o: Decoration.cc Decoration.h constants.h
	$(CCC) -c Decoration.cc

Enemy.o: Enemy.cc Enemy.h constants.h
	$(CCC) -c Enemy.cc

Powerup.o: Powerup.cc Powerup.h constants.h
	$(CCC) -c Powerup.cc

Credit.o: Credit.cc Credit.h constants.h
	$(CCC) -c Credit.cc

clean:
	@ \rm -rf *.o *.gch core

zap:
	@ \rm -f main *~

