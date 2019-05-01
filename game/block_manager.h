#ifndef __BLOCK_MANAGER_H__
#define __BLOCK_MANAGER_H__

#include "base/components/node.h"
#include "game/block.h"

const int MaxBlockColumn = 8;
const int MaxBlockRow = 12;

class BlockManager : public Node {
  using BlockVistedSet = std::vector<std::bitset<MaxBlockRow>>;

 public:
  BlockManager();
  virtual void Update() override;
  void CreateDefaultBlocks();
  void CreateNewBlock();
  void CreateThornBlock();

  auto& Blocks() { return blocks; }

 private:
  Block* GetBlock(int x, int y);
  void CreateBlock(int x, int y);
  void UpdateBlock(Block* block, int x, int y);
  void CheckAndSwapBelowBlock(int x, int y);
  bool CanHit(const BlockVistedSet& visited, Block* block, BlockType blockType);
  void HitConnectedBlock(Block* block);
  bool HitConnectedBlockInternal(BlockVistedSet& visited, Block* block,
                                 BlockType blockType);
  void EraseBlocks(const BlockVistedSet& visited);

 private:
  Block* blocks[MaxBlockColumn][MaxBlockRow];
  RandomGenerator random;
};

#endif  // __BLOCK_MANAGER_H__