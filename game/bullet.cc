#include "game/bullet.h"
#include "game/block.h"

using namespace std::string_literals;

Bullet::Bullet(int level, bool flip) : flip(false) {
  this->SetTexture("play/player/lv"s + std::to_string(level) + ".png"s);
  this->EnableGravity(false);
  this->flip = flip;
  this->Collision([&](auto other, auto result) {
    if(auto block = dynamic_cast<Block*>(other); block != nullptr) {
      block->Hit();
      this->Erase();
    }
  });
}

void Bullet::Update() {
  base::Update();

  if (this->flip)
    this->ForceX(-300);
  else
    this->ForceX(300);

  int left_end = Global::LeftPad;
  int right_end = Global::RightEnd - this->Width();
  if (this->X() < left_end || this->X() > right_end) {
    this->Erase();
  }
}
