#include "game/game_scene.h"
#include "game/background_layer.h"
#include "game/block_manager.h"
#include "game/player.h"
#include "game/weapon.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<BackgroundLayer>());
  this->AddChild(std::make_shared<BlockManager>());
  auto weapon = std::make_shared<Weapon>();
  this->AddChild(weapon);
  auto player = std::make_shared<Player>();
  weapon->SetPlayer(player);
  this->AddChild(player);
  
}

GameScene::~GameScene() {}