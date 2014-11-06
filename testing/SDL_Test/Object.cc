#include "Object.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <iostream>
#include <string>

using namespace std;

Objects::Objects( int _x, int _y, string _image, SDL_Surface* _screen, string _image2)
        : x(_x), y(_y), screen(_screen)
        {
            image = load_image( _image );
            flipped_image = load_image( _image2 );
            
            if( image == NULL )
            {
                cout << "Error, could not find " << _image << endl;
            }
        }
    
Objects::~Objects()
{
    free();
}

void Objects::free()
{
    if(image != NULL)
    {
        SDL_FreeSurface( image );
        SDL_FreeSurface( flipped_image );
        image = nullptr;
        flipped_image = nullptr;
    }
}
SDL_Surface* Objects::load_image( string filename )
{
    SDL_Surface* loaded_image = NULL;
    SDL_Surface* optimized_image = NULL;
    
    loaded_image = IMG_Load( filename.c_str() );
    
    if (loaded_image != NULL)
    {
        optimized_image = SDL_DisplayFormat( loaded_image );
        SDL_FreeSurface( loaded_image );
    }
    return optimized_image;
}

void Objects::render()
{
    
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    
    SDL_BlitSurface(image, NULL, screen, &offset);
}

void Objects::setX(int _x)
{
    x = _x;
}

void Objects::setY(int _y)
{
    y = _y;
}

int Objects::getX()
{
    return x;
}

int Objects::getY()
{
    return y;
}


Player::Player(int _x, int _y, string _image, SDL_Surface* _screen, string _image2, const int _cW, const int _cH, const int _totFrames)
    : Objects( _x, _y, _image, _screen, _image2), cW(_cW), cH(_cH), totFrames(_totFrames)
    {
       spriteSetup();
    }
    
void Player::spriteSetup()
{
    //spriteClips[0] = spriteClips[totFrames-1];
    //spriteClipsFlipped[0] = spriteClipsFlipped[totFrames-1];
    
    spriteClips[0].x = 0;
    spriteClips[0].y = 0;
    spriteClips[0].w = cW;
    spriteClips[0].h = cH;
    
    spriteClipsFlipped[0].x = 46*7;
    spriteClipsFlipped[0].y = 0;
    spriteClipsFlipped[0].w = cW;
    spriteClipsFlipped[0].h = cH;
    
    for(int i{1}; i < totFrames; ++i)
    {
        spriteClips[i].x = (46*(i-1));
        spriteClips[i].y = 150;
        spriteClips[i].w = cW;
        spriteClips[i].h = cH;
        
        spriteClipsFlipped[i].x = 368-(i*46);
        spriteClipsFlipped[i].y = 150;
        spriteClipsFlipped[i].w = cW;
        spriteClipsFlipped[i].h = cH;
    }
    
}

void Player::render()
{
    
    SDL_Rect offset;
    offset.x = getX();
    offset.y = getY();
    
    if( dir )
    {
        SDL_BlitSurface(flipped_image, &spriteClipsFlipped[frame], screen, &offset);
        //SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
    if ( !dir )
    {
        SDL_BlitSurface(image, &spriteClips[frame], screen, &offset);
        //SDL_UpdateRect(screen, 0, 0, 0, 0);
    }
}

void Player::addFrame()
{
    ++frame;
    if(frame >= totFrames)
        frame = 1;
}

void Player::resFrame()
{
    frame = 0;
}

void Player::setFrame(int input)
{
    frame = input;
}

void Player::setDir(bool newDir)
{
    dir = newDir;
}

