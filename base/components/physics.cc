#include "physics.h"
#include "sprite.h"

std::vector<Physics*> Physics::physics_children;

void Physics::UpdateAll() {
  for (auto sprite : physics_children) {
    sprite->UpdatePhysics();
  }
}

Physics::Physics() : acceleration(0) {
  Physics::physics_children.push_back(this);
}

Physics::~Physics() {
  auto& v = Physics::physics_children;
  if (auto iter = std::find(v.begin(), v.end(), this); iter == v.end()) {
    v.erase(iter);
  }
}

void Physics::UpdatePhysics() {
  if (auto sp = dynamic_cast<Sprite*>(this); sp != nullptr) {
    double delta = 50 * Global::DeltaTime;
    this->acceleration += Global::DeltaTime;
    sp->GetY() += delta + acceleration;
  }
}