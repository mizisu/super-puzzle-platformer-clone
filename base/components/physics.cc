#include "physics.h"
#include "sprite.h"

std::vector<Physics*> Physics::physics_children;

void Physics::UpdateAll() {
  for (auto phy : physics_children) {
    phy->UpdatePhysics();
  }
}

Physics::Physics() : enable_gravity(true), acceleration(0) {
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
    UpdatePosition(sp);
  }
}

void Physics::EnableGravity(bool enable) {
  enable_gravity = enable;
  if (!enable_gravity) {
    this->acceleration = 0;
  }
}

void Physics::UpdatePosition(Sprite* sp) {
  if (this->enable_gravity) {
    double delta = 50 * Global::DeltaTime;
    this->acceleration += Global::DeltaTime;
    sp->Y() += delta + acceleration;
  }
}

void Physics::CheckCollision(Sprite* sp) {
  SDL_Rect rect {sp->X(), sp->Y(), sp->Width(), sp->Height()};
  SDL_Rect compare_rect;
  for (auto& phy : Physics::physics_children) {
    if (auto sp = dynamic_cast<Sprite*>(this); sp != nullptr) {

    }
  }
}
