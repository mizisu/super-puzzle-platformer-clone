#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "base/components/sprite.h"
#include "base/components/physics.h"

enum class BlockType {
  Red,
  Green,
  Blue,
  Thorn,
};

class Block : public Physics, public Sprite {
 public:
  BlockType Type() { return type; }
  virtual void Hit() = 0;
  virtual void Update() override;

 protected:
  BlockType type;
};

#endif  // __BLOCK_H__