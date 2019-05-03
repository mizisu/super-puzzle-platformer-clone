#include "base/components/physics.h"
#include "base/components/sprite.h"

std::list<Physics*> Physics::physics_children;

void Physics::UpdateAll() {
  for (auto& phy : physics_children) {
    if (phy->IsSprite()) phy->UpdatePosition();
  }

  for (auto& phy : physics_children) {
    if (phy->IsSprite()) phy->CheckCollision();
  }
}

Physics::Physics()
    : enable_gravity(true),
      acceleration(15),
      velocity_x(0),
      velocity_y(0),
      sprite(nullptr) {
  Physics::physics_children.push_back(this);
}

Physics::~Physics() {
  this->collision_functions.clear();
  auto& v = Physics::physics_children;
  if (auto iter = std::find(v.begin(), v.end(), this); iter != v.end()) {
    v.erase(iter);
  }
  this->sprite = nullptr;
}

void Physics::EnableGravity(bool enable) {
  enable_gravity = enable;
  if (!enable_gravity) {
    this->velocity_y = 0;
  }
}

Sprite* Physics::GetSprite() {
  if (this->sprite == nullptr) this->sprite = dynamic_cast<Sprite*>(this);
  return sprite;
}

void Physics::UpdatePosition() {
  if (this->enable_gravity) {
    this->velocity_y += acceleration;
    this->GetSprite()->Y() += this->velocity_y * Global::DeltaTime;
  }
  this->GetSprite()->X() += velocity_x * Global::DeltaTime;
  velocity_x *= 0.9;
}

void Physics::CheckCollision() {
  if (this->collision_functions.size() == 0) return;
  for (auto& other : Physics::physics_children) {
    if (other->IsSprite() && this != other) Intersect(other->GetSprite());
  }
}

void Physics::Intersect(Sprite* other) {
  auto& rect = this->GetSprite()->GetCollisionRect();
  auto& other_rect = other->GetCollisionRect();
  SDL_Rect result;
  if (SDL_IntersectRect(&rect, &other_rect, &result)) {
    for (auto& func : this->collision_functions) {
      func(other, result);
    }
  }
}