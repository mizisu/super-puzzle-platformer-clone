#ifndef __ITEM_H__
#define __ITEM_H__

#include "base/components/animation_sprite.h"
#include "base/components/physics.h"

class Item : public AnimationSprite, public Physics {
 public:
  Item(int point);
  virtual ~Item() = default;
  int GetPoint() { return point; }

 private:
  void Jump();

 private:
  int point;
  RandomGenerator rand;
};

#endif  // __ITEM_H__