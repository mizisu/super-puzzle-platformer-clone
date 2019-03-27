#include "sprite.h"
#include "texture.h"
#include "texture_manager.h"

Sprite::Sprite(const std::string& filename) {
  texture = TextureManager::GetInstance().GetTexture(filename);
  destRect.x = 0;
  destRect.y = 0;
  destRect.w = texture->Width();
  destRect.h = texture->Height();
}

Sprite::~Sprite() {}

void Sprite::Update() {}

void Sprite::Render() {
  SDL_RenderCopy(Global::Renderer, texture->SDLTexture(), NULL, &destRect);
}