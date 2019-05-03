#include "game/bullet.h"
#include "game/block.h"
#include "game/effect.h"

Bullet::Bullet(int level, bool flip) : flip(flip) {
  level = std::min(level, 4);
  this->SetTexture("play/player/lv"s + std::to_string(level) + ".png"s);
  this->EnableGravity(false);
  this->FlipHorizontal(flip);
  this->Collision([&](auto other, auto result) {
    if (auto block = dynamic_cast<Block*>(other); block != nullptr) {
      this->Erase();
      AddEffect();
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
    this->AddEffect();
  }
}

void Bullet::AddEffect() {
  auto effect = std::make_shared<Effect>();
  effect->X() = this->X();
  effect->Y() = this->Y() - (effect->Height() / 2);
  this->GetParent()->AddChild(effect);
}