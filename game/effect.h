#ifndef __EFFECT_H__
#define __EFFECT_H__

#include "base/components/animation_sprite.h"

class Effect : public AnimationSprite {
  using base = AnimationSprite;
 public:
  Effect();
  virtual ~Effect() = default;
  virtual void Update() override;
};

#endif  // __EFFECT_H__