#include "block_manager.h"
#include "normal_block.h"

const int LeftPad = 96;
const int TopPad = 330;

BlockManager::BlockManager() { CreateDefaultBlocks(); }

void BlockManager::Update() {}

void BlockManager::CreateBlock(int i, int j) {
  auto block = std::make_shared<NormalBlock>();
  block->GetX() = i * block->Width() + LeftPad;
  block->GetY() = j * block->Height() + TopPad;
  blocks[i][j] = block;
  this->AddChild(block);
}

void BlockManager::CreateDefaultBlocks() {
  for (int i = 0; i < BlockMaxWidth; i++) {
    for (int j = BlockMaxWidth - 3; j < BlockMaxWidth; j++) {
      CreateBlock(i, j);
    }
  }
}
