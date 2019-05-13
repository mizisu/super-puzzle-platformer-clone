#include "game/laser.h"
#include "game/block.h"
#include "game/player.h"

Laser::Laser() {
  this->EnableGravity(false);
  this->SetTexture("play/laser/laser.png");
  origin_height = this->Height();

  auto mark = std::make_shared<Sprite>("play/laser/warning_mark.png");
  mark->DestRect().w *= 3;
  mark->DestRect().h *= 3;
  this->AddChild(mark);

  int x = rand.Get(Global::LeftPad, Global::RightEnd);

  mark->X() = x + 5;

  this->X() = x;
  this->Y() -= 500;
  this->dest_rect.h = origin_height * 0.2;
  this->src_rect.h = origin_height * 0.2;
  this->ForceY(15);

  this->Collision([&](auto other, auto result) {
    if (auto block = dynamic_cast<Block*>(other); block != nullptr) {
      if (on_hit_block != nullptr) on_hit_block(block);
      std::cout << block->GetBlockX() << " " << block->GetBlockY() << "\n";
    } else if (auto player = dynamic_cast<Player*>(other); player != nullptr) {
      player->Kill();
    }
  });

  timer.SetTimeout([&]() { this->Erase(); }, 4000);
}

void Laser::Update() {
  if (this->Y() >= -100) {
    this->ForceY(0);
    this->dest_rect.h = origin_height * 1.2;
    this->src_rect.h = origin_height;
  }
}