#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "base/components/animation_sprite.h"
#include "base/components/physics.h"

class Block;

enum class PlayerState {
  Stand,
  RunLeft,
  RunRight,
  Jump,
};

class Player : public AnimationSprite, public Physics {
  using base = AnimationSprite;

 public:
  Player();
  virtual ~Player();
  virtual void Update() override;
  void OnHitByBlock(std::function<void()> func) { hit_by_block = func; }
  int GetEnergy() { return energy; }
  void AddEnerge(int value);

 private:
  void Move(double force);
  void Jump();
  void CollisionBlock(Block* block, const SDL_Rect& result);
  void HitByBlock();
  void Kill();
  void LevelUp();

 public:
  std::function<void()> hit_by_block;
  int level;

 private:
  InputAdapter input_adapter;
  PlayerState state;
  std::shared_ptr<Texture> texture_stand;
  std::shared_ptr<Texture> texture_move;
  int energy;
};

#endif  // __PLAYER_H__