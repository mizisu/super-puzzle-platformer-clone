#include "block.h"

Block::Block() : block_x(0), block_y(0), max_y(0) {}

void Block::Update() {
  if (this->Y() > max_y) {
    this->Y() = max_y;
    this->EnableGravity(false);
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