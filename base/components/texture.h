#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "base/base.h"

class Texture {
 public:
  Texture(const std::string& path);
  ~Texture();

  std::string_view& Name() { return name; }
  int Width() { return width; }
  int Height() { return height; }
  SDL_Texture* SDLTexture() { return texture; }

 private:
  SDL_Texture* texture;
  std::string_view name;
  int width;
  int height;
};

#endif  // __TEXTURE_H__