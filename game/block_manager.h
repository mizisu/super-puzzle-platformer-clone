#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "base/components/node.h"

class Block;

const int BlockMaxWidth = 8;
const int BlockMaxHeight = 12;

class BlockManager : public Node {
 public:
  BlockManager();
  virtual void Update() override;

  void CreateDefaultBlocks();

 private:
  void CreateBlock(int x, int y);

 private:
  std::shared_ptr<Block> blocks[BlockMaxWidth][BlockMaxHeight];
};

#endif  // __BLOCK_MANAGER_H__