#include "game/player.h"
#include "base/components/texture_manager.h"
#include "base/input_adapter.h"
#include "game/block.h"
#include "game/dead_player.h"
#include "game/string_effect.h"

const double MoveForce = 80;
const double JumpForce = -180;
const int animation_frame_count = 4;

Player::Player()
    : state(PlayerState::Stand),
      texture_stand(nullptr),
      texture_move(nullptr),
      energy(0) {
  this->texture_stand =
      TextureManager::GetInstance().GetTexture("play/player/stand.png");

  this->texture_move =
      TextureManager::GetInstance().GetTexture("play/player/move.png");

  this->SetAnimationTexture(texture_stand, animation_frame_count);

  this->X() = Global::ScreenWidth / 2 + Global::LeftPad;

  this->Collision([&](Sprite* other, auto result) {
    if (auto block = dynamic_cast<Block*>(other); block != nullptr)
      this->CollisionBlock(block, result);
  });

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

  if (this->energy < 0) this->Kill();

  this->EnableGravity(true);

  if (this->Y() > Global::ScreenRealHeight) this->Kill();
}

void Player::AddEnerge(int value) {
  auto before_level = this->EnergyToLevel();
  this->energy = std::min(this->energy + value, Global::PlayerMaxEnergy);
  auto current_level = this->EnergyToLevel();

  if (before_level != current_level) LevelUp();
}

int Player::EnergyToLevel() { return Global::EnergyToLevel(this->energy); }

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
  this->EnableGravity(true);
}

void Player::CollisionBlock(Block* block, const SDL_Rect& result) {
  int player_center_x = this->X() + (this->Width() / 2);
  int block_center_x = block->X() + (block->Width() / 2);

  bool is_below_block = this->Y() + (this->Height() / 2) - 15 < block->Y();
  bool is_above_block = this->Y() > block->Y() + block->Height() / 2;

  int player_block_center_dist = std::abs(player_center_x - block_center_x);
  int player_block_center_dist_max =
      (this->Width() / 2) + (block->Width() / 2) - 20;

  if (player_block_center_dist < player_block_center_dist_max &&
      is_above_block) {
    this->Y() = block->Y() - this->Height();
    HitByBlock();
    return;
  }

  if (this->IsFalling() && is_below_block &&
      player_block_center_dist < player_block_center_dist_max) {
    if (block->GetBlockType() == BlockType::Thorn) {
      this->Kill();
    }
    this->Y() = block->Y() - this->Height();
    this->EnableGravity(false);
    this->state = PlayerState::Stand;
  }

  if (!is_below_block) {
    if (player_center_x < block_center_x)
      this->X() = block->X() - this->Width();

    if (player_center_x > block_center_x)
      this->X() = block->X() + block->Width();
  }
}

void Player::HitByBlock() {
  this->energy -= 10;
  this->AddChild(std::make_shared<StringEffect>(StringEffectType::PowerDown,
                                                this->X(), this->Y()));
  if (this->hit_by_block != nullptr) this->hit_by_block();
  if (this->energy < 0) Kill();
}

void Player::Kill() {
  auto dead_player = std::make_shared<DeadPlayer>();
  dead_player->X() = this->X();
  dead_player->Y() = this->Y();
  this->GetParent()->AddChild(dead_player);
  this->X() = 0;
  this->Y() = 0;
  this->dest_rect.w = 0;
  this->dest_rect.h = 0;
  this->energy = 0;
  this->EnableGravity(false);
  this->Erase();
  if(on_erase != nullptr) on_erase();
}

void Player::LevelUp() {
  this->AddChild(std::make_shared<StringEffect>(StringEffectType::PowerUp,
                                                this->X(), this->Y()));
}