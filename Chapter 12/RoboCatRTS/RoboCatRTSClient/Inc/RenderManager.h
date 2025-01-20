#pragma once

#include <SDL_image.h>

#include <memory>
#include <vector>

#include "SpriteComponent.h"

// I take care of rendering things!

class RenderManager {
 public:
  static void StaticInit();
  static std::unique_ptr<RenderManager> sInstance;

  void Render();
  void RenderComponents();

  // very inefficient method of tracking scene graph...
  void AddComponent(SpriteComponent* inComponent);
  void RemoveComponent(SpriteComponent* inComponent);
  int GetComponentIndex(SpriteComponent* inComponent) const;

 private:
  RenderManager();

  // this can't be only place that holds on to component- it has to live inside
  // a GameObject in the world
  std::vector<SpriteComponent*> mComponents;

  SDL_Rect mViewTransform;
};