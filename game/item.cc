#include "game/item.h"
#include "game/block.h"
#include "game/player.h"

Item::Item(int point) : point(point) {
  this->X() = rand.Get(Global::LeftPad, Global::RightEnd);
  if (point >= 8) {
    this->SetAnimationTexture("play/item/point2.png", 4);
  } else {
    this->SetAnimationTexture("play/item/point.png", 1);
  }

  this->Collision([&](auto other, auto result) {
    if (auto block = dynamic_cast<Block*>(other); block != nullptr) {
      Jump();
    } else if (auto player = dynamic_cast<Player*>(other); player != nullptr) {
      this->Erase();
      player->AddEnerge(this->GetPoint());
    }
  });
}

void Item::Jump() { this->ForceY(-200); }