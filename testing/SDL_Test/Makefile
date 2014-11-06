#
# Makefile
#

CCC	= g++ -std=c++11 
LFLAGS	= -lSDL -lSDL_image

all: game.cc Object.o
	$(CCC) -o game game.cc Object.o $(LFLAGS)

Object.o: Object.cc Object.h
	$(CCC) -c Object.cc Object.h $(LFLAGS)

clean:
	@ \rm -rf *.o *.gch core

zap: clean
	@ \rm -f game *~
