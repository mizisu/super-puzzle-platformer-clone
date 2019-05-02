#include "base/components/animation_sprite.h"
#include "base/components/texture.h"
#include "base/components/texture_manager.h"

AnimationSprite::AnimationSprite()
    : frame_count(1),
      animaion_speed(0.f),
      current_frame(0.f),
      repeat_animation(true) {}

AnimationSprite::~AnimationSprite() {}

void AnimationSprite::SetAnimationTexture(std::shared_ptr<Texture> texture,
                                          int frame_count,
                                          double animaion_speed) {
  if (this->texture != nullptr && this->texture->Name() == texture->Name())
    return;

  this->SetTexture(texture);
  this->frame_count = frame_count;
  this->animaion_speed = animaion_speed;
  this->dest_rect.w = this->texture->Width() / this->frame_count;

  this->src_rect.w = this->dest_rect.w;
  this->src_rect.h = this->dest_rect.h;
  this->src_rect.x = 0;
  this->src_rect.y = 0;
}

void AnimationSprite::SetAnimationTexture(const std::string& path,
                                          int frame_count,
                                          double animaion_speed) {
  auto texture = TextureManager::GetInstance().GetTexture(path);
  this->SetAnimationTexture(texture, frame_count, animaion_speed);
}

void AnimationSprite::Update() {
  current_frame += animaion_speed * Global::DeltaTime;

  this->src_rect.x = (int)current_frame * this->Width();

  if (this->IsEndAnimation() && this->repeat_animation) {
    RestartAnimation();
  }
}