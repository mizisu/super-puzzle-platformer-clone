#include "game/block_manager.h"
#include "base/camera.h"
#include "base/input_adapter.h"
#include "game/normal_block.h"
#include "game/thorn_block.h"

InputAdapter adapter;

BlockManager::BlockManager() : on_break_block(nullptr) {
  CreateDefaultBlocks();

  // TODO: remove test code
  adapter.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_W) this->CreateNewBlock();
    if (scancode == SDL_SCANCODE_Q) this->CreateThornBlock();
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
      if (j >= MaxBlockRow - 3) {
        CreateBlock(i, j);
        blocks[i][j]->init_action_end = true;
      } else {
        blocks[i][j] = nullptr;
      }
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
  block->OnHitByBullet([&](Block* block, int bullet_level) {
    this->HitConnectedBlock(block, bullet_level);
  });
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

bool BlockManager::CanHit(const BlockVistedSet& visited, Block* block,
                          BlockType blockType) {
  if (block == nullptr || block->GetBlockType() != blockType ||
      block->IsFalling())
    return false;
  auto x = block->GetBlockX();
  auto y = block->GetBlockY();
  if (!visited[x][y]) {
    return true;
  } else {
    return false;
  }
}

void BlockManager::HitConnectedBlock(Block* block, int bullet_level) {
  bool hit = false;
  BlockVistedSet visited;
  for (int i = 0; i < bullet_level; i++) {
    visited.clear();
    visited.resize(MaxBlockColumn);
    hit =
        this->HitConnectedBlockInternal(visited, block, block->GetBlockType());
  }

  if (hit == false) {
    EraseBlocks(visited);
  }
}

bool BlockManager::HitConnectedBlockInternal(BlockVistedSet& visited,
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

void BlockManager::EraseBlocks(const BlockVistedSet& visited) {
  int count = 0;
  for (int x = 0; x < visited.size(); x++) {
    for (int y = 0; y < visited[x].size(); y++) {
      if (!visited[x][y]) continue;
      ++count;
      blocks[x][y]->Erase();
      blocks[x][y] = nullptr;
    }
  }
  Camera::GetInstance().Shake(std::min(count * 5, 30), 500);
  if (this->on_break_block != nullptr) on_break_block(count);
}