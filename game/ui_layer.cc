#include "game/ui_layer.h"
#include "base/components/animation_sprite.h"
#include "base/components/bar_sprite.h"
#include "base/components/sprite.h"
#include "game/player.h"
#include "game/score.h"

const int UiTopPad = 23;

UiLayer::UiLayer() {
  auto black = std::make_shared<Sprite>("play/ui/black.png");
  black->SetAlpha(0.5);
  this->AddChild(black);
  this->lvbar = std::make_shared<BarSprite>();
  this->lvbar->SetTexture("play/ui/lvbar.png");
  this->lvbar->SetMinMax(Global::PlayerMinEnergy, Global::PlayerMaxEnergy);
  this->lvbar->X() = 98;
  this->lvbar->Y() = UiTopPad;
  this->AddChild(lvbar);
  lv_mark.push_back(std::make_shared<Sprite>("play/ui/x1.png", 0, UiTopPad));
  this->AddChild(lv_mark.back());
  lv_mark.push_back(std::make_shared<Sprite>("play/ui/x2.png", 300, UiTopPad));
  this->AddChild(lv_mark.back());
  lv_mark.push_back(std::make_shared<Sprite>("play/ui/x3.png", 600, UiTopPad));
  this->AddChild(lv_mark.back());

  auto max = std::make_shared<AnimationSprite>();
  lv_mark.push_back(max);
  max->SetAnimationTexture("play/ui/max.png", 4);
  max->X() = 845;
  max->Y() = UiTopPad - 17;
  this->AddChild(max);

  this->score = std::make_shared<Score>();
  this->AddChild(score);
}

void UiLayer::Update() {
  auto level = Global::EnergyToLevel(this->lvbar->GetValue());
  for (int i = 0; i < lv_mark.size(); i++) {
    if (i < level) {
      this->lv_mark[i]->SetAlpha(1);
    } else {
      this->lv_mark[i]->SetAlpha(0);
    }
  }
}

void UiLayer::AddScore(long num) { this->score->Add(num); }

long UiLayer::GetScore() { return this->score->score; }

void UiLayer::SetEnerge(int value) { this->lvbar->SetValue(value); }
