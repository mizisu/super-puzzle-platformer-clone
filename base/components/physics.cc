#include "base/components/physics.h"
#include "base/components/sprite.h"

std::vector<Physics*> Physics::physics_children;

void Physics::UpdateAll() {
  for (auto phy : physics_children) {
    phy->UpdatePhysics();
  }
}

Physics::Physics()
    : enable_gravity(true), acceleration(0), on_collision(nullptr) {
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
    CheckCollision(sp);
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

void Physics::Intersect(Sprite* sp, Sprite* other) {
  if (other != sp) {
    auto& rect = sp->DestRect();
    auto& other_rect = other->DestRect();
    if (SDL_HasIntersection(&rect, &other_rect)) {
      this->on_collision(other);
    }
  }
}

void Physics::CheckCollision(Sprite* sp) {
  if (this->on_collision == nullptr) return;
  for (auto& phy : Physics::physics_children) {
    if (auto* other = dynamic_cast<Sprite*>(phy); other != nullptr) {
      Intersect(sp, other);
    }
  }
}
