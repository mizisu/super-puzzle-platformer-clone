#include "game/player.h"
#include "base/components/input.h"
#include "base/components/input_adapter.h"
#include "base/components/texture_manager.h"

const double MoveForce = 80;
const double JumpForce = -200;

InputAdapter a;

Player::Player() : state(PlayerState::Stand) {
  this->SetAnimationTexture(
      TextureManager::GetInstance().GetTexture("play/player/stand.png"), 4);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->Collision(
      [&](Sprite* other, auto result) { this->CollisionBlock(other, result); });

  a.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_UP && state != PlayerState::Jump) Jump();
  });
}

Player::~Player() {}

void Player::Update() {
  base::Update();

  if (Input::GetInstance().IsKeyDown(SDL_SCANCODE_RIGHT)) {
    this->Move(MoveForce);
  }
  if (Input::GetInstance().IsKeyDown(SDL_SCANCODE_LEFT)) {
    this->Move(-MoveForce);
  }

  this->EnableGravity(true);
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
  this->ForceY(JumpForce);
}

void Player::CollisionBlock(Sprite* block, const SDL_Rect& result) {
  if (this->Y() < block->Y()) {
    this->state = PlayerState::Stand;
    this->EnableGravity(false);
    this->Y() = block->Y() - this->Height();
  }

  if (this->Y() > block->Y()) {
    if (this->X() < result.x) this->X() -= result.w;
    if (this->X() >= result.x) this->X() += result.w;
  }
}
