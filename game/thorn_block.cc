#include "game/thorn_block.h"

ThornBlock::ThornBlock() {
  this->type = BlockType::Thorn;
  this->SetTexture("play/block/thorn.png");
}