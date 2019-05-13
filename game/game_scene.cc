#include "game/game_scene.h"
#include "game/background_layer.h"
#include "game/block_manager.h"
#include "game/item.h"
#include "game/laser.h"
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
    if (scancode == SDL_SCANCODE_R) {
      timer.SetInterval([&]() { this->StartLaser(); }, 4000);
      timer.SetInterval([&]() { this->StartDropBlockLine(); }, 4000);
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
  if (stage >= 6) {
    stage = 6;
    stage = rand.Get(1, 6);
  }

  if (stage == 1) {
    this->StartDropBlockStage();
  } else if (stage == 2) {
    this->StartDropThronBlock();
  } else if (stage == 3) {
    this->StartDropBlockLine();
  } else if (stage == 4) {
    this->StartLaser();
  } else if (stage == 5) {
    this->StartDropMultipleBlockStage();
  }
}

void GameScene::StartStage(std::function<void()> func, int count,
                           int interval) {
  stage_lock = true;

  for (int i = 0; i < count; i++) {
    timer.SetTimeout(func, i * interval);
  }

  timer.SetTimeout([&]() { this->stage_lock = false; },
                   (count * interval) + 500);
}

void GameScene::StartDropBlockStage() {
  StartStage([&]() { block_manager->CreateNewBlock(); }, 6, 2000);
}

void GameScene::StartDropThronBlock() {
  StartStage([&]() { block_manager->CreateThornBlock(); }, 2, 2000);
}

void GameScene::StartDropBlockLine() {
  StartStage(
      [&]() {
        for (size_t i = 1; i <= MaxBlockColumn - 3; i++) {
          block_manager->CreateNewBlock();
        }
      },
      3, 4000);
}

void GameScene::StartLaser() {
  StartStage(
      [&]() {
        auto laser = std::make_shared<Laser>();
        laser->on_hit_block = [&](Block* block) {
          this->block_manager->EraseBlocks(std::vector<Block*>{block});
        };
        this->AddChild(laser);
      },
      2, 4000);
}

void GameScene::StartDropMultipleBlockStage() {
  StartStage([&]() { block_manager->CreateNewBlock(); }, 20, 500);
}