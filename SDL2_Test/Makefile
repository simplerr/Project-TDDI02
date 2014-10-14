#
# Makefile
#

CCC	= g++ -std=c++11 
LFLAGS	= -lSDL2 -lSDL2_image

all: main.cc Object.o
	$(CCC) -o main main.cc Object.o $(LFLAGS)

Object.o: Object.cc Object.h
	$(CCC) -c Object.cc Object.h $(LFLAGS)

clean:
	@ \rm -rf *.o *.gch core

zap: clean
	@ \rm -f main *~
