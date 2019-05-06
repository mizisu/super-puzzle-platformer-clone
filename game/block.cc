#include "game/block.h"
#include "base/components/animation_sprite.h"
#include "game/block_ground_dust.h"
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
    if (this->Y() != this->GetMaxY()) {
      for (int i = 0; i < 1; i++) {
        // auto dust = std::make_shared<BlockDust>();
        // dust->X() = this->X() + this->Width() / 2;
        // dust->Y() = this->Y() + this->Height() / 2;
        // this->AddChild(dust);
        auto dust = std::make_shared<BlockGroundDust>();
        dust->X() = this->X();
        dust->Y() = this->Y() - this->Height() / 2;
        this->AddChild(dust);
      }
    }
    this->Y() = this->GetMaxY();
    this->EnableGravity(false);

  } else {
    this->EnableGravity(true);
  }
}

void Block::SetBlockX(int x) { block_x = x; }

void Block::SetBlockPosX(int x) {
  this->X() = x * this->Width() + Global::LeftPad;
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