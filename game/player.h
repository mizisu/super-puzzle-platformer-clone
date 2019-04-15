#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "base/components/animation_sprite.h"
#include "base/components/physics.h"

enum class PlayerState {
  Stand,
  RunLeft,
  RunRight,
  Jump,
};

class Player : public AnimationSprite, public Physics {
 public:
  typedef AnimationSprite base;
  Player();
  virtual ~Player();
  virtual void Update() override;

 private:
  PlayerState state;
};

#endif  // __PLAYER_H__