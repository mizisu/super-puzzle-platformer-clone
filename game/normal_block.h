#ifndef __NORMAL_BLOCK_H__
#define __NORMAL_BLOCK_H__

#include "game/block.h"

class NormalBlock : public Block {
  using base = Block;

 public:
  NormalBlock();
  virtual ~NormalBlock() = default;
  virtual bool IsDead() override { return this->life <= 0; }
  virtual void Hit() override;
  virtual void ChangeHitEffectTexture() override;

 private:
  void LoadImages();

 private:
  static RandomGenerator rand;

  int life;
  std::vector<std::shared_ptr<Texture>> block_images;
  std::vector<std::shared_ptr<Texture>> block_damaged_images;
};

#endif  // __NORMAL_BLOCK_H__