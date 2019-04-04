#include "player.h"
#include "base/components/texture_manager.h"

Player::Player() {
  this->SetAnimationTexture(
      TextureManager::GetInstance().GetTexture("play/player/stand.png"),
      4);
}

Player::~Player() {}