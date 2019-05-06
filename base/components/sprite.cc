#include "base/components/sprite.h"
#include "base/components/texture.h"
#include "base/components/texture_manager.h"

Sprite::Sprite() : texture(nullptr), angle(0), is_flip_horz(false) {
  dest_rect = {0, 0, 0, 0};
  src_rect = {0, 0, 0, 0};
  center = {0, 0};
}

Sprite::Sprite(const std::string& path) : Sprite() {
  SetTexture(TextureManager::GetInstance().GetTexture(path));
}

Sprite::Sprite(const std::string& path, int x, int y) : Sprite(path) {
  this->X() = x;
  this->Y() = y;
}

Sprite::~Sprite() {}

void Sprite::Update() {}

void Sprite::Render() {
  int flip = SDL_FLIP_NONE;
  if (is_flip_horz) flip |= SDL_FLIP_HORIZONTAL;
  SDL_RenderCopyEx(Global::Renderer, texture->SDLTexture(), &src_rect,
                   &dest_rect, angle, NULL, (SDL_RendererFlip)flip);
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture) {
  this->texture = texture;
  this->dest_rect.w = texture->Width();
  this->dest_rect.h = texture->Height();
  src_rect.w = this->dest_rect.w;
  src_rect.h = this->dest_rect.h;
}

void Sprite::SetTexture(const std::string& path) {
  SetTexture(TextureManager::GetInstance().GetTexture(path));
}

void Sprite::SetAlpha(float opacity) {
  SDL_SetTextureAlphaMod(this->texture->SDLTexture(), 255 * opacity);
}