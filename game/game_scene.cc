#include "game_scene.h"
#include "background_layer.h"
#include "base/sprite.h"
#include "block.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<BackgroundLayer>());
  this->AddChild(std::make_shared<Block>());
}

GameScene::~GameScene() {}