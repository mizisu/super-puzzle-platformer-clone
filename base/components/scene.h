#ifndef __SCENE_H__
#define __SCENE_H__

#include "base/components/node.h"

class SceneManager;

class Scene : public Node {
 public:
  Scene();
  ~Scene();
  void Next(Scene* scene);
  void SetSceneManager(SceneManager* scene_manager) {
    this->scene_manager = scene_manager;
  }

 private:
  SceneManager* scene_manager;
};

#endif  // __SCENE_H__
