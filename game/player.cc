#include "game/player.h"
#include "base/components/input.h"
#include "base/components/input_adapter.h"
#include "base/components/texture_manager.h"

const double MoveForce = 80;
const double JumpForce = -250;

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
    this->Move(MoveForce);
  }
  if (Input::GetInstance().IsKeyPress(SDL_SCANCODE_LEFT)) {
    this->Move(-MoveForce);
  }

  if (Input::GetInstance().IsKeyPress(SDL_SCANCODE_UP) &&
      state != PlayerState::Jump) {
    this->Jump();
  }
}

void Player::Move(double force) {
  this->X() += force * Global::DeltaTime;
  if (this->X() < Global::LeftPad) {
    this->X() = Global::LeftPad;
  }
  if (this->X() > Global::RightEnd - this->Width()) {
    this->X() = Global::RightEnd - this->Width();
  }
}

void Player::Jump() {
  this->state = PlayerState::Jump;
  this->EnableGravity(true);
  this->ForceY(JumpForce);
}

void Player::CollisionBlock(Sprite* block) {
  this->state = PlayerState::Stand;
  this->EnableGravity(false);
  this->Y() = block->Y() - this->Height();
}
