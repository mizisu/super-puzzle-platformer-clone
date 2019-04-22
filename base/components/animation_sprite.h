#ifndef __ANIMATION_SPRITE_H__
#define __ANIMATION_SPRITE_H__

#include "base/components/sprite.h"

class AnimationSprite : public Sprite {
 public:
  AnimationSprite();
  virtual ~AnimationSprite();

  void SetAnimationTexture(std::shared_ptr<Texture> texture, int frame_count,
                           double animaion_speed = 1);

  virtual void Update() override;

 private:
  int frame_count;
  double animaion_speed;
  double current_frame;
};

#endif  // __ANIMATION_SPRITE_H__