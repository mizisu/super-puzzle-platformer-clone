#include "game/score.h"
#include "base/components/sprite.h"
#include "base/components/texture_manager.h"

Score::Score() : score(0), current_score(0) {
  for (int i = 0; i < 10; i++) {
    this->textures.push_back(TextureManager::GetInstance().GetTexture(
        "play/ui/"s + std::to_string(i) + ".png"));

    auto sp = std::make_shared<Sprite>();
    sp->SetTexture(this->textures[0]);
    sp->DestRect().w *= 0.9;
    sp->DestRect().h *= 0.9;
    sp->X() = 755 - ((sp->Width() + 3) * i);
    sp->Y() = 1225;

    this->AddChild(sp);
    this->sprites.push_back(sp);
  }
}

void Score::Update() {
  if (this->current_score < this->score) {
    this->current_score += rand.Get(1, 100);
    this->current_score = std::min(this->current_score, this->score);
    auto temp = this->current_score;
    int i = 0;
    while (temp != 0) {
      auto texture = this->textures[temp % 10];
      auto sp = this->sprites[i];
      sp->SetTexture(texture);
      sp->DestRect().w *= 0.9;
      sp->DestRect().h *= 0.9;
      temp = temp / 10;
      ++i;
    }
  }
}

void Score::Add(long num) {
  this->score += num;
  this->score = std::min(this->score, 9999999999);
}