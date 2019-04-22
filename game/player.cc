#include "game/player.h"
#include "base/components/input_adapter.h"
#include "base/components/texture_manager.h"

const double MoveForce = 80;
const double JumpForce = -200;
const int animation_frame_count = 4;

Player::Player()
    : state(PlayerState::Stand), texture_stand(nullptr), texture_move(nullptr) {
  this->texture_stand =
      TextureManager::GetInstance().GetTexture("play/player/stand.png");

  this->texture_move =
      TextureManager::GetInstance().GetTexture("play/player/move.png");

  this->SetAnimationTexture(texture_stand, animation_frame_count);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->Collision(
      [&](Sprite* other, auto result) { this->CollisionBlock(other, result); });

  this->input_adapter.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_UP && state != PlayerState::Jump) Jump();
  });
}

Player::~Player() {}

void Player::Update() {
  base::Update();

  if (Input::GetInstance().IsKeyDown(SDL_SCANCODE_RIGHT)) this->Move(MoveForce);
  if (Input::GetInstance().IsKeyDown(SDL_SCANCODE_LEFT)) this->Move(-MoveForce);

  if (Input::GetInstance().IsKeyUp(SDL_SCANCODE_LEFT) &&
      Input::GetInstance().IsKeyUp(SDL_SCANCODE_RIGHT)) {
    this->SetAnimationTexture(this->texture_stand, animation_frame_count);
  }

  this->EnableGravity(true);
}

void Player::Move(double force) {
  this->X() += force * Global::DeltaTime;

  if (force > 0) {  // right
    this->SetAnimationTexture(this->texture_move, animation_frame_count);
    this->FlipHorizontal(false);
  }

  if (force < 0) {  // left
    this->SetAnimationTexture(this->texture_move, animation_frame_count);
    this->FlipHorizontal(true);
  }

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
  if (this->Y() < block->Y() && this->IsFalling()) {
    this->state = PlayerState::Stand;
    this->EnableGravity(false);
    this->Y() = block->Y() - this->Height();
  }

  // block fall on the player
  if (this->Y() - block->Y() > this->Height() / 2) {
    this->Y() = block->Y();
    return;
  }

  // check block left right
  if (this->Y() > block->Y()) {
    if (this->X() < result.x) this->X() -= result.w;
    if (this->X() >= result.x) this->X() += result.w;
  }
}
