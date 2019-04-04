#include "game_scene.h"
#include "background_layer.h"
#include "block_manager.h"
#include "player.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<BackgroundLayer>());
  this->AddChild(std::make_shared<BlockManager>());
  this->AddChild(std::make_shared<Player>());
}

GameScene::~GameScene() {}