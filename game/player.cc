#include "game/player.h"
#include "base/components/input.h"
#include "base/components/input_adapter.h"
#include "base/components/texture_manager.h"

InputAdapter a;

Player::Player() : state(PlayerState::Stand) {
  this->SetAnimationTexture(
      TextureManager::GetInstance().GetTexture("play/player/stand.png"), 4);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->Collision([&](Sprite* other) { this->CollisionBlock(other); });
}

Player::~Player() {}

void Player::Update() {
  base::Update();
  
  if (Input::GetInstance().IsKeyPress(SDL_SCANCODE_RIGHT)) {
    this->X() += 100 * Global::DeltaTime;
  }
  if (Input::GetInstance().IsKeyPress(SDL_SCANCODE_LEFT)) {
    this->X() -= 100 * Global::DeltaTime;
  }

  if (Input::GetInstance().IsKeyPress(SDL_SCANCODE_UP) &&
      state != PlayerState::Jump) {
  }
}

void Player::Move() {}

void Player::Jump() {
  this->state = PlayerState::Jump;
  this->EnableGravity(true);
  this->ForceY(-250);
}

void Player::CollisionBlock(Sprite* block) {
  this->state = PlayerState::Stand;
  this->EnableGravity(false);
  this->Y() = block->Y() - this->Height();
}
