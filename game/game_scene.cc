#include "game/game_scene.h"
#include "game/background_layer.h"
#include "game/block_manager.h"
#include "game/player.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<BackgroundLayer>());
  this->AddChild(std::make_shared<BlockManager>());
  this->AddChild(std::make_shared<Player>());
}

GameScene::~GameScene() {}