#ifndef __TEXTURE_MANAGER_H__
#define __TEXTURE_MANAGER_H__

#include "../base.h"

class Texture;

class TextureManager {
 private:
  TextureManager();
  ~TextureManager();

 public:
  static inline auto& GetInstance() {
    static TextureManager instance;
    return instance;
  }

  std::shared_ptr<Texture> GetTexture(const std::string& path);
  void LoadTexture(const std::string& path);

 private:
  std::string ConvertPath(const std::string& path);

 private:
  std::map<std::string, std::shared_ptr<Texture>> textures;
};

#endif  // __TEXTURE_MANAGER_H__
