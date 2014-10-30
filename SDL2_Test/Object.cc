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
    velX -= moveSpeed;
    playerDir = false;
    addFrameForward();
}

void Player::moveUp()
{
    ;
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

void Player::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY -= moveSpeed; break;
            case SDLK_DOWN: velY += moveSpeed; break;
            case SDLK_LEFT: moveLeft(); break;
            case SDLK_RIGHT: velX += moveSpeed; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: velY += moveSpeed; break;
            case SDLK_DOWN: velY -= moveSpeed; break;
            case SDLK_LEFT: velX += moveSpeed; break;
            case SDLK_RIGHT: velX -= moveSpeed; break;
        }
    }
}




void Player::move( SDL_Rect& B )
{
    SDL_Rect* PP = getRectPointer();
    //Move the dot left or right
    //PP->x += velX;
    PP->x += velX;
	//mCollider.x = mPosX;
        
    //If the dot collided or went too far to the left or right
    if( checkCollision( *PP, B ) )
    {
        //Move back
        PP->x -= velX;
		//mCollider.x = mPosX;
    }

    //Move the dot up or down
    //PP->x += velY;
    PP->y += velY;
	//mCollider.y = mPosY;
    
    //If the dot collided or went too far up or down
    if( (checkCollision( *PP, B )) )
    {
        //Move back
        PP->y -= velY;
		//mCollider.y = mPosY;
    }
    velY = 0;
    velX = 0;
}


bool Player::checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB && topA >= bottomB && rightA <= leftB && leftA >= rightB )
    {
        return false;
    }
<<<<<<< HEAD

    //If none of the sides from A are outside B
    return true;
}

void Player::systemRun(vector<Object> v)
{
    SDL_Rect B;
    for (auto i : v)
    {
	B = i.getTextureRec();
	move(B);
    }
=======
    
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
    
>>>>>>> 9aede0badb0583606a7bc64eff4630fd9eb44754
}

