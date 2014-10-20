#include "Object.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

SDL_Texture* Object::loadTexture(string str)
{
    //The final texture
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface* tmpSurface = IMG_Load( str.c_str() );
    if(tmpSurface == NULL)
    {
        cerr << "ERROR: Kunde inte öppna fil: " << str << IMG_GetError() << endl;
    }else
    {
        //Convertera surface till screen format
        newTexture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
        if(newTexture == NULL)
        {
            cerr << "ERROR: Misslyckades konvertera fil: " << str << SDL_GetError() << endl;
        }
        SDL_FreeSurface(tmpSurface);
    }
    return newTexture;
}

void Object::render()
{
    //Render texture to screen
    SDL_RenderCopy( renderer, texture, NULL, &textureRec );
}

void Player::setupClips()
{
    SDL_Rect textRec = getTextureRec();
    int counter{};
    for( int iy{0}; iy < 4; ++iy)
    {
        for( int ix{0}; ix < 8; ++ix)
        {
            rectClipsRight[counter].x =textRec.w*ix;
            rectClipsRight[counter].y =textRec.h*iy;
            rectClipsRight[counter].w = textRec.w;
            rectClipsRight[counter].h = textRec.h;
            ++counter;
        }
    }
    counter=0;
    for( int jy{0}; jy < 4; ++jy)
    {
        for( int jx{7}; jx >= 0; --jx)
        {
            rectClipsLeft[counter].x =textRec.w*jx;
            rectClipsLeft[counter].y =textRec.h*jy;
            rectClipsLeft[counter].w = textRec.w;
            rectClipsLeft[counter].h = textRec.h;
            ++counter;
        }
    }
}

void Player::render()
{
    SDL_Renderer* renderer = getRenderer();
    SDL_Rect offset = getTextureRec();
    
     
    if(playerDir) // Höger Sprite
    {
        offset.w = rectClipsRight->w;
        offset.h = rectClipsRight->h;
        SDL_RenderCopy( renderer, textureRight, &rectClipsRight[clipFrame], &offset ); //Render texture to screen
    }
    else // Vänster Sprite
    {
        offset.w = rectClipsLeft->w;
        offset.h = rectClipsLeft->h;
        SDL_RenderCopy( renderer, textureLeft, &rectClipsLeft[clipFrame], &offset );
    }
}       

void Player::moveRight()
{
    setX(getX()+moveSpeed);
    playerDir = true;
    addFrameForward();
}

void Player::moveLeft()
{
    setX(getX()-moveSpeed);
    playerDir = false;
    addFrameForward();
}

void Player::moveUp()
{
    if (jumpCounter <= 0)
    {
        jumpCounter = jumpHeight;
    }
}

void Player::moveStand()
{
    clipFrame = 0;
}
void Player::addFrameForward()
{
    ++clipFrame;
    if(clipFrame >= 32 || clipFrame <= 24)
        clipFrame = 25;
}

/*
bool Player::collisionDetected(vector<Object> v)
{
    
    SDL_Rect A = getTextureRec();
    SDL_Rect B;
    for (int i{0}; i < v.size(); ++i)
    {
        B = v[i].getTextureRec();
        
            //  A.y+A.h > B.y - Uppifrån
           // A.x+A.w > B.x - från vänster
           // A.x < B.x+B.w -höger
           //A.y < B.y+B.h - Underifrån 
           if ((A.x < B.x+B.w && A.x+A.w > B.x && A.y+A.h > B.y && A.y < B.y+B.h))
            {
                return true;
            }
    }
    return false;
}
*/

void Player::move()
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
    
    if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_RIGHT ])
    {
             moveRight();
             moveUp();
    }
    else if( currentKeyStates[ SDL_SCANCODE_UP ] &&  currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
            moveLeft();
            moveUp();
    }
    else if( currentKeyStates[ SDL_SCANCODE_LEFT ] )
    {
            moveLeft();
    }
    else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] )
    {
            moveRight();
    }
    else if( currentKeyStates[ SDL_SCANCODE_UP ] )
    {
            moveUp();
    }else
    {
            moveStand();
    }
    
    if (jumpCounter >= jumpHeight/2) //Jump active
      {
	setY(getY()-fallSpeed);
	jumpCounter -= fallSpeed;
	clipFrame = 17;
      }else if (jumpCounter > 0 && jumpCounter <= jumpHeight/2)
      {
        jumpCounter -= fallSpeed;
        clipFrame = 17;
      }else
      setY(getY()+fallSpeed);
    
}

