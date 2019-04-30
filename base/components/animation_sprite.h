#ifndef __ANIMATION_SPRITE_H__
#define __ANIMATION_SPRITE_H__

#include "base/components/sprite.h"

class AnimationSprite : public Sprite {
 public:
  AnimationSprite();
  virtual ~AnimationSprite();

  void SetAnimationTexture(std::shared_ptr<Texture> texture, int frame_count,
                           double animaion_speed = 0.8);
  void SetAnimationTexture(const std::string& path, int frame_count,
                           double animaion_speed = 0.8);

  virtual void Update() override;

  void RestartAnimation() { current_frame = 0; }
  void RepeatAnimation(bool repeat) { this->repeat_animation = repeat; }
  bool IsEndAnimation() { return current_frame > frame_count - 1; }

 private:
  int frame_count;
  double animaion_speed;
  double current_frame;
  bool repeat_animation;
};

#endif  // __ANIMATION_SPRITE_H__