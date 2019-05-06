#ifndef __BLOCK_GROUND_DUST_H__
#define __BLOCK_GROUND_DUST_H__

#include "base/components/animation_sprite.h"

class BlockGroundDust : public AnimationSprite {
  using base = AnimationSprite;
 public:
  BlockGroundDust() {
    int n = rand.Get(0, 4);
    this->SetAnimationTexture("play/block/dust.png", 4);
    this->RepeatAnimation(false);
  }

  virtual void Update() override {
    base::Update();
    if (this->IsEndAnimation()) this->Erase();
  }

 private:
  RandomGenerator rand;
  int force_x;
  int force_y;
};

#endif  // __BLOCK_GROUND_DUST_H__