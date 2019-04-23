#ifndef __BULLET_H__
#define __BULLET_H__

#include "base/components/sprite.h"
#include "base/components/physics.h"

class Bullet : public Sprite, public Physics {
  using base = Sprite;
 public:
  Bullet(int level, bool flip);
  virtual ~Bullet() = default;
  virtual void Update() override;

 private:
  bool flip;
};

#endif  // __BULLET_H__