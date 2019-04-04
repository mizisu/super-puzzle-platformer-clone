#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "base/components/sprite.h"

class Sprite;
class Texture;

enum class BlockType {
  Red,
  Green,
  Blue,
  Thorn,
};

class Block : public Sprite {
 public:
  BlockType Type() { return type; }
  virtual void Hit() = 0;
  
  virtual void Update() override;

 protected:
  BlockType type;
};

#endif  // __BLOCK_H__