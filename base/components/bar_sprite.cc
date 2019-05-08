#include "base/components/bar_sprite.h"
#include "base/components/texture.h"

void BarSprite::SetValue(int value) {
  this->value = value;
  double val = (double)(value - min) / (double)(max - min);
  double len = (double)this->texture->Width() * val;
  this->src_rect.w = len;
  this->dest_rect.w = len;
}