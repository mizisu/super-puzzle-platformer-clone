#include "base/components/texture.h"

const char* base = "./res/";

Texture::Texture(const std::string& path) {
  auto real_path = base + path;
  SDL_Texture* newTexture = NULL;

  SDL_Surface* loadedSurface = IMG_Load(real_path.c_str());

  if (loadedSurface == NULL)
    Global::Log(std::string("Image load failed : ") + path + IMG_GetError());

  newTexture = SDL_CreateTextureFromSurface(Global::Renderer, loadedSurface);

  if (newTexture == NULL)
    Global::Log(std::string("CreateTexutre failed : ") + path + SDL_GetError());

  SDL_QueryTexture(newTexture, NULL, NULL, &width, &height);

  texture = newTexture;

  SDL_FreeSurface(loadedSurface);
}

Texture::~Texture() { SDL_DestroyTexture(texture); }
