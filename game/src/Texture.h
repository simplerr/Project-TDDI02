#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL_image.h>

using namespace std;

//class SDL_Texture;

class Texture
{
public:
    Texture(SDL_Texture* texture); // correct argument?
    ~Texture();
    string getFilename();
    SDL_Texture* getData();
private:
    SDL_Texture* mTexture;
    string mFilename;
};

#endif