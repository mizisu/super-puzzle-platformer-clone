#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "base/base.h"

class Sprite;

class Physics {
 public:
  static void UpdateAll();

 private:
  static std::list<Physics*> physics_children;

 public:
  Physics();
  virtual ~Physics();
  void EnableGravity(bool enable);

 private:
  bool IsSprite() { return this->GetSprite() != nullptr; }
  Sprite* GetSprite();
  void UpdatePosition();
  void CheckCollision();
  void Intersect(Sprite* other);

 protected:
  void Collision(std::function<void(Sprite*, const SDL_Rect&)> fn) {
    collision = fn;
  }
  void ForceX(double force) { velocity_x = force; }
  void ForceY(double force) { velocity_y = force; }
  bool IsFalling() { return velocity_y > 0; }

 private:
  double acceleration;
  double velocity_y;
  double velocity_x;
  bool enable_gravity;
  std::function<void(Sprite*, const SDL_Rect& result)> collision;
  Sprite* sprite;
};

#endif  // __PHYSICS_H__