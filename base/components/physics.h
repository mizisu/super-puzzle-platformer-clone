#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "base/base.h"

class Sprite;

class Physics {
  using CollisionFunc = std::function<void(Sprite*, const SDL_Rect&)>;

 public:
  static void UpdateAll();

 private:
  static std::list<Physics*> physics_children;

 public:
  Physics();
  virtual ~Physics();
  void EnableGravity(bool enable);
  void Collision(CollisionFunc fn) { collision_functions.push_back(fn); }
  void ForceX(double force) { velocity_x = force; }
  void ForceY(double force) { velocity_y = force; }
  bool IsFalling() { return velocity_y > 0; }

 private:
  bool IsSprite() { return this->GetSprite() != nullptr; }
  Sprite* GetSprite();
  void UpdatePosition();
  void CheckCollision();
  void Intersect(Sprite* other);

 protected:
  double acceleration;

 protected:
  double velocity_x;
  double velocity_y;
  bool enable_gravity;
  std::vector<CollisionFunc> collision_functions;
  Sprite* sprite;
};

#endif  // __PHYSICS_H__