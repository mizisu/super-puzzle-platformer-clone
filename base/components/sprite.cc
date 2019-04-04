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
  SDL_RenderCopy(Global::Renderer, texture->SDLTexture(), NULL, &dest_rect);
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
  dest_rect.x = 0;
  dest_rect.y = 0;
  dest_rect.w = width = texture->Width();
  dest_rect.h = height = texture->Height();
}
