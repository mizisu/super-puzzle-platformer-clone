#include "game/player.h"
#include "base/components/texture_manager.h"

Player::Player() {
  this->SetAnimationTexture(
      TextureManager::GetInstance().GetTexture("play/player/stand.png"), 4);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->OnCollision([&](Sprite* other) {
    this->EnableGravity(false);
    this->Y() = other->Y() - this->Height();
  });
}

Player::~Player() {}