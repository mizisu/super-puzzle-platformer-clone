#ifndef __LASER_H__
#define __LASER_H__

#include "base/components/physics.h"
#include "base/components/sprite.h"

class Laser : public Sprite, public Physics {
 public:
  Laser();
  virtual void Update() override;

 private:
  RandomGenerator rand;
  int origin_height;
  Timer timer;
};

#endif  // __LASER_H__