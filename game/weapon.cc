#include "game/weapon.h"
#include "game/bullet.h"
#include "game/player.h"

const int XPad = 25;
const int YPad = 25;

Weapon::Weapon() {
  this->SetTexture("play/player/weapon.png");
  input.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_Z) this->Fire();
  });
}

void Weapon::Render() {
  this->X() = this->player->X();
  this->Y() = this->player->Y();
  this->FlipHorizontal(this->player->IsFlipHorizontal());

  if (this->IsFlipHorizontal()) {
    this->X() -= XPad;
  }

  base::Render();
}

void Weapon::Fire() {
  auto level = std::max(this->player->level, 1);
  auto bullet = std::make_shared<Bullet>(level, this->IsFlipHorizontal());
  bullet->X() = this->X();
  if (this->IsFlipHorizontal()) {
    this->X() -= XPad;
  }
  bullet->Y() = this->Y() + YPad - (level * level);
  this->AddChild(bullet);
}