#include "game/player.h"
#include "base/components/input.h"
#include "base/components/input_adapter.h"
#include "base/components/texture_manager.h"

InputAdapter a;

Player::Player() : state(PlayerState::Stand) {
  this->SetAnimationTexture(
      TextureManager::GetInstance().GetTexture("play/player/stand.png"), 4);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->Collision([&](Sprite* other) {
    this->EnableGravity(false);
    this->Y() = other->Y() - this->Height();
  });
}

Player::~Player() {}

void Player::Update() {
  base::Update();
  if (Input::GetInstance().GetKeyState(SDLK_RIGHT) == KeyState::KeyPress)
    this->X() += 100 * Global::DeltaTime;
  else if (Input::GetInstance().GetKeyState(SDLK_LEFT) == KeyState::KeyPress)
    this->X() -= 100 * Global::DeltaTime;
}