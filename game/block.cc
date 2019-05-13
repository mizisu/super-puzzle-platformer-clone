#include "game/block.h"
#include "base/components/animation_sprite.h"
#include "game/block_ground_dust.h"
#include "game/bullet.h"

const int BlockHeight = 96;

Block::Block()
    : block_x(0),
      block_y(0),
      max_y(0),
      on_hit(nullptr),
      init_action_end(false) {
  this->Collision([&](auto other, auto result) {
    if (auto bullet = dynamic_cast<Bullet*>(other); bullet != nullptr) {
      FireOnHitByBullet(bullet->level);
    }
  });
  this->EnableGravity(false);
  this->ForceY(10);
  timer.SetTimeout(
      [&]() {
        this->EnableGravity(true);
        init_action_end = true;
      },
      500);
}

void Block::Update() {
  base::Update();
  if (!init_action_end) return;
  if (this->Y() >= this->GetMaxY()) {
    if (this->Y() != this->GetMaxY()) {
      auto dust = std::make_shared<BlockGroundDust>();
      dust->X() = this->X();
      dust->Y() = this->Y() - this->Height() / 2;
      this->AddChild(dust);
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
  SetBlockY(y);
}