#include "sprite.h"
#include "texture.h"
#include "texture_manager.h"

Sprite::Sprite() {}

Sprite::Sprite(const std::string& filename) {
  SetTexture(TextureManager::GetInstance().GetTexture(filename));
}

Sprite::~Sprite() {}

void Sprite::Update() {}

void Sprite::Render() {
  SDL_RenderCopy(Global::Renderer, texture->SDLTexture(), NULL, &destRect);
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
  destRect.x = 0;
  destRect.y = 0;
  destRect.w = texture->Width();
  destRect.h = texture->Height();
}
