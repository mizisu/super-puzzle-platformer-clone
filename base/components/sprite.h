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

  int& X() { return dest_rect.x; }
  int& Y() { return dest_rect.y; }
  SDL_Rect& DestRect() { return dest_rect; }

  virtual int Width() { return width; }
  virtual int Height() { return height; }

  void SetTexture(std::shared_ptr<Texture> texture);

 protected:
  std::shared_ptr<Texture> texture;
  SDL_Rect dest_rect;
  float width;
  float height;
};

#endif  // __SPRITE_H__