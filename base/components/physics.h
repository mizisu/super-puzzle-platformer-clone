#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "base/base.h"

class Sprite;

class Physics {
 public:
  static void UpdateAll();

 private:
  static std::vector<Physics*> physics_children;

 public:
  Physics();
  virtual ~Physics();
  void UpdatePhysics();
  void EnableGravity(bool enable);

 private:
  void UpdatePosition(Sprite* sp);
  void CheckCollision(Sprite* sp);
  void Intersect(Sprite* sp, Sprite* other);

 protected:
  void Collision(std::function<void(Sprite*, const SDL_Rect&)> fn) { collision = fn; }
  void ForceX(double force) { velocity_x = force; }
  void ForceY(double force) { velocity_y = force; }

 private:
  double acceleration;
  double velocity_y;
  double velocity_x;  
  bool enable_gravity;
  std::function<void(Sprite*, const SDL_Rect& result)> collision;
};

#endif  // __PHYSICS_H__