#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "node.h"

class Texture;

class Sprite : public Node {
 public:
  Sprite(const std::string& filename);
  virtual ~Sprite();

  virtual void Update() override;
  virtual void Render() override;

 private:
  std::shared_ptr<Texture> texture;
  SDL_Rect destRect;
};

#endif  // __SPRITE_H__