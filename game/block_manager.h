#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "base/components/node.h"

class Block;

const int BlockMaxColumn = 8;
const int BlockMaxRow = 12;

class BlockManager : public Node {
 public:
  BlockManager();
  virtual void Update() override;
  void CreateDefaultBlocks();
  void CreateNewBlock();
  void CreateThornBlock();

  auto& Blocks() { return blocks; }

 private:
  void CreateBlock(int x, int y);
  void UpdateBlock(Block* block, int x, int y);
  void CheckAndSwapBelowBlock(int x, int y);

 private:
  Block* blocks[BlockMaxColumn][BlockMaxRow];
  RandomGenerator random;
};

#endif  // __BLOCK_MANAGER_H__