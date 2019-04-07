#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "base/components/animation_sprite.h"
#include "base/components/physics.h"

class Player : public AnimationSprite, public Physics {
 public:
  Player();
  virtual ~Player();

};

#endif  // __PLAYER_H__