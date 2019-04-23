#include "game/bullet.h"

using namespace std::string_literals;

Bullet::Bullet(int level, bool flip) {
  this->SetTexture("play/player/lv"s + std::to_string(level) + ".png"s);
  if (flip)
    this->ForceX(-500);
  else
    this->ForceX(500);

  this->EnableGravity(false);
}

void Bullet::Update() {
  base::Update();

  if (this->X() > Global::RightEnd || this->X() < Global::LeftPad) {
  }
}
