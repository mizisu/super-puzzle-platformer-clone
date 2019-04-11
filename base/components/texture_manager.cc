#include "base/components/texture_manager.h"
#include "base/components/texture.h"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& path) {
  auto find = textures.find(path);
  if (find == textures.end()) {
    LoadTexture(path);
  }
  return textures[path];
}

void TextureManager::LoadTexture(const std::string& path) {
  textures.insert_or_assign(path, std::make_shared<Texture>(path));
}