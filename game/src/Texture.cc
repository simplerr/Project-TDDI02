#include "Texture.h"

Texture::Texture(SDL_Texture* texture)
{
    // load texture using SDL
    // error handling

    mTexture = texture;
    //mFilename = filename;
}

string getFilename()
{
    return mFilename;
}

SDL_Texture* getData()
{
    return mTexture;
}
