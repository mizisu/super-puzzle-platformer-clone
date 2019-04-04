#include "scene.h"
#include "scene_manager.h"

Scene::Scene() {}

Scene::~Scene() { scene_manager = nullptr; }

void Scene::Next(Scene* scene) { scene_manager->Push(scene); }