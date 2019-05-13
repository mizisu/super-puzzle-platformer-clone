#ifndef __SCENE_MANAGER_H__
#define __SCENE_MANAGER_H__

#include "base/components/scene.h"

class SceneManager {
 private:
  SceneManager();

 public:
  ~SceneManager();
  void Push(Scene* scene);
  void Play();
  static auto& GetInstance() {
    static SceneManager instance;
    return instance;
  }

 private:
  Scene* current_scene;
};

#endif  // __SCENE_MANAGER_H__