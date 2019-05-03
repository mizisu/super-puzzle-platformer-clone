#ifndef __BAR_SPRITE_H__
#define __BAR_SPRITE_H__

#include "base/components/sprite.h"

class BarSprite : public Sprite {
 public:
  void SetMinMax(int min, int max) {
    this->min = min;
    this->max = max;
  }
  void SetValue(int value);

 private:
  int min;
  int max;
};

#endif  // __BAR_SPRITE_H__