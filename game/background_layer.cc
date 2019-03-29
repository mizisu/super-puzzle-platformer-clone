#include "background_layer.h"
#include "base/sprite.h"

const int UIHeihgt = 96;

BackgroundLayer::BackgroundLayer() {
  auto background = std::make_shared<Sprite>("./res/play/background.png");
  background_width = background->Width();
  background_height = background->Height();
  this->AddChild(background);

  CreateBottomLine();
  CreatePill();
  CreateEdge();
}

BackgroundLayer::~BackgroundLayer() {}

void BackgroundLayer::CreateBottomLine() {
  for (int i = 0; i < 10; i++) {
    auto sp = std::make_shared<Sprite>("./res/play/block/bottom.png");
    sp->SetPosition(sp->Width() * i, background_height - sp->Height());
    this->AddChild(sp);
  }
}

void BackgroundLayer::CreatePill() {
  auto texturepath = "./res/play/block/pill.png";
  for (int i = 0; i < 11; i++) {
    auto left = std::make_shared<Sprite>(texturepath);
    left->SetPosition(0, (left->Height() * i) + UIHeihgt);
    this->AddChild(left);

    auto right = std::make_shared<Sprite>(texturepath);
    right->SetPosition(background_width - right->Width(),
                       (right->Height() * i) + UIHeihgt);
    this->AddChild(right);
  }
}

void BackgroundLayer::CreateEdge() {
  auto lefttop = std::make_shared<Sprite>("./res/play/block/edge.png");
  lefttop->SetPosition(0, UIHeihgt);
  this->AddChild(lefttop);

  auto righttop = std::make_shared<Sprite>("./res/play/block/edge.png");
  righttop->SetPosition(background_width - righttop->Width(), UIHeihgt);
  this->AddChild(righttop);

  auto leftbottom = std::make_shared<Sprite>("./res/play/block/edge.png");
  leftbottom->SetPosition(0, background_height - leftbottom->Height());
  this->AddChild(leftbottom);

  auto rightbottom = std::make_shared<Sprite>("./res/play/block/edge.png");
  rightbottom->SetPosition(background_width - righttop->Width(),
                           background_height - leftbottom->Height());
  this->AddChild(rightbottom);
}