#include "scene_manager.h"
#include "physics.h"

SceneManager::SceneManager() : current_scene(nullptr) {}

SceneManager::~SceneManager() { Global::SafeDelete(current_scene); }

void SceneManager::Push(Scene* scene) {
  if (current_scene) current_scene->Clear();
  Global::SafeDelete(current_scene);
  if (scene) {
    scene->SetSceneManager(this);
    current_scene = scene;
  }
}

void SceneManager::Play() {
  if (current_scene) {
    current_scene->UpdateChildren();
    Physics::UpdateAll();
    current_scene->RenderChildren();
  }
}
