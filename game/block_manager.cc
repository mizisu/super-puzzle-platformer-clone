#include "game/block_manager.h"
#include "base/input_adapter.h"
#include "game/normal_block.h"

InputAdapter adapter;

BlockManager::BlockManager() {
  CreateDefaultBlocks();

  // TODO: remove test code
  adapter.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_SPACE) this->CreateNewBlock();
  });
}

void BlockManager::Update() {
  for (int i = 0; i < BlockMaxColumn; i++) {
    for (int j = 0; j < BlockMaxRow; j++) {
      if (blocks[i][j] != nullptr) {
        UpdateBlock(blocks[i][j], i, j);
      }
    }
  }
}

void BlockManager::CreateDefaultBlocks() {
  for (int i = 0; i < BlockMaxColumn; i++) {
    for (int j = 0; j < BlockMaxRow; j++) {
      if (j >= BlockMaxRow - 3)
        CreateBlock(i, j);
      else
        blocks[i][j] = nullptr;
    }
  }
}

void BlockManager::CreateNewBlock() {
  int x = random.Get(0, BlockMaxColumn);
  if (this->blocks[x][0] == nullptr) {
    this->CreateBlock(x, 0);
  }
}

void BlockManager::CreateBlock(int i, int j) {
  auto block = std::make_shared<NormalBlock>();
  block->SetBlockPosX(i);
  block->SetBlockPosY(j);
  blocks[i][j] = block.get();
  this->AddChild(block);
}

void BlockManager::UpdateBlock(Block* block, int x, int y) {
  CheckAndSwapBelowBlock(x, y);
}

void BlockManager::CheckAndSwapBelowBlock(int x, int y) {
  if (y + 1 < BlockMaxRow && blocks[x][y + 1] == nullptr) {
    auto block = blocks[x][y];
    blocks[x][y] = nullptr;
    blocks[x][y + 1] = block;
    block->SetBlockY(y + 1);
  }
}