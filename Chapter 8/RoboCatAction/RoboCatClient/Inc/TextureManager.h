#pragma once

#include <string>
#include <unordered_map>

#include "Texture.h"

class TextureManager {
 public:
  static void StaticInit();

  static std::unique_ptr<TextureManager> sInstance;

  TexturePtr GetTexture(const std::string& inTextureName);

 private:
  TextureManager();

  bool CacheTexture(std::string inName, const char* inFileName);

  std::unordered_map<std::string, TexturePtr> mNameToTextureMap;
};