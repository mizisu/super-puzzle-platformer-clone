#include "game/game_scene.h"
#include "game/background_layer.h"
#include "game/block_manager.h"
#include "game/item.h"
#include "game/player.h"
#include "game/string_effect.h"
#include "game/ui_layer.h"
#include "game/weapon.h"

InputAdapter input;

GameScene::GameScene() : stage_lock(false), stage(0) {
  // TODO: remove test code
  input.KeyDown([&](auto scancode) {
    if (scancode == SDL_SCANCODE_E) {
      CreateItem(10);
    }
  });

  this->AddChild(std::make_shared<BackgroundLayer>());
  this->block_manager = std::make_shared<BlockManager>();
  this->AddChild(this->block_manager);

  this->player = std::make_shared<Player>();
  auto weapon = std::make_shared<Weapon>();
  weapon->SetPlayer(player);
  player->AddChild(weapon);
  this->AddChild(player);

  this->ui = std::make_shared<UiLayer>();
  this->ui->SetEnerge(0);
  this->AddChild(ui);

  this->player->OnHitByBlock(
      [&]() { this->ui->SetEnerge(this->player->GetEnergy()); });

  block_manager->OnBreakBlock([&](int count) {
    this->ui->AddScore(count * rand.Get(1, 30) * rand.Get(1, 30));
    CreateItem(count);
    this->AddChild(std::make_shared<StringEffect>(
        StringEffectType::Score, this->player->X(), this->player->Y()));
  });

  timer.SetInterval(
      [&]() {
        if (!stage_lock) {
          this->NextStage();
        }
      },
      1000);
}

GameScene::~GameScene() {}

void GameScene::CreateItem(int count) {
  for (int i = 0; i < count; i++) {
    auto item = std::make_shared<Item>(rand.Get(1, count * 2));
    item->Collision([this, &item](auto other, auto result) {
      if (this->player.get() == other) {
        this->ui->SetEnerge(this->player->GetEnergy());
      }
    });
    this->AddChild(item);
  }
}

void GameScene::NextStage() {
  stage++;
  if (stage == 1) {
    this->StartDropBlockStage();
  } else if (stage == 2) {
    this->StartDropThronBlock();
  } else if (stage == 3) {
    this->StartDropBlockLine();
  }
}

void GameScene::StartDropBlockStage() {
  stage_lock = true;
  for (int i = 1; i <= 6; i++) {
    timer.SetTimeout([&]() { block_manager->CreateNewBlock(); }, 2000 * i);
  }
  timer.SetTimeout([&]() { this->stage_lock = false; }, 14000);
}

void GameScene::StartDropThronBlock() {
  for (int i = 1; i <= 2; i++) {
    timer.SetTimeout([&]() { block_manager->CreateThornBlock(); }, 3000 * i);
  }
}

void GameScene::StartDropBlockLine() {
  for (int i = 1; i <= 2; i++) {
    timer.SetTimeout(
        [&]() {
          for (size_t i = 1; i <= MaxBlockColumn - 3; i++) {
            block_manager->CreateNewBlock();
          }
        },
        7000 * i);
  }
}