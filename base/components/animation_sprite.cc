#include "animation_sprite.h"
#include "texture.h"

AnimationSprite::AnimationSprite()
    : frame_count(1), animaion_speed(0.f), current_frame(0.f) {}

AnimationSprite::~AnimationSprite() {}

void AnimationSprite::SetAnimationTexture(std::shared_ptr<Texture> texture,
                                          int frame_count,
                                          double animaion_speed) {
  this->SetTexture(texture);
  this->frame_count = frame_count;
  this->animaion_speed = animaion_speed;
  this->width = this->texture->Width() / this->frame_count;

  this->src_rect.w = this->width;
  this->src_rect.h = this->height;
  this->src_rect.x = 0;
  this->src_rect.y = 0;

  this->dest_rect.w = this->width;
}

void AnimationSprite::Update() {
  current_frame += animaion_speed * Global::DeltaTime;

  this->src_rect.x = (int)current_frame;

  if(current_frame > frame_count) {
    current_frame = 0;
  }
}

void AnimationSprite::Render() {
  SDL_RenderCopy(Global::Renderer, texture->SDLTexture(), &src_rect, &dest_rect);
}
