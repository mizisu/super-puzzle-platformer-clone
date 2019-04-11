#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "base/components/scene.h"

class SceneManager {
 public:
  SceneManager();
  ~SceneManager();
  void Push(Scene* scene);
  void Play();

 private:
  Scene* current_scene;
};

#endif  // __SCENE_MANAGER_H__