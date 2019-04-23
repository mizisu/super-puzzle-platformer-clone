#include "base/components/sprite.h"
#include "base/components/texture.h"
#include "base/components/texture_manager.h"

Sprite::Sprite() : texture(nullptr), angle(0), is_flip_horz(false) {
  dest_rect = {0, 0, 0, 0};
  src_rect = {0, 0, 0, 0};
  center = {0, 0};
}

Sprite::Sprite(const std::string& filename) : Sprite() {
  SetTexture(TextureManager::GetInstance().GetTexture(filename));
}

Sprite::~Sprite() {}

void Sprite::Update() {}

void Sprite::Render() {
  int flip = SDL_FLIP_NONE;
  if (is_flip_horz) flip |= SDL_FLIP_HORIZONTAL;

  SDL_RenderCopyEx(Global::Renderer, texture->SDLTexture(), &src_rect,
                   &dest_rect, angle, &center, (SDL_RendererFlip)flip);
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
  width = texture->Width();
  height = texture->Height();
  dest_rect.w = width;
  dest_rect.h = height;
  src_rect.w = width;
  src_rect.h = height;
}

void Sprite::SetTexture(const std::string& filename) {
  SetTexture(TextureManager::GetInstance().GetTexture(filename));
}