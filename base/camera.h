#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "base/base.h"

class Camera {
 public:
  static auto& GetInstance() {
    static Camera instance;
    return instance;
  }

  void Update() {
    if (this->shake_force != 0) {
      this->viewport.x = rand.Get(-shake_force, shake_force);
      this->viewport.y = rand.Get(-shake_force, shake_force);
    }
    SDL_RenderSetViewport(Global::Renderer, &viewport);
  }

  void Shake(int force, int interval) {
    this->shake_force = force;
    timer.SetTimeout(
        [&]() {
          this->shake_force = 0;
          this->viewport.x = 0;
          this->viewport.y = 0;
        },
        interval);
  }

 private:
  Camera() : shake_force(0) {
    viewport = {0, 0, Global::ScreenRealWidth, Global::ScreenRealHeight};
  }

 private:
  SDL_Rect viewport;
  int shake_force;
  Timer timer;
  RandomGenerator rand;
};

#endif  // __CAMERA_H__