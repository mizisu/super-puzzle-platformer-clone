#include "game_scene.h"
#include "background_layer.h"
#include "base/sprite.h"

GameScene::GameScene() { this->AddChild(std::make_shared<BackgroundLayer>()); }

GameScene::~GameScene() {}