#include "game/game_scene.h"
#include "game/background_layer.h"
#include "game/block_manager.h"
#include "game/player.h"
#include "game/ui_layer.h"
#include "game/weapon.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<BackgroundLayer>());
  auto block_manager = std::make_shared<BlockManager>();
  this->AddChild(block_manager);
  auto weapon = std::make_shared<Weapon>();
  this->AddChild(weapon);
  auto player = std::make_shared<Player>();
  weapon->SetPlayer(player);
  this->AddChild(player);
  ui = std::make_shared<UiLayer>();
  this->AddChild(ui);

  block_manager->OnBreakBlock([&](int count) {
    this->ui->AddScore(count * rand.Get(1, 30) * rand.Get(1, 30));
  });
}

GameScene::~GameScene() {}