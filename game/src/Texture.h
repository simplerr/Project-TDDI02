#pragma once
#include <string>
using namespace std;

class SDL_Texture;

class Texture
{
public:
    Texture(SDL_Texture* texture); // correct argument?

    string getFilename();
    SDL_Texture* getData();
private:
    SDL_Texture* mTexture;
    string mFilename;
};
