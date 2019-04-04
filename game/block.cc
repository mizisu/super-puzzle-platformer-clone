#include "block.h"


void Block::Update() {
  double delta = 50 * Global::DeltaTime;
  this->DestRect().y += delta;
}