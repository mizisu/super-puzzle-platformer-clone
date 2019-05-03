#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "base/components/scene.h"

class UiLayer;
class Player;

class GameScene : public Scene {
 public:
  GameScene();
  virtual ~GameScene();

 private:
  void CreateItem(int count);
 private:
  RandomGenerator rand;
  std::shared_ptr<UiLayer> ui;
  std::shared_ptr<Player> player;
};

#endif  // __GAME_SCENE_H__