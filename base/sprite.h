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
    dest_rect.x = x;
    dest_rect.y = y;
  }

  SDL_Rect& DestRect() { return dest_rect; }

  int Width() { return dest_rect.w; }
  int Height() { return dest_rect.h; }

  void SetTexture(std::shared_ptr<Texture> texture);

 private:
  std::shared_ptr<Texture> texture;
  SDL_Rect dest_rect;
};

#endif  // __SPRITE_H__