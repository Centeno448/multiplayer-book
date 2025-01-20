#pragma once

#include <memory>
#include <unordered_map>

#include "GameObject.h"

typedef GameObjectPtr (*GameObjectCreationFunc)();

class GameObjectRegistry {
 public:
  static void StaticInit();

  static std::unique_ptr<GameObjectRegistry> sInstance;

  void RegisterCreationFunction(uint32_t inFourCCName,
                                GameObjectCreationFunc inCreationFunction);

  GameObjectPtr CreateGameObject(uint32_t inFourCCName);

 private:
  GameObjectRegistry();

  std::unordered_map<uint32_t, GameObjectCreationFunc>
      mNameToGameObjectCreationFunctionMap;
};
