#include "base/components/physics.h"
#include "base/components/sprite.h"

std::vector<Physics*> Physics::physics_children;

void Physics::UpdateAll() {
  for (auto phy : physics_children) {
    phy->UpdatePhysics();
  }
}

Physics::Physics()
    : enable_gravity(true),
      acceleration(15),
      velocity_x(0),
      velocity_y(0),
      collision(nullptr) {
  Physics::physics_children.push_back(this);
}

Physics::~Physics() {
  auto& v = Physics::physics_children;
  if (auto iter = std::find(v.begin(), v.end(), this); iter != v.end()) {
    v.erase(iter);
  }
  this->collision = nullptr;
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
    this->velocity_y = 0;
  }
}

void Physics::UpdatePosition(Sprite* sp) {
  if (this->enable_gravity) {
    this->velocity_y += acceleration;
    sp->Y() += this->velocity_y * Global::DeltaTime;
  }
  sp->X() += velocity_x * Global::DeltaTime;
  velocity_x *= 0.9;
}

void Physics::Intersect(Sprite* sp, Sprite* other) {
  if (other != sp) {
    auto& rect = sp->DestRect();
    auto& other_rect = other->DestRect();
    SDL_Rect result;
    if (SDL_IntersectRect(&rect, &other_rect, &result)) {
      this->collision(other, result);
    }
  }
}

void Physics::CheckCollision(Sprite* sp) {
  if (this->collision == nullptr) return;
  for (auto& phy : Physics::physics_children) {
    if (auto* other = dynamic_cast<Sprite*>(phy); other != nullptr) {
      Intersect(sp, other);
    }
  }
}
