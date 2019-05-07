#ifndef __DEAD_PLAYER_H__
#define __DEAD_PLAYER_H__

#include "base/components/physics.h"
#include "base/components/sprite.h"

class DeadPlayer : public Sprite, public Physics {
  using base = Sprite;

 public:
  DeadPlayer() {
    this->SetTexture("play/player/stand.png");
    this->ForceX(this->X() - (Global::ScreenRealWidth / 2));
    this->ForceY(-600);
    this->src_rect.w *= 0.25;
  }
  virtual void Update() override {
    base::Update();
    this->angle += 30 * Global::DeltaTime;
    this->dest_rect.w += 70 * Global::DeltaTime;
    this->dest_rect.h += 70 * Global::DeltaTime;
  }
};

#endif  // __DEAD_PLAYER_H__