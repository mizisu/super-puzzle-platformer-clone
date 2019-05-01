#include "game/block_manager.h"
#include "base/input_adapter.h"
#include "game/normal_block.h"
#include "game/thorn_block.h"

InputAdapter adapter;

BlockManager::BlockManager() {
  CreateDefaultBlocks();

  // TODO: remove test code
  adapter.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_SPACE) this->CreateNewBlock();
  });
}

void BlockManager::Update() {
  for (int i = 0; i < MaxBlockColumn; i++) {
    for (int j = 0; j < MaxBlockRow; j++) {
      if (blocks[i][j] != nullptr) {
        UpdateBlock(blocks[i][j], i, j);
      }
    }
  }
}

void BlockManager::CreateDefaultBlocks() {
  for (int i = 0; i < MaxBlockColumn; i++) {
    for (int j = 0; j < MaxBlockRow; j++) {
      if (j >= MaxBlockRow - 3)
        CreateBlock(i, j);
      else
        blocks[i][j] = nullptr;
    }
  }
}

void BlockManager::CreateNewBlock() {
  int x = random.Get(0, MaxBlockColumn);
  if (this->blocks[x][0] == nullptr) {
    this->CreateBlock(x, 0);
  }
}

void BlockManager::CreateThornBlock() {
  int x = random.Get(0, MaxBlockColumn);
  auto block = std::make_shared<ThornBlock>();
  block->SetBlockPosX(x);
  block->SetBlockPosY(0);
  blocks[x][0] = block.get();
  this->AddChild(block);
}

Block* BlockManager::GetBlock(int x, int y) {
  if (x < 0 || x >= MaxBlockColumn || y < 0 || y >= MaxBlockRow) return nullptr;
  auto block = blocks[x][y];
  return block;
}

void BlockManager::CreateBlock(int x, int y) {
  auto block = std::make_shared<NormalBlock>();
  block->SetBlockPosX(x);
  block->SetBlockPosY(y);
  block->OnHitByBullet([&](Block* block) { this->HitConnectedBlock(block); });
  blocks[x][y] = block.get();
  this->AddChild(block);
}

void BlockManager::UpdateBlock(Block* block, int x, int y) {
  CheckAndSwapBelowBlock(x, y);
}

void BlockManager::CheckAndSwapBelowBlock(int x, int y) {
  if (y + 1 < MaxBlockRow && blocks[x][y + 1] == nullptr) {
    auto block = blocks[x][y];
    blocks[x][y] = nullptr;
    blocks[x][y + 1] = block;
    block->SetBlockY(y + 1);
  }
}

bool BlockManager::CanHit(BlockVistedSet visited, Block* block,
                          BlockType blockType) {
  if (block == nullptr || block->GetBlockType() != blockType) return false;
  auto x = block->GetBlockX();
  auto y = block->GetBlockY();
  if (!visited[x][y]) {
    return true;
  } else {
    return false;
  }
}

void BlockManager::HitConnectedBlock(Block* block) {
  std::bitset<MaxBlockRow> visited[MaxBlockColumn];
  bool hit =
      this->HitConnectedBlockInternal(visited, block, block->GetBlockType());
  if (hit == false) {
    std::cout << "erase blocks" << std::endl;
  }
}

bool BlockManager::HitConnectedBlockInternal(BlockVistedSet visited,
                                             Block* block,
                                             BlockType blockType) {
  auto x = block->GetBlockX();
  auto y = block->GetBlockY();

  visited[x][y] = true;

  if (block->IsDead()) {
    block->ChangeHitEffectTexture();
  } else {
    block->Hit();
    return true;
  }

  struct Point {
    int x;
    int y;
  };

  Point next_dirs[] = {
      {x - 1, y},
      {x, y - 1},
      {x + 1, y},
      {x, y + 1},
  };

  for (auto& next : next_dirs) {
    auto next_block = this->GetBlock(next.x, next.y);
    if (CanHit(visited, next_block, blockType) &&
        HitConnectedBlockInternal(visited, next_block, blockType)) {
      return true;
    }
  }

  return false;
}