#include "game/effect.h"

Effect::Effect() {
  this->SetAnimationTexture("play/player/bulleteff.png", 3, 2);
  this->RepeatAnimation(false);
}

void Effect::Update() {
  base::Update();
  if(this->IsEndAnimation()) {
    this->Erase();
  }
}