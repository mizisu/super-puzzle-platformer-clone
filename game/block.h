#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "base/node.h"

class Block : public Node {
 public:
  Block();
  ~Block();
 private:
 RandomGenerator rand;
};

enum class BlockType {
  Red,
  Blue,
  Green,
  Thorn,
};

#endif  // __BLOCK_H__