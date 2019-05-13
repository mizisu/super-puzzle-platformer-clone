#include "base/components/scene_manager.h"
#include "base/camera.h"
#include "base/components/physics.h"

SceneManager::SceneManager() : current_scene(nullptr) {}

SceneManager::~SceneManager() { Global::SafeDelete(current_scene); }

void SceneManager::Push(Scene* scene) {
  if (current_scene) current_scene->Clear();
  Global::SafeDelete(current_scene);
  if (scene) {
    current_scene = scene;
  }
}

void SceneManager::Play() {
  if (current_scene) {
    Physics::UpdateAll();
    current_scene->UpdateChildren();
    Camera::GetInstance().Update();
    current_scene->RenderChildren();
    current_scene->RemoveMarkedChild();
  }
}
