#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "base/components/scene.h"

class UiLayer;

class GameScene : public Scene {
 public:
  GameScene();
  virtual ~GameScene();

 private:
  RandomGenerator rand;
  std::shared_ptr<UiLayer> ui;
};

#endif // __GAME_SCENE_H__