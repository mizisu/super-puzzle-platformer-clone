#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "base/sprite.h"

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
  Block();
  ~Block();

  BlockType Type() { return type; }
  void Hit();
  
 private:
  static RandomGenerator rand;

  int life;
  BlockType type;
  std::vector<std::shared_ptr<Texture>> block_images;
};

#endif  // __BLOCK_H__