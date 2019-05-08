#ifndef __DEAD_PLAYER_H__
#define __DEAD_PLAYER_H__

#include "base/components/sprite.h"

class DeadPlayer : public Sprite {
  using base = Sprite;

 public:
  DeadPlayer() {
    this->SetTexture("play/player/stand.png");
    this->src_rect.w *= 0.25;
    this->dest_rect.w *= 0.25;
    dest_y = -300;
    delta_angle = 90;
    delta_size = 100;
    int t = 1300;
    timer.SetTimeout(
        [&]() {
          delta_angle = 0;
          delta_size = 0;
        },
        t);

    timer.SetTimeout([&]() { this->dest_y = 300; }, t + 500);
    timer.SetTimeout([&]() { this->dest_y = 1700; }, t + 1000);
  }
  virtual void Update() override {
    base::Update();
    this->angle += delta_angle * Global::DeltaTime;
    this->dest_rect.w += delta_size * Global::DeltaTime;
    this->dest_rect.h += delta_size * Global::DeltaTime;
    this->X() +=
        ((Global::ScreenRealWidth / 2) - this->X() - (this->Width() / 2)) *
        Global::DeltaTime;
    this->Y() += (dest_y - this->Y()) * Global::DeltaTime;
  }

 private:
  Timer timer;
  int dest_y;
  int delta_angle;
  int delta_size;
};

#endif  // __DEAD_PLAYER_H__