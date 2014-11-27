#include "Texture.h"

Texture::Texture(SDL_Texture* texture)
{
    // load texture using SDL
    // error handling

    mTexture = texture;
    //mFilename = filename;
}

Texture::~Texture()
{
    SDL_DestroyTexture(mTexture);
}

string Texture::getFilename()
{
    return mFilename;
}

SDL_Texture* Texture::getData()
{
    return mTexture;
}
