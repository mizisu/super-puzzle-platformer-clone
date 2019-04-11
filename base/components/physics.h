#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "../base.h"

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
  
 private:
  double acceleration;
  bool enable_gravity;
};

#endif  // __PHYSICS_H__