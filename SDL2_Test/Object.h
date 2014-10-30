#ifndef OBJECT_H
#define OBJECT_H

#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include <string>
#include <vector>

using namespace std;

class Object
{
public:
    Object(int _x, int _y, int _w, int _h, SDL_Renderer* _renderer)
        : textureRec{_x, _y, _w, _h} , renderer(_renderer) {}
    
    Object(int _x, int _y, int _w, int _h, SDL_Renderer* _renderer, string _strImage)
        : textureRec{_x, _y, _w, _h} , renderer(_renderer)
        {
            texture = loadTexture(_strImage);
        }
        
    SDL_Texture* loadTexture(string);
        
    virtual void render();
    SDL_Rect* getRectPointer(){ return & textureRec; }
    SDL_Rect getTextureRec(){ return textureRec; }
    int getX(){ return textureRec.x; }
    int getY(){ return textureRec.y; }
    void setX(int x) { textureRec.x = x; }
    void setY(int y) { textureRec.y = y; }
    
    SDL_Renderer* getRenderer(){ return renderer; }
    
private:
    SDL_Rect textureRec; 
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
};

class Player : public Object
{
public:
    Player(int _x, int _y, int _w, int _h, SDL_Renderer* _renderer, string _strImage, string _strImage2)
        : Object(_x, _y, _w, _h, _renderer)
        {
            textureRight = loadTexture(_strImage);
            textureLeft = loadTexture(_strImage2);
            setupClips();
            velX = _x;
            velY = _y;
        }
        
    void render() override;
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveStand();
    void addFrameForward();
    void move();
    
    void systemRun(vector<Object> v);
    bool checkCollision( SDL_Rect a, SDL_Rect b );
    void move( SDL_Rect& B );
    void handleEvent( SDL_Event& e );
    
    
private:
    SDL_Texture* textureRight;
    SDL_Texture* textureLeft;
    SDL_Rect rectClipsRight[32];
    SDL_Rect rectClipsLeft[32];
    int playerDir{true};
    int clipFrame{};
<<<<<<< HEAD
    int moveSpeed{3};
    int jumpHeight{120};
=======
    int moveSpeed{2};
    float fallSpeed{4};
    int jumpHeight{100};
>>>>>>> 9aede0badb0583606a7bc64eff4630fd9eb44754
    int jumpCounter{};
    int velX;
    int velY;
    void setupClips();
};

#endif
