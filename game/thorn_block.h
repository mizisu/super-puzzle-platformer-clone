#ifndef __THORN_BLOCK_H__
#define __THORN_BLOCK_H__

#include "game/block.h"

class ThornBlock : public Block {
 public:
  ThornBlock();
  virtual ~ThornBlock() = default;
  virtual void Hit() override{};
  virtual int GetMaxY() override { return max_y - 24; }
};

#endif  // __THORN_BLOCK_H__