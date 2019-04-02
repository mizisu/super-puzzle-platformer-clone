#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "node.h"

class Texture;

class Sprite : public Node {
 public:
  Sprite();
  Sprite(const std::string& filename);
  virtual ~Sprite();

  virtual void Update() override;
  virtual void Render() override;

  void SetPosition(int x, int y) {
    destRect.x = x;
    destRect.y = y;
  }

  int Width() { return destRect.w; }
  int Height() { return destRect.h; }

  void SetTexture(std::shared_ptr<Texture> texture);

 private:
  std::shared_ptr<Texture> texture;
  SDL_Rect destRect;
};

#endif  // __SPRITE_H__