
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "base.h"

class SceneManager;

class Application {
 public:
  Application();
  ~Application();
  bool Initialize();
  void Run();

 private:
  void Close();
  void UpdateDeltaTime();

 private:
  std::unique_ptr<SceneManager> scene_manager;
};

#endif  // __APPLICATION_H__