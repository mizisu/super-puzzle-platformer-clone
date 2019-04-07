#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include "../base.h"

class Physics {
 public:
  static void UpdateAll();

 private:
  static std::vector<Physics*> physics_children;

 public:
  Physics();
  virtual ~Physics();
  void UpdatePhysics();

 private:
  double acceleration;
};

#endif  // __PHYSICS_H__