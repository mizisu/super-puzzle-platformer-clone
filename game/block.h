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
 public:
  Block();
  BlockType Type() { return type; }
  virtual int GetMaxY() { return max_y; }
  virtual void Hit() = 0;
  virtual void Update() override;
  void SetBlockX(int x);
  void SetBlockPosX(int x);
  void SetBlockY(int y);
  void SetBlockPosY(int y);

 protected:
  BlockType type;
  int block_x;
  int block_y;
  int max_y;
};

#endif  // __BLOCK_H__