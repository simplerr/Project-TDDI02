#ifndef OBJECT_H
#define OBJECT_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <iostream>

using namespace std;

class Objects
{
public:
    Objects( int, int, string, SDL_Surface*, string = "");
    
    ~Objects();
    
    void free();
    
    SDL_Surface* load_image( string );
    
    void setX(int);
    void setY(int);
    virtual int getX();
    virtual int getY();
    
    
    void render();
    
    SDL_Surface* screen;
    SDL_Surface* image;
    SDL_Surface* flipped_image;
private:
    int x;
    int y;

};


class Player : public Objects
{
public:
    Player(int, int, string, SDL_Surface*, string, const int, const int, const int);
    
    void spriteSetup();
    
    void render();
    
    void addFrame();
    void resFrame();
    void setDir(bool);
    void setFrame(int input);
    
    
private:
    bool dir;
    int frame{};
    const int totFrames;
    const int cW;
    const int cH;
    SDL_Rect spriteClips[9];
    SDL_Rect spriteClipsFlipped[9];
};
    
#endif
