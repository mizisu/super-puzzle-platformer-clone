#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "base/components/physics.h"
#include "base/components/sprite.h"

enum class BlockType {
  Red,
  Green,
  Blue,
  Thorn,
};

class Block : public Physics, public Sprite {
  using base = Sprite;

 public:
  Block();
  virtual ~Block() = default;
  BlockType GetBlockType() { return type; }
  virtual int GetMaxY() { return max_y; }
  virtual void Hit() = 0;
  virtual void ChangeHitEffectTexture(){};
  virtual void Update() override;
  virtual bool IsDead() { return false; }
  void SetBlockX(int x);
  void SetBlockPosX(int x);
  int GetBlockX() { return this->block_x; }
  void SetBlockY(int y);
  void SetBlockPosY(int y);
  int GetBlockY() { return this->block_y; }
  void OnHitByBullet(std::function<void(Block* block, int bullet_level)> func) {
    this->on_hit = func;
  }
  void FireOnHitByBullet(int bullet_level) {
    this->on_hit(this, bullet_level);
  }

 public:
  bool init_action_end;

 protected:
  BlockType type;
  int block_x;
  int block_y;
  int max_y;
  std::function<void(Block* block, int bullet_level)> on_hit;
  Timer timer;
};

#endif  // __BLOCK_H__