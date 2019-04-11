#include "block_manager.h"
#include "normal_block.h"

void BlockManager::BlockLoop(std::function<void(int i, int j)> func) {
  for (int i = 0; i < BlockMaxWidth; i++) {
    for (int j = BlockMaxWidth - 3; j < BlockMaxWidth; j++) {
      func(i, j);
    }
  }
}

void BlockManager::BlockLoop(std::function<void(Block* block)> func) {
  BlockLoop([&](int i, int j) {
    auto block = Blocks()[i][j];
    if (block != nullptr) func(block.get());
  });
}

BlockManager::BlockManager() { CreateDefaultBlocks(); }

void BlockManager::Update() {
  BlockLoop([&](int i, int j) {
    auto block = Blocks()[i][j];
    if (block != nullptr) {
    }
  });
}

void BlockManager::CreateBlock(int i, int j) {
  auto block = std::make_shared<NormalBlock>();
  block->SetBlockPosX(i);
  block->SetBlockPosY(j);
  blocks[i][j] = block;
  this->AddChild(block);
}

void BlockManager::CreateDefaultBlocks() {
  BlockLoop([&](int i, int j) { CreateBlock(i, j); });
}
