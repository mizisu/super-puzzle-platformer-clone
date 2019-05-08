#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "base/components/scene.h"

class UiLayer;
class Player;
class BlockManager;

class GameScene : public Scene {
 public:
  GameScene();
  virtual ~GameScene();

 private:
  void CreateItem(int count);
  void NextStage();
  void StartStage(std::function<void()> func, int count, int interval);
  void StartDropBlockStage();
  void StartDropThronBlock();
  void StartDropBlockLine();
  void StartLaser();
  void StartDropMultipleBlockStage();

 private:
  RandomGenerator rand;
  std::shared_ptr<UiLayer> ui;
  std::shared_ptr<Player> player;
  std::shared_ptr<BlockManager> block_manager;
  Timer timer;
  bool stage_lock;
  int stage;
};

#endif  // __GAME_SCENE_H__