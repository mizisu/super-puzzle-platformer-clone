#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "base/components/sprite.h"

class Player;

class Weapon : public Sprite {
  using base = Sprite;
 public:
  Weapon();
  virtual ~Weapon() = default;
  virtual void Update() override;
  virtual void Render() override;
  void SetPlayer(std::shared_ptr<Player> player) { this->player = player; }
  void Fire();

 private:
  std::shared_ptr<Player> player;
  InputAdapter input;
};

#endif  // __WEAPON_H__