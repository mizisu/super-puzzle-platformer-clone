#include "game/weapon.h"
#include "game/bullet.h"
#include "game/player.h"

const int XPad = 25;
const int YPad = 30;

Weapon::Weapon() {
  this->SetTexture("play/player/weapon.png");
  input.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_Z) this->Fire();
  });
}

void Weapon::Update() {}

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
  auto bullet = std::make_shared<Bullet>(1, this->IsFlipHorizontal());
  bullet->X() = this->X();
  if (this->IsFlipHorizontal()) {
    this->X() -= XPad;
  }
  bullet->Y() = this->Y() + YPad;
  this->AddChild(bullet);
}