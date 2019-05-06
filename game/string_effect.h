#ifndef __STRING_EFFECT_H__
#define __STRING_EFFECT_H__

#include "base/components/sprite.h"
#include "base/components/physics.h"

enum class StringEffectType {
  PowerUp,
  PowerDown,
  Score,
};

class StringEffect : public Sprite, public Physics {
  using base = Sprite;
 public:
  StringEffect(StringEffectType type, int x, int y) {
    if (type == StringEffectType::PowerUp) {
      this->SetTexture("play/player/pup.png");
    } else if (type == StringEffectType::PowerDown) {
      this->SetTexture("play/player/pdown.png");
    } else if (type == StringEffectType::Score) {
      int n = rand.Get(0, 20);
      this->SetTexture("play/string_effect/se"s + std::to_string(n) + ".png");
    }
    this->ForceY(-100);
    this->acceleration *= 0.5;
    this->X() = x;
    this->Y() = y;
    this->dest_rect.w *= 1.3;
    this->dest_rect.h *= 1.3;
  }

  virtual void Update() override {
    base::Update();
    if(this->IsFalling()) this->Erase();
  }

 private:
  RandomGenerator rand;
};

#endif  // __STRING_EFFECT_H__