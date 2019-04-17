#include "game/block.h"

Block::Block() : block_x(0), block_y(0), max_y(0) {
  // this->Collision([&](Sprite* other) {
  //   if (auto block = dynamic_cast<Block*>(other); block) {
  //     if(this->Y() < other->Y()) {
  //       this->Y() = other->Y() - other->Height();
  //       this->EnableGravity(false);
  //     }
  //   }
  // });
}

void Block::Update() {
  if (this->Y() >= max_y) {
    this->Y() = max_y;
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
  max_y = block_y * this->height + Global::TopPad;
}

void Block::SetBlockPosY(int y) {
  this->Y() = y * this->height + Global::TopPad;
  this->EnableGravity(true);
  SetBlockY(y);
}