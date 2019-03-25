#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "base.h"

class Texture {
 public:
  Texture(const std::string& path);
  ~Texture();

  int Width() { return width; }
  int Height() { return height; }

 private:
  SDL_Texture* texture;
  int width;
  int height;
};

#endif  // __TEXTURE_H__