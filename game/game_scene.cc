#include "game_scene.h"
#include "base/sprite.h"

GameScene::GameScene() {
  this->AddChild(std::make_shared<Sprite>("./res/play/background.png"));
}

GameScene::~GameScene() {

}