#ifndef __NORMAL_BLOCK_H__
#define __NORMAL_BLOCK_H__

#include "game/block.h"

class NormalBlock : public Block {
 public:
  NormalBlock();
  virtual ~NormalBlock();
  virtual void Hit() override;

 private:
  static RandomGenerator rand;

  int life;
  std::vector<std::shared_ptr<Texture>> block_images;
};

#endif  // __NORMAL_BLOCK_H__