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
  void Move(double force);
  void Jump();
  void CollisionBlock(Sprite* block, const SDL_Rect& result);

 private:
  InputAdapter input_adapter;
  PlayerState state;
  std::shared_ptr<Texture> texture_stand;
  std::shared_ptr<Texture> texture_move;
};

#endif  // __PLAYER_H__