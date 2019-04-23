#include "game/bullet.h"

using namespace std::string_literals;

Bullet::Bullet(int level, bool flip) : flip(false) {
  this->SetTexture("play/player/lv"s + std::to_string(level) + ".png"s);
  this->EnableGravity(false);
  this->flip = flip;
}

void Bullet::Update() {
  base::Update();

  if (this->flip)
    this->ForceX(-300);
  else
    this->ForceX(300);

  int right_end = (Global::RightEnd - this->Width() * 2);
  int left_end = Global::LeftPad + this->Width();
  if (this->X() < left_end || this->X() > right_end) {
    this->Erase();
  }
}
