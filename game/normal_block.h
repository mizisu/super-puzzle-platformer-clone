#ifndef __NORMAL_BLOCK_H__
#define __NORMAL_BLOCK_H__

#include "game/block.h"

class NormalBlock : public Block {
  using base = Block;

 public:
  NormalBlock();
  virtual ~NormalBlock();
  virtual void Hit() override;

 private:
  void LoadImages();
  void HitInternal();

 private:
  static RandomGenerator rand;

  int life;
  std::vector<std::shared_ptr<Texture>> block_images;
  std::vector<std::shared_ptr<Texture>> block_damaged_images;
  Timer timer;
};

#endif  // __NORMAL_BLOCK_H__