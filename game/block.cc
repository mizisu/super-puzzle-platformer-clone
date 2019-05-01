#include "game/block.h"
#include "game/bullet.h"

const int BlockHeight = 96;

Block::Block() : block_x(0), block_y(0), max_y(0), on_hit(nullptr) {
  this->Collision([&](auto other, auto result) {
    if (auto bullet = dynamic_cast<Bullet*>(other); bullet != nullptr) {
      if (this->on_hit != nullptr) this->on_hit(this);
    }
  });
}

void Block::Update() {
  if (this->Y() >= this->GetMaxY()) {
    this->Y() = this->GetMaxY();
    this->EnableGravity(false);
  } else {
    this->EnableGravity(true);
  }
}

void Block::SetBlockX(int x) { block_x = x; }

void Block::SetBlockPosX(int x) {
  this->X() = x * this->width + Global::LeftPad;
  SetBlockX(x);
}

void Block::SetBlockY(int y) {
  block_y = y;
  max_y = block_y * BlockHeight + Global::TopPad;
}

void Block::SetBlockPosY(int y) {
  this->Y() = y * BlockHeight + Global::TopPad;
  this->EnableGravity(true);
  SetBlockY(y);
}