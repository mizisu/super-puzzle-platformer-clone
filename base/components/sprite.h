#ifndef __SPRITE_H__
#define __SPRITE_H__

#include "base/components/node.h"

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
  bool IsFlipHorizontal() { return is_flip_horz; }

  virtual int Width() { return width; }
  virtual int Height() { return height; }

  void FlipHorizontal(bool is_flip) { is_flip_horz = is_flip; }
  void SetTexture(std::shared_ptr<Texture> texture);
  void SetTexture(const std::string& filename);

 protected:
  std::shared_ptr<Texture> texture;
  SDL_Rect src_rect;
  SDL_Rect dest_rect;
  SDL_Point center;
  double angle;
  SDL_RendererFlip flip;
  bool is_flip_horz;
  float width;
  float height;
};

#endif  // __SPRITE_H__